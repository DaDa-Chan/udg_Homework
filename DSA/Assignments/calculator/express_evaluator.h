#pragma once

#include<string>
#include<iostream>
#include<stack>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<sstream>

using namespace std;

stack<char> expressor_trans;
vector<string> expressor_split;

/**
 * @brief 区分不同字符的类型，字符与数字类型相关的区分界限为1
 * @param 字符
 * @return 不同字符对应的编号
 */
inline int type(const char& ch)
{

    if (ch == '+' || ch == '-' || ch == '*' || ch == '/') return 0;
    if (ch =='(' || ch == ')') return 1;
    if ('0' <= ch && ch <= '9') return 2;
    if (ch == '.') return 3;
    if (ch == 'e' || ch == 'E') return 4;//支持大写“E”
    else return -1;
}

/**
 * @brief 对输入的表达式进行切分
 * @param 装载的空容器、输入的表达式
 * @return 切分过的字符串
 */
inline void split(vector<string> &result,string &input)
{
    size_t fast = 0;
    size_t low  = 0;
    while(fast < input.size())
    {
        if(type(input[fast]) <= 1 )//除了数字、小数点、“e”之外的都做单个切分
        {
            result.push_back(string(1,input[fast]));
            fast++;
        }
        else 
        {
            string elm = "";
            while(fast < input.size() && type(input[fast])>1)//将数字作为一个整体放入容器内
            {
                elm += input[fast];
                fast++;
                if (type(elm.back()) == 4) //出现"e"或者"E"
                {
                    if (fast < input.size() && (input[fast] == '+' || input[fast] == '-')) 
                    {
                        elm += input[fast];
                        fast++;
                    }
                }
            }
            result.push_back(elm);
        }
        low = fast;
    }
    /*
    for(auto x : result)
    {
        cout << x << " ";
    }
    cout << endl;
    */
}

/**
 * @brief 检查带有小数点的数据的正确性，包括用科学技术法表示的float数据
 */
inline void check_float(string &str,int &flag)
{
    int num = count(str.begin(),str.end(),'.');
    size_t pos = str.find(".");

    if (pos == std::string::npos) return; // 没有小数点，不是浮点数，但合法.这一步为了判断科学计数法数据而设计

    if(num > 1) 
    {
        cout << "ILLEGAL_f1" << endl; //小数点大于一个报错
        flag = 0;
        return;
    }

    else if(pos == 0 || pos == str.length()-1 )
    {
        cout << "ILLEGAL_f2" << endl; //小数点前后没有数字报错
        flag = 0;
        return;
    }

    else if(type(str[pos+1]) != 2 || type(str[pos-1]) != 2)
    {
        cout << "ILLEGAL_f3" << endl;//小数点前后不是数字报错
        flag = 0;
        return;
    }
}
/**
 * @brief 检查用科学计数法表示的数据的正确性，如果正确则转化呗float型数据
 */
inline void check_e(string & str ,vector<string> &result ,int &k,int &flag)
{
    //if(flag == 0 ) return;//已经错了就没必要继续检查了 

    int num = count(str.begin(),str.end(),'e') + count(str.begin(), str.end(), 'E');
    size_t pos = str.find("e");
    if (pos == string::npos) pos = str.find('E');

    if(pos == string::npos) return;

    if(num >1) 
    {
        cout << "ILLEGAL_e1" << endl;//e的数量大于两个报错；
        flag = 0;
        return;
    }
    if(pos == 0 || pos == str.length()-1 )
    {
        cout << "ILLEGAL_e2" << endl; //e前后没有数字报错
        flag = 0;
        return;
    }

    string before_e = str.substr(0, pos);
    check_float(before_e,flag);  // 如果 before_e 不合法，会直接输出 ILLEGAL 并返回

    // 检查 e 后的部分是否合法（整数，可以带符号）
    string after_e = str.substr(pos + 1);

    // e 后面不能是空的
    if (after_e.empty()) {
        cout << "ILLEGAL_e3" << endl;
        flag = 0;
        return;
    }

    // e 后的第一字符可以是 '+' 或 '-'
    size_t start = 0;
    if (after_e[0] == '+' || after_e[0] == '-' ) {
        if(after_e.size()>1) start = 1;
        else {
            cout << "ILLEGAL_e4"<< endl;
            flag = 0;
            return;
        }
    }

    // e 后的部分必须是纯数字
    for (size_t i = start; i < after_e.size(); ++i) {
        if (type(after_e[i]) != 2) {
            cout << "ILLEGAL_e5" << endl;
            flag = 0;
            return;
        }
    }

    /*
    try {
        float value = stof(str);  // 转换为浮点数
        ostringstream oss;
        oss << value;
        result[k] = oss.str();
    } catch (...) {
        cout << "ILLEGAL_e5" << endl;
        flag = 0;
    }
    */
}

/**
 * @brief 检查表达式的正确性,预处理负数
 * 
 */
