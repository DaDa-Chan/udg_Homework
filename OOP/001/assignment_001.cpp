//Write a program that asks you for 10 records of students. 
//Each record consists of a name (w/o space) and scores for three courses (in integer, 1 to 5).
//Output a list as follows and calculate the average score (in float) of each student and each course. 
//Output the lowest and highest score for each course.
/*
no      name    score1  score2  score3  average
1       K.Weng  5       5       5       5
2       T.Dixon 4       3       2       3
3       V.Chu   3       4       5       4
4       L.Tson  4       3       4       3.66667
5       L.Lee   3       4       3       3.33333
6       I.Young 4       2       5       3.66667
7       K.Hiro  4       2       1       2.33333
8       G.Ping  4       4       4       4
9       H.Gu    2       3       4       3
10      J.Jon   5       4       3       4
        average 3.8     3.4     3.6
        min     2       2       1
        max     5       5       5
'''
*/
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<iomanip>

using namespace std;


int main(){

  string record;
  vector<string> name;
  vector<int> score1,score2,score3;
  vector<float> student_avg;//每个学生的平均成绩
  float score1_avg = 0.0,score2_avg = 0.0,score3_avg = 0.0;
  int score1_max = -1,score2_max = -1,score3_max = -1;
  int score1_min = INT_MAX,score2_min = INT_MAX,score3_min = INT_MAX;

  for(int i = 0;i<10;i++){
    getline(cin,record);
    istringstream iss(record);//创建输入流，分割字符串

    string part;
    if(iss>>part) name.push_back(part);//储存学生名字

    int s1,s2,s3;
    if(iss>>s1){
      score1.push_back(s1);
      score1_max = max(score1_max,s1);
      score1_min = min(score1_min,s1);
      score1_avg += s1;
    }
    if(iss>>s2){
      score2.push_back(s2);
      score2_max = max(score2_max,s2);
      score2_min = min(score2_min,s2);
      score2_avg += s2;
    }
    if(iss>>s3){
      score3.push_back(s3);
      score3_max = max(score3_max,s3);
      score3_min = min(score3_min,s3);
      score3_avg += s3;
    }
    //计算每个学员的平均成绩
    student_avg.push_back((s1+s2+s3)/3.0);      
    
  }

  score1_avg /= 10.0;
  score2_avg /= 10.0;
  score3_avg /= 10.0;
// 打印表头
  cout<< setw(3) << "no" 
      << setw(10) << "name" 
      << setw(8) << "score1" 
      << setw(8) << "score2" 
      << setw(8) << "score3" 
      << setw(10) << "average" 
      << endl;

//打印每个同学的成绩
  for(int i =0 ; i<10 ; i++){
    cout << setw(3)   << i+1
         << setw(10)  << name[i]
         << setw(8)   << score1[i]
         << setw(8)   << score2[i]
         << setw(8)   << score3[i]
         << setw(10)  << fixed << setprecision(5) << student_avg[i]
         << endl;
  }
//打印每个科目的均分
  cout << setw(3)  << " "
       << setw(10) <<"average"
       << setw(8)  << fixed << setprecision(2) << score1_avg
       << setw(8)  << fixed << setprecision(2) << score2_avg
       << setw(8)  << fixed << setprecision(2) << score3_avg
       << endl;
//打印每个科目的最高分
  cout << setw(3)  << " "
       << setw(10) <<"max"
       << setw(8)  << score1_max
       << setw(8)  << score2_max
       << setw(8)  << score3_max
       << endl;
//打印每个科目的最低分
  cout << setw(3)  << " "
       << setw(10) << "min"
       << setw(8)  <<  score1_min
       << setw(8)  <<  score2_min
       << setw(8)  <<  score3_min
       << endl;


  return 0;
}