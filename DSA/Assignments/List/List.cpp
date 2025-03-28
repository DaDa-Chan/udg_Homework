#include "List.h"  
#include <iostream>  
#include <string>  
  
using namespace std;  
  
int main() {  
    // 测试构造函数和基本操作  
    cout << "Testing default constructor and push_back:" << endl;  
    List<int> list1;  
    for (int i = 1; i <= 5; ++i) {  
        list1.push_back(i);  
    }  
    list1.printlist();  // 输出应为 1 2 3 4 5  
    cout<<"list1's size is:"<<list1.size()<<endl;
    cout<<"list1's the first value is:"<<list1.front()<<endl;
    cout<<"list1's the last value is:"<<list1.back()<<endl;


    // 测试初始化列表构造函数  
    cout << "Testing initializer list constructor:" << endl;  
    List<int> list2 {10, 20, 30, 40, 50};  
    list2.printlist();  // 输出应为 10 20 30 40 50  
  
    // 测试拷贝构造函数  
    cout << "Testing copy constructor:" << endl;  
    List<int> list3 = list2;  
    list3.printlist();  // 输出应为 10 20 30 40 50  
  
    // 测试移动构造函数  
    cout << "Testing move constructor:" << endl;  
    List<int> list4 = std::move(list3);  
    list4.printlist();  // 输出应为 10 20 30 40 50  
    cout << "After move, list3 is " << (list3.empty() ? "empty" : "not empty") << endl;  // 应为空  
  
    // 测试移动赋值运算符
    cout << "Testing move assignment operator:" << endl;  
    List<int> list5;  
    list5 = std::move(list4);  
    list5.printlist();  // 输出应为 10 20 30 40 50  
    cout << "After move assignment, list4 is " << (list4.empty() ? "empty" : "not empty") << endl;  // 应为空  
  
    // 测试赋值运算符  
    cout << "Testing assignment operator:" << endl;  
    list1 = list2;  
    list1.printlist();  // 输出应为 10 20 30 40 50  
  
    // 测试push_front, pop_back, pop_front  
    cout << "Testing push_front, pop_back, and pop_front:" << endl;  
    list1.push_front(0);  
    list1.pop_back();  
    list1.pop_front();  
    list1.printlist();  // 输出应为 10 20 30 40  
  
    // 测试插入和删除  
    cout << "Testing insert and erase:" << endl;  
    auto it = list1.begin();  
    ++it;  // 指向 20  
    list1.insert(it, 15);  // 在 20 前插入 15  
    list1.printlist();  // 输出应为 10 15 20 30  
    list1.erase(it);  // 删除 20  
    list1.printlist();  // 输出应为 10 15 30  
  
    // 测试范围删除  
    cout << "Testing range erase:" << endl;  
    list1.insert(list1.end(), 20);  
    list1.insert(list1.end(), 30);  
    list1.printlist();  // 输出应为 10 15 30 20 30  
    it = list1.begin();  
    ++it;  // 指向 15  
    auto it2 = list1.end();    
    list1.erase(it, it2);  
    list1.printlist();  // 输出应为 10  
  
    // 测试反转  
    cout << "Testing reverse:" << endl;  
    list1.push_back(10);  
    list1.push_back(20);  
    list1.push_back(30);  
    list1.printlist();  // 输出应为 10 10 20 30  
    list1.reverse();  
    list1.printlist();  // 输出应为 30 20 10 10  
  
    // 测试remove_all  
    cout << "Testing remove_all:" << endl;  
    list1.remove_all(10);  
    list1.printlist();  // 输出应为 30 20  
  
    return 0;  
}  