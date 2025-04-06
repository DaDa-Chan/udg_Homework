#include"diary.h"
#include<string>
#include<iostream>

using namespace std;

void show_usage(){
    cerr<<"Usage: pdadd YYYY-MM-DD"<< endl;
    cerr<<"Reads diary entry content from standard input until a line"<< endl;
    cerr<<"containing only '.' or EOF (Ctrl+D/Ctrl+Z) is encountered."<< endl;
}

int main(int argc, char* argv[]){
    if(argc != 2){
       cerr<<"Error: Incorrect number of arguments."<<endl;
       show_usage();
       return 1;
    }

    string date = argv[1];

    if(!checkFormat(date)){
        cerr << "Error: Invalid date format '" << date << "'. Please use YYYY-MM-DD." << endl;
        show_usage();
        return 1;
    }

    Diary mydiary(DIARY_FILENAME);

    if(!mydiary.read()){//read the memory
        return 1;
    }

    cout << "Enter diary content for " << date << ". End with '.' on a new line or EOF:" << endl;

    string content = "";
    string line;

    while(getline(cin,line)){
        if(line == "."){
            break;// end with "."
        }
        content += line +"\n";
    }

    if(!content.empty()){
        if(content.back() == '\n'){
            content.pop_back();
        }
    }

    mydiary.addEntry(date,content);

    if(!mydiary.store()){
        return 1;
    }

    cout << "Diary entry for " << date << " saved." << endl;
    return 0;

}   
