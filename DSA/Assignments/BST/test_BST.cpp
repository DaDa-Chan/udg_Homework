#include <iostream>
#include "BST.h"  // 假设 BinarySearchTree 类定义在这个头文件中
using namespace std;

void testBinarySearchTree() {
    BinarySearchTree<int> bst;

    // 测试插入功能
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
/*
    // 测试打印树结构
    std::cout << "Initial Tree:" << std::endl;
    bst.printTree();

    // 测试查找最小和最大元素
    std::cout << "Minimum element: " << bst.findMin() << std::endl;
    std::cout << "Maximum element: " << bst.findMax() << std::endl;

    // 测试 contains 功能
    std::cout << "Contains 7? " << (bst.contains(7) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 20? " << (bst.contains(20) ? "Yes" : "No") << std::endl;
*/
    // 测试删除功能
    std::cout << "before any deletions: ";
    bst.drawTree();

    // 删除叶子节点
    cout << "\nDeleting leaf node (20): ";
    bst.remove(20);
    bst.drawTree();

    // 删除只有一个子节点的节点
    cout << "\nDeleting node with one child (30): ";
    bst.remove(30);
    bst.drawTree();

    // 删除具有两个子节点的节点
    cout << "\nDeleting node with two children (50): ";
    bst.remove(50);
    bst.drawTree();

    cout<<endl;
    // 测试清空树
    bst.makeEmpty();
    cout << "Tree after making empty:" << std::endl;
    bst.printTree();
/*
    // 测试是否为空
    cout << "Is tree empty? " << (bst.isEmpty() ? "Yes" : "No") << std::endl;

    cout<<endl;
    // 测试拷贝构造函数和赋值运算符
    BinarySearchTree<int> bst2;
    bst2.insert(1);
    bst2.insert(3);
    bst2.insert(2);

    BinarySearchTree<int> bst3(bst2);
    std::cout << "Copied Tree (bst3):" << std::endl;
    bst3.printTree();

    BinarySearchTree<int> bst4;
    bst4 = bst2;
    std::cout << "Assigned Tree (bst4):" << std::endl;
    bst4.printTree();

    // 测试移动构造函数和移动赋值运算符
    BinarySearchTree<int> bst5(std::move(bst2));
    std::cout << "Moved Tree (bst5):" << std::endl;
    bst5.printTree();

    BinarySearchTree<int> bst6;
    bst6 = std::move(bst5);
    std::cout << "Move Assigned Tree (bst6):" << std::endl;
    bst6.printTree();

    BinarySearchTree<int> bst7;
    bst7.findMax();  // 测试异常处理
*/
}

int main() {
    testBinarySearchTree();
    return 0;
}