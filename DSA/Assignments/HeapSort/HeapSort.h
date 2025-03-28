#pragma once

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

template <typename T>
/**
 * @brief 下滤操作
 * @param i 下滤的起点
 * @param n 下滤终点
 */
inline void percolatedown(vector<T> & vec, int i ,int n)
{
    int child = i;
    T tmp;

    for(tmp = std::move(vec[i]) ; 2*i+1 < n ; i = child ) 
    {
        child = 2*child +1;//左孩子
        if(child < n-1 && vec[child] < vec[child +1])
            ++child;
        if(tmp < vec[child])
            vec[i]=std::move(vec[child]);
        else break;
    }
    vec[i] = std::move(tmp);
}

template <typename T>
/**
 * @brief 创建大顶堆，即堆顶为元素最大值
 */
inline void BuildHeap(vector<T> &vec)
{
    for(int i = vec.size()/2-1;i >= 0;--i)
        percolatedown(vec,i,vec.size());
}


template <typename T>
/**
 * @brief 将堆进行排序
 */
inline void Sort(vector<T> &vec)
{
    for(int i = vec.size()-1 ; i >0 ; --i)
    {
        swap(vec[0],vec[i]);
        percolatedown(vec,0,i);
    }
}

template <typename T>
inline void Heapsort(vector<T> &vec)
{
    BuildHeap(vec);
    Sort(vec);
    return;
}

