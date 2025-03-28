#include"HeapSort.h"

#include<random>
#include <chrono>

using namespace std;

const int SIZE = 1000000;

// 创建随机序列
vector<int> RandomSeq() 
{
    vector<int> sequence(SIZE);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000000);  // 生成1到1000000之间的随机数

    for (int i = 0; i < SIZE; ++i) {
        sequence[i] = dis(gen);
    }
    return sequence;
}

// 创建有序序列（递增）
vector<int> OrderedSeq() {
    vector<int> sequence(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        sequence[i] = i + 1;  // 顺序填充1到SIZE
    }
    return sequence;
}

// 创建逆序序列（递减）
vector<int> ReverseSeq() {
    vector<int> sequence(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        sequence[i] = SIZE - i;  // 填充SIZE到1
    }
    return sequence;
}

// 创建部分元素重复序列
vector<int> RepetitiveSeq() {
    vector<int> sequence(SIZE);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 500000);  // 生成1到500000之间的随机数

    // 随机生成大部分元素
    for (int i = 0; i < SIZE; ++i) {
        sequence[i] = dis(gen);
    }

    // 随机重复一些元素
    uniform_int_distribution<> disRepeat(0, SIZE - 1);
    for (int i = 0; i < SIZE / 10; ++i) {  // 重复10%的元素
        int index = disRepeat(gen);
        sequence[i] = sequence[index];
    }

    return sequence;
}


// 测量运行时间的模板函数
template <typename Func>
long long measureTime(Func func, std::vector<int>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    func(data);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}


void check(vector<int> &vec1,vector<int> &vec2)
{
    int flag = 1;
    BuildHeap(vec1);
    std::cout << "Heapsort: " << measureTime(Sort<int>, vec1) << " ms\n";
    make_heap(vec2.begin(),vec2.end());
    std::cout << "sort_heap: " << measureTime([](std::vector<int>& data) {std::sort_heap(data.begin(), data.end());}, vec2) << " ms\n";
    for(int i = 0; i<vec1.size() ; ++i)
    {
        if(vec1[i] != vec2[i]) 
            cout << "Error!" << endl;
            flag = 0;
            break;
    } 
    if(flag == 1) cout << "PASS!" << endl;
}

int main() {
    // 创建四种序列
    vector<int> randomSeq = RandomSeq();
    vector<int> orderedSeq = OrderedSeq();
    vector<int> reverseSeq = ReverseSeq();
    vector<int> repetitiveSeq = RepetitiveSeq();

    vector<int> oldrandomSeq = randomSeq;
    vector<int> oldorderedSeq = orderedSeq;
    vector<int> oldreverseSeq = reverseSeq;
    vector<int> oldrepetitiveSeq = repetitiveSeq;

    cout << "Test RandomSeq:" << endl;
    check(randomSeq,oldrandomSeq);
    
    cout << endl;

    cout << "Test orderedSeq:" << endl;
    check(orderedSeq,oldorderedSeq);

    cout << endl;

    cout << "Test reverseSeq:" << endl;
    check(reverseSeq,oldreverseSeq);

    cout << endl;

    cout << "Test repetitiveSeq:" << endl;
    check(repetitiveSeq,oldrepetitiveSeq);


    return 0;
}