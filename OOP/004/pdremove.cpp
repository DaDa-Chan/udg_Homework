#include"diary.h"
#include<string>
#include<iostream>

using namespace std;

void show_usage() {
    cerr << "Usage: pdremove YYYY-MM-DD" << endl;
    cerr << "Removes the diary entry for the specified date." << endl;
    cerr << "Returns 0 on success, -1 if the entry was not found, "
         << "other non-zero on errors." << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: Incorrect number of arguments." << std::endl;
        show_usage();
        return 1; 
    }

    std::string date = argv[1];
    if(!checkFormat(date)) {
        std::cerr << "Error: Invalid date format '" << date << "'." << std::endl;
        show_usage();
        return 1; 
    }
    
    Diary mydiary(DIARY_FILENAME);
    if(!mydiary.read()){
        return 1;
    }

    if(mydiary.removeEntry(date)){
        cout << "Diary entry for " << date << " removed." << endl;
        if(!mydiary.store()){
            cerr << "failed to store" << endl;
            return 2;
        }
        return 0;
    }else{
        cerr << "Info: No diary entry found for date " << date << " to remove." << endl;
        return -1;
    }
}