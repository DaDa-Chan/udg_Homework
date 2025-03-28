#include <iostream>  
#include <cstring> // 为了使用strcpy和strlen  
  
using namespace std;  
  
class Chicken {  
private:  
    int age = 24;  
    char *name = nullptr;  
  
public:  
    Chicken() {}  
    Chicken(int _age) : age(_age) {}  
    Chicken(int _age, const char *_name) : age(_age) {  
        int len = strlen(_name) + 1; 
        name = new char[len];  
        strcpy(name, _name); 
    }  
    ~Chicken() {  
        if (name != nullptr)  
            delete[] name;  
    }  
    //深度复制
    Chicken(const Chicken& other) : age(other.age), name(nullptr) {  
        if (other.name != nullptr) {  
            int len = strlen(other.name) + 1;  
            name = new char[len];  
            strcpy(name, other.name);  
        }  
    }
    //连续赋值
    Chicken& operator=(const Chicken& other) {  
        if (this != &other) { // 避免自赋值  
            age = other.age; // 复制年龄  
            if (name != nullptr) {  
                delete[] name;  
                name = nullptr;  
            }  
            if (other.name != nullptr) {  
                int len = strlen(other.name) + 1;  
                name = new char[len];  
                strcpy(name, other.name);  
            }  
        }  
        return *this;   
    }  
    void setAge(int _age) {  
        age = _age;  
    }  
    void setName(const char *_name) {  
        if(name != nullptr)  
            delete[] name; 
            name = nullptr; 
        int len = strlen(_name) + 1;  
        name = new char[len];  
        strcpy(name, _name); 
    }  
  
    const char *getName() const {  
        return name;  
    }  
  
    const int &getAge() const {  
        return age;  
    }  
};  
  
int main() {  
    Chicken c(24, "Kunkun");  
    cout << "Hi, everyone! My name is " << c.getName() << ", I am " << c.getAge() << " years old." << endl;  
    return 0;  
}  