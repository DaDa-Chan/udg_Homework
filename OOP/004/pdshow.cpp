#include"diary.h"
#include<iostream>
#include<string>

using namespace std;

void show_usage(){
    cerr << "Usage: pdshow YYYY-MM-DD" << endl;
    cerr << "Prints the content of the diary entry for the specified date." << endl;    
}

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr<<"Error: Incorrect number of arguments"<<endl;
        show_usage();
        return 1;

    }

    string date = argv[1];

    if(!checkFormat(date)){
        cerr<<"Error: Invalid date formet"<<date <<"."<<endl;
        show_usage();
        return 1;
    }

    Diary mydiary(DIARY_FILENAME);
    if(!mydiary.read()){
        return 1;
    }

    const string* content = mydiary.showContent(date);
    
    if(content != nullptr){
        cout<< *content << endl;
        return 0;
    }else{
        cerr<<"Error: No diary entry found for date"<<endl;
        return 1;
    }


}