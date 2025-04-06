#include"diary.h"
#include<string>
#include<vector>
#include<iostream>

using namespace std;

void show_usage() {
    cerr << "Usage: pdlist [YYYY-MM-DD_start] [YYYY-MM-DD_end]" << endl;
    cerr << "Lists diary entry dates. If start/end dates are given," << endl;
    cerr << "lists entries within that range (inclusive)." << endl;
}

int main(int argc , char* argv[]){
    if(argc > 3){
        cerr<< "Error: Too many arguments." <<endl;
        show_usage();
        return 1;
    }

    string start_date = "";
    string end_date = "";

    if(argc >= 2){
        start_date = argv[1];
        if(!checkFormat(start_date)){
            cerr<<"Error: Unvalid startdate:"<< start_date << "." <<endl;
            show_usage();
            return 1;
        }
    }
    
    if(argc == 3){
        end_date = argv[2];
        if(!checkFormat(end_date)){
            cerr<<"Error: Unvalid enddate:"<< end_date << "." <<endl;
            show_usage();
            return 1;
        }
        if(!start_date.empty() && start_date > end_date){
            cerr << "Error: Start date (" << start_date
                 << ") must be less than or equal to end date (" << end_date 
                 << ")."<< endl;
            return 1;
        }
    }

    Diary mydiary(DIARY_FILENAME);
    if(!mydiary.read()){
        return 1;
    }

    vector<string> dates = mydiary.listDates(start_date,end_date);

    for(const string& date : dates){
        cout<< date << endl;
    }

    return 0;
} 