inline void check_expressor(vector<string> & result, int &flag)
{
    int Leftbrackets = 0;//左括号数
    
    for(int i = 0;i<result.size();i++)
    {
        //if(flag == 0) break;

        //cout << "Checking: " << result[i] << endl;

        //判断单个符号
        if(result[i].size() == 1)
        {
            if((type(result[i][0]) == -1 || type(result[i][0]) >= 3))//如果出现特殊符号，或者"."和“e”单独出现则报错
            {
                cout << "ILLEGAL_c1" << endl;
                flag = 0;
                break;
            }

            //判断括号
            if(type(result[i][0]) == 1)//出现括号
            {
                if(result[i] == "(") //出现左括号+1，右括号-1
                {
                    if(i-1 >= 0 && type(result[i][0]) == 2){
                        cout << "ILLEGAL_c2" << endl;
                        flag = 0;
                        break;
                    }
                    else Leftbrackets++;
                }
                else 
                {
                    Leftbrackets--;
                    if(Leftbrackets < 0)//右括号数大于左括号数报错
                    {
                        cout << "ILLEGAL_c3" << endl;
                        flag = 0;
                        break;
                    }
                    if(result[i-1] == "(" || (i<result.size()-1 && result[i+1] == "("))//"()"or")("
                    {
                        cout << "ILLEGAL_c4"<<endl;
                        flag = 0;
                        break;
                    }
                }

            }
            //预处理负数情况
            if(i == 0 && result[i] == "-")//处理负数为第一个数的情况
                result.insert(result.begin()+i , "0");

            if ((result[i] == "+" || result[i] == "("))
            {
                if( i+1 < result.size() - 1 && result[i+1] == "-")
                    result.insert(result.begin()+i+1 , "0");
            }

            if (result[i] == "*" || result[i] == "/"|| result[i] == "-" )
            {
                if( i+1 < result.size() - 1 && result[i+1] == "-")
                {
                    result.insert(result.begin()+i+3 , ")");
                    result.insert(result.begin()+i+1 , "0");
                    result.insert(result.begin()+i+1 , "(");
                }
            }


            // 检查操作符两边是否合法
            if (type(result[i][0]) == 0)// + - * /
            {
                // 检查左侧是否合法
                if (i == 0 || (type(result[i - 1][0]) != 2 && result[i - 1] != ")")) 
                {
                    cout << "ILLEGAL_c5" << endl;
                    flag = 0;
                    break;
                }
                // 检查右侧是否合法
                if (i == result.size() - 1 || (type(result[i + 1][0]) != 2 && result[i + 1] != "(")) 
                {
                    cout << "ILLEGAL_c6" << endl;
                    flag = 0;
                    break;
                }
            }

        }

        //判断数据正确性
        else
        {
            check_float( result[i] , flag );
            check_e( result[i] , result , i , flag );
        }
    }
    //判断括号是否匹配
    if (Leftbrackets != 0) {
        cout << "ILLEGAL_c7" << endl;
        flag = 0;
    }

    /*
    for(auto x  : result)
    {
        cout << x << " ";
    }
    cout << endl;
    */

    //if (flag == 1) cout << "expressor_True" << endl; //标记

}

/**
 * @brief 比较计算符号的优先级
 * @param "+,-,*,/"
 * @return 返回计算符号的优先级，数字越大表示优先级越高
 */
inline int priority(const string& t)
{
    if(t == "+" || t == "-") return 1;
    if(t == "*" || t == "/") return 2;
    return -1;
}


/**
 * @brief 将中缀表达式转化为后缀表达式
 */
inline vector<string> suffixexpressor(vector<string> &infix)
{
    vector<string> suffix;
    stack<string> op;
    
    for(size_t i = 0 ; i<infix.size() ; ++i)
    {
        if(type(infix[i][0]) == 2)//遇到数字，入栈
        {
            suffix.push_back(infix[i]);
            continue;
        }
        else if(infix[i] == "(") op.push(infix[i]);
        else if (infix[i] == ")") 
        { // 遇到右括号
            // 弹出操作符，直到遇到左括号为止
            while (!op.empty() && op.top() != "(") {
                suffix.push_back(op.top());
                op.pop();
            }
            if (!op.empty() && op.top() == "(") {
                op.pop(); // 弹出左括号，但不加入后缀表达式
            } else {
                cout << "ILLEGAL: Mismatched parentheses" << endl;
                return {};
            }
        } 
        else 
        { // 普通操作符
            // 弹出优先级高或相同的操作符，直到栈为空或遇到左括号
            while (!op.empty() && op.top() != "(" && priority(infix[i]) <= priority(op.top())) {
                suffix.push_back(op.top());
                op.pop();
            }
            op.push(infix[i]); // 当前操作符入栈
        }

        /*(auto val : suffix)//标记1
        {
            cout << val << " ";
        }
        cout << endl;
        */
    }

    while(!op.empty())
    {
        if (op.top() == "(") {
            cout << "ILLEGAL: Mismatched parentheses" << endl;//标记2
            return {};
        }
        suffix.push_back(op.top());
        op.pop();
    }
    return suffix;
}


inline void calc_op(float &x1,float &x2,string &op,stack<float> &stk, int &flag)
{
    switch (op[0])
    {
    case '+':
        stk.push(x1 + x2);
        break;
    case '-':
        stk.push(x1 - x2);
        break;
    case '*':
        stk.push(x1 * x2);
        break;
    case '/':
        if(x2 == 0)
        {
            cout << "ILLEGAL" << endl;
            flag = 0;
        }
        else stk.push(x1 / x2);
        break;
    }
}

/**
 * 计算后缀表达式
 */
inline void calculate(vector<string> &suffix,int &flag)
{
    stack<float> calc_stk;

    //cout << "Step 4" << endl;
    
    for(int i = 0 ; i < suffix.size(); ++i)
    {
        if(flag == 0) break;

        if(type(suffix[i][0]) == 0)
        {
            float right = calc_stk.top();
            calc_stk.pop();
            float left = calc_stk.top();
            calc_stk.pop();
            calc_op(left,right,suffix[i],calc_stk,flag);
            continue;
        } 
        else
        {
            calc_stk.push(stof(suffix[i]));
        }
    }

    //cout << flag << endl;
    if (flag == 1 && calc_stk.size()==1)
    {
        float result = calc_stk.top();
        cout << result << endl; 
    }
    else cout<<"ILLEGAL"<<endl;
}










