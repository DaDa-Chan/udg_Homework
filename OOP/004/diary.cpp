#include "diary.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex> 
#include <vector>
using namespace std; 

Diary::Diary(const string& filename ):data_filename(filename) {}

bool Diary::read(){// read the data 
    entries.clear();
    ifstream inFile(data_filename);

    if(!inFile){//the file doesn't exit is ok.
        return true;
    }

    string line;
    string curDate = "";
    string curContent = "";
    bool isContent = false; //flag :check if it is reading the content
    
    while(getline(inFile,line)){
        if(!isContent){
            if(checkFormat(line)){
                curDate = line;
                curContent = "";//renew the content
                isContent = true;
            }
        }
        else{
            if(line == "."){ //using "." to end.
                if(!curContent.empty()){
                    if(curContent.back() == '\n'){
                        curContent.pop_back();
                    }
                    entries[curDate] = curContent;//Add to map
                }
                isContent = false;
                curContent = "";
            }
            else{
                curContent += line+"\n";
            }
        }                    
    }
    
    if(isContent && !curContent.empty() ){
        if(curContent.back() == '\n'){
            curContent.pop_back();
        }
        entries[curDate] = curContent;
    }

    if(inFile.bad()){
        cerr<<"Error:The file is criticle bad"<<endl;
        return false;
    }

    return true;
}

bool Diary::store() const{
    ofstream outFile(data_filename);//open file for writing
    if(!outFile){
        cerr<<"Error: Cannot open the file"<<endl;
        return false;
    }

    for(const auto& entry: entries){//entry is a pair
        outFile<< entry.first << endl;
        outFile<< entry.second << endl;
        outFile<< "." << endl;
    }

    if(outFile.bad()){
        cerr<< "Error:The file is criticle bad" <<endl;
        return false;
    }

    return true;
}


void Diary::addEntry(const string& date , const string& content){
    entries[date] = content;
}


bool Diary::removeEntry(const string& date) {
    return entries.erase(date) > 0 ; //map::erase() return 1 if the key successfully erased otherwise return 0
}

const string* Diary::showContent(const string& date) const {
    auto it = entries.find(date);//return an iterator

    if(it != entries.end()){
        return &(it->second);
    }else{
        return nullptr;
    }
}



vector<string> Diary::listDates(const string& start_date ,const string& end_date) const{
    vector<string> dates ;

    //Determine the range
    auto it_start =  entries.begin();

    if(!start_date.empty() && checkFormat(start_date)){
        it_start = entries.lower_bound(start_date);
    }

    auto it_end = entries.end();

    if(!end_date.empty() && checkFormat(end_date)){
        it_end = entries.upper_bound(end_date);
    }

    for(auto it = it_start; it != it_end ; ++it){
        dates.push_back(it->first);
    }

    return dates;
}


bool checkFormat(const string& date){
    //"YYYY-MM-DD"
    static const regex data_pattern(R"(^\d{4}-\d{2}-\d{2}$)");
    return regex_match(date , data_pattern);
}