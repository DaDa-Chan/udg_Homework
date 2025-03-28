#include"express_evaluator.h"
#include <fstream>
using namespace std;

void calculator(string &input)
{
    int flag = 1;
    vector<string> expressor;
    vector<string> suffix;

    split(expressor,input);

    check_expressor(expressor,flag);

    if(flag)
    {
        suffix = suffixexpressor(expressor);        
        calculate(suffix , flag);
    }
    else return;    
}

int main() {
    ///*
    ifstream file("expressions.txt"); 
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }
    string line;

    while (getline(file, line)) {
        if (!line.empty()) { // 跳过空行
            cout << line << " : ";
            calculator(line); 
            cout << endl;
        }
    }

    file.close(); // 关闭文件
    //*/

    /*
    string str;
    cin >> str;
    calculator(str);
    */
    
}