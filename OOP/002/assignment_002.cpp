#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

class Calendar {
private:
    int year;
    int month_per_row;

    //储存月份名字
    const vector<string> month_names = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // 判断是否为润年
    bool isLeapYear(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    //获取每月天数
    int getmonthdays(int y, int m) {
        static const int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (m == 2 && isLeapYear(y)) {  // 润年二月份天数加一
            return 29;
        }
        return days_in_month[m-1];
    }

    //利用蔡勒公式，返回给定月份的第一天是星期几(0 = 星期日)
    int getmonthfirstday(int y ,int m){
        if(m < 3){
            m+=12;
            y--;
        }

        int d = 1;
        int k = y % 100;
        int j = y / 100;
        int day = (d + ((13 * (m + 1)) / 5) + k + (k / 4) + (j / 4) + (5 * j)) % 7;

        return (day + 6)%7;
    }

/*
    vector<string> getmonthblock(int y ,int m) {
        vector<string> block;
        
        int width = 20;

    }

    
        try {
            // 确保 month_name 长度不会超过 width，防止负数 padding
            string month_name = month_names[m - 1];
            if (month_name.size() > width) {
                month_name = month_name.substr(0, width);  // 截断过长的名字
            }
    
            int l_padding = max(0, (width - (int)month_name.size()) / 2);
            int r_padding = max(0, width - l_padding - (int)month_name.size());
    
            block.push_back(string(l_padding, ' ') + month_name + string(r_padding, ' '));
    
            // 处理日期行
            int days = getmonthdays(y, m);
            int first_day = getmonthfirstday(y, m);
    
            string line = "";
            stringstream ss;
    
            for (int i = 0; i < first_day; ++i) {  // 处理第一行
                line += string(" ", 3);
            }
    
            for (int d = 1; d <= days; ++d) {
                ss.str("");
                ss.clear();
                ss << setw(3) << d;
                line += ss.str();
    
                if (d != days && (first_day + d) % 7 == 0) {
                    block.push_back(line);
                    cout<< line <<endl;
                    line = "";
                }
                else if (d == days) {  // 最后一行补齐长度
                    int padding = max(0, width - (int)line.size());
                    line += string(padding, ' ');
                    block.push_back(line);
                }
            }
    
            // 保证每个月的 block 行数一致
            while (block.size() < 7) {
                block.push_back(string(width,' '));
            }
        } catch (const std::length_error& e) {
            cerr << "Error: String length exceeded in getmonthblock() for month " << m << ": " << e.what() << endl;
        } catch (const std::exception& e) {
            cerr << "Unexpected error in getmonthblock(): " << e.what() << endl;
        }
    
        return block;
    }
*/


    vector<string> getmonthblock(int y ,int m){
        vector<string> block;
        
        int width = 21;

        //加入居中月名行
        string month_name = month_names[m-1];
        int l_padding = (width - month_name.size())/2;
        int r_padding = width - l_padding - month_name.size();
        block.push_back(string(max(0,l_padding),' ') + month_name + string(max(0,r_padding),' '));

        //加入日期行
        int days = getmonthdays(y,m);
        int first_day = getmonthfirstday(y,m);

        string line = "";
        stringstream ss;
        
        for(int i = 0;i < first_day;++i){//处理第一行
            line += string(3,' ');
        }

        for (int d = 1; d < days+1;++d){

            ss.str("");
            ss << setw(3) << d;
            line += ss.str();

            if (d != days && (first_day+d)%7 == 0){
                block.push_back(line);
                line = "";
            }
            else if (d == days){//最后一行补齐长度
                int padding = width - line.size();
                line += string(padding,' ');
                block.push_back(line);
                line ="";
            }
        }

        while(block.size()<7){// 保证每个月block行数一样
            block.push_back(string(width,' '));
        }
        
        return block;
    }
 

public:

    Calendar(int y ,int n ) : year(y),month_per_row(n){}

/*
    void print_calendar() {


        try {
            vector<vector<string>> all_months;
            for (int m = 1; m <= 12; ++m) {
                all_months.push_back(getmonthblock(year, m));
            }
    
            int rows = 12 / month_per_row;
    
            for (int row = 0; row < rows; ++row) {
                for (int l = 0; l < 7; ++l) {
                    string line = "";
                    for (int i = month_per_row * row; i < min(12, month_per_row * (row + 1)); i++) {
                        if (i < all_months.size()) {
                            line += all_months[i][l] + "  ";
                        }
                    }
                    cout << line << endl;
                }
            }
        } catch (const std::out_of_range& e) {
            cerr << "Error: Out of range access in print_calendar(): " << e.what() << endl;
        } catch (const std::exception& e) {
            cerr << "Unexpected error in print_calendar(): " << e.what() << endl;
        }
    
*/
    


    //打印日历
    void print_calendar(){

        vector< vector<string> > all_months;
        for(int m =1;m < 13;++m){
            all_months.push_back(getmonthblock(year,m));
        }

        int rows = 12/month_per_row;

      
        for(int row = 0; row < rows ; row++){
            for(int l = 0; l < 7 ; ++l){
                for(int i = month_per_row*row ; i < month_per_row*(row+1);i++){
                    cout << all_months[i][l]<<"  ";
                }
                cout << endl;
            }
        }
    }
    

};


int main(int argc, char* argv[]){

    if (argc != 3) {//检查参数
        std::cerr << "Usage: " << argv[0] << " <year> <months_per_row>" << std::endl;
        return 1;
    }

    int year, months_per_row;
    std::stringstream ss;
    
    ss << argv[1];
    ss >> year;
    ss.clear();
    
    ss << argv[2];
    ss >> months_per_row;

    if (months_per_row <= 0) {
        std::cerr << "Error: months_per_row must be positive." << std::endl;
        return 1;
    }

    Calendar cal1(year,months_per_row);
    cal1.print_calendar();

    return 0;

}