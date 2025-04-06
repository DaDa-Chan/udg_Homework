#ifndef DIARY_H
#define DIARY_H

#include<string>
#include<vector>
#include<map>

using namespace std;

const string DIARY_FILENAME = "personal_diary.dat";

class Diary{
private:
    map<string,string>entries; //map:date<YYYY-MM-DD> -> content

    string data_filename;

public:
    explicit Diary(const string& filename);

    //delete copy constructor
    Diary(const Diary&) = delete;
    //delete copy assignment
    Diary& operator  = (const Diary&) = delete;

    bool read(); // read at beginning

    bool store() const ;// store back at the end

    void addEntry(const string& date, const string& content);

    bool removeEntry(const string& date);

    const string* showContent(const string& date) const;

    vector<string> listDates(const string& start = "",const string& end = "") const;

};

bool checkFormat(const string& date);

#endif