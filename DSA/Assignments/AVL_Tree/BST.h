/**
 * @file BST.h 
 * @author M. A. Weiss (you@domain.com)
 * @brief 课本代码的注释和改进
 * @version 0.1
 * @date 2024-10-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <algorithm>
#include<string>
using namespace std;

/// 临时性的异常类，用于表示树为空的异常
class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

/**
 * @brief 二叉搜索树模板类
 * 
 * @tparam Comparable 模板参数，表示树中存储的元素类型
 */
template <typename Comparable>
class BinarySearchTree
{
public:
    /**
     * @brief 默认构造函数
     * 
     * 初始化一个空的二叉搜索树。
     */
    BinarySearchTree() : root{ nullptr } {}

    /**
     * @brief 拷贝构造函数
     * 
     * 创建一个新树，它是给定树的深拷贝。这里相比课本代码，引用更直接，有利于编译器优化。
     * 
     * @param rhs 要拷贝的二叉搜索树
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}

    /**
     * @brief 移动构造函数
     * 
     * 将给定树的资源转移到新树中。这里 noexcept 用于指示该函数不会抛出异常。
     * 因为移动构造不涉及内存分配，所以不会抛出异常。这里显式声明 noexcept 是为了提高性能。
     * 让编译器知道这个函数不会抛出异常，从而优化代码。
     * 
     * @param rhs 要移动的二叉搜索树
     */
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }

    /**
     * @brief 析构函数
     * 
     * 释放树中所有节点占用的内存。
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * @brief 查找并返回树中的最小元素
     * 
     * 这是一个公有接口，它调用了私有的递归函数。
     * 
     * @return 最小元素的引用
     */
    const Comparable &findMin() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    /**
     * @brief 查找并返回树中的最大元素
     * 
     * @return 最大元素的引用
     */
    const Comparable &findMax() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    /**
     * @brief 检查树中是否包含指定的元素
     * 
     * @param x 要查找的元素
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    /**
     * @brief 检查树是否为空
     * 
     * @return 如果树为空，则返回 true；否则返回 false
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * @brief 打印树的结构
     * 
     * 将树的结构输出到指定的输出流，默认输出到标准输出流。
     * 
     * @param out 输出流，默认为 std::cout
     */
    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    /**
     * @brief 清空树中的所有元素
     * 
     * 释放树中所有节点占用的内存，使树变为空。
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * @brief 插入一个常量引用元素到树中
     * 
     * @param x 要插入的元素
     */
    void insert(const Comparable &x) {
        insert(x, root);
    }

    /**
     * @brief 插入一个右值引用元素到树中
     * 
     * @param x 要插入的元素
     */
    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    /**
     * @brief 从树中移除指定的元素
     * 
     * @param x 要移除的元素
     */
    void remove(const Comparable &x) {
        remove(x, root);
    }

    /**
     * @brief 拷贝赋值运算符
     * 
     * 将一个树的资源拷贝到当前树中。对自赋值进行了排除。
     * 
     * @param rhs 要拷贝的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
    if (this != &rhs) {
        BinarySearchTree temp(rhs);
        std::swap(root, temp.root);
    }
    return *this;
}


    /**
     * @brief 移动赋值运算符
     * 
     * 将一个树的资源移动到当前树中。
     * 
     * @param rhs 要移动的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }
    void inorderTraversal() {
        inorder(root);
    }

    void drawTree()
    {
        drawTree(root,0,false);
    }
        void DrawTree(std::ostream &out = std::cout) const {
        // 调用受保护的 DrawTree 函数，从根节点开始打印
        DrawTree(root, out);
    }

protected:
    /**
     * @brief 二叉树节点结构体
     */
    struct BinaryNode
    {
        Comparable element;  ///< 节点存储的元素
        BinaryNode *left;    ///< 左子节点指针
        BinaryNode *right;   ///< 右子节点指针
        int        height;   ///< 高度

        /**
         * @brief 构造函数，接受常量引用
         * 
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, int h = 0)
            : element{ theElement }, left{ lt }, right{ rt } ,height{ h } { }

        /**
         * @brief 构造函数，接受右值引用
         * 
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt,int h = 0)
            : element{ std::move(theElement) }, left{ lt }, right{ rt } ,height{ h } { }
    };

    BinaryNode *root;  ///< 树的根节点指针

    /**
     * @brief 递归查找最小元素
     * 
     * @param t 当前节点指针
     * @return 最小元素所在的节点指针
     */
    BinaryNode *findMin(BinaryNode *t) const {
        /// 从一个空节点开始查找，返回空指针                
        if (t == nullptr) {
            return nullptr;
        }
        /// 向左无路了，当前节点就是最小元素
        if (t->left == nullptr) {
            return t;
        }
        /// 否则继续向左查找
        return findMin(t->left);
    }

    /**
     * @brief 递归查找最大元素
     * 
     * @param t 当前节点指针
     * @return 最大元素所在的节点指针
     */
    BinaryNode *findMax(BinaryNode *t) const {
        /// 这里没有使用递归，而是使用循环，更高效
        /// findMin 也可以改成循环实现
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    /**
     * @brief 递归检查树中是否包含指定的元素
     * 
     * @param x 要查找的元素
     * @param t 当前节点指针
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x, BinaryNode *t) const {
        /// 这是递归版本，也可以有循环版本
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } 
        else if (x > t->element) {
            return contains(x, t->right);
        } 
        else {
            return true;  // 找到元素
        }
    }

    /**
     * @brief 递归打印树的结构
     * 
     * @param t 当前节点指针
     * @param out 输出流
     */
    void printTree(BinaryNode *t, std::ostream &out) const {
        /// 中序遍历
        if (t != nullptr) {
            printTree(t->left, out);  // 先打印左子树
            out << t->element << std::endl;  // 打印当前节点
            printTree(t->right, out);  // 再打印右子树
        }
    }

    /**
     * @brief 递归清空树中的所有元素
     * 
     * @param t 当前节点指针
     */
    void makeEmpty(BinaryNode * &t) {
        /// 这必须是一个后序遍历，为什么？
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            /// delete 并不会自动将指针置空，这里需要手动置空
            t = nullptr;
        }
    }

    /**
     * @brief 递归插入一个常量引用元素到树中
     * 
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(const Comparable &x, BinaryNode * &t) {
        /// 这句话乍一看不可思异，怎么能对一个空指针赋值呢？
        /// 但是这里是引用，所以实际上是对指针 t 的引用，t 现在存了 nullptr, 
        /// 所以可以修改指针 t 的值
        if (t == nullptr) {
            /// 创建一个新节点，包含 x 的值，左右子节点为空
            /// 挂在 t 指向的节点上
            /// 而在递归过程中，t 总是会指向父节点的左子节点或右子节点
            /// 所以这里实际上是将新节点挂在父节点的左子节点或右子节点上
            t = new BinaryNode{x, nullptr, nullptr};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        } else {
            /// 如果元素已存在，则不进行插入
            /// 这种情况不可遗漏，严格的规则中也可以抛出异常
        }
        balance(t);
    }

    /**
     * @brief 递归插入一个右值引用元素到树中
     * 
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(Comparable &&x, BinaryNode * &t) {
        /// 一样的逻辑
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        } else {
            // 如果元素已存在，则不进行插入
        }

        balance(t);
    }

    /**
     * @brief 递归从树中移除指定的元素
     * 
     * @param x 要移除的元素
     * @param t 当前节点指针
     */
    void remove(const Comparable &x, BinaryNode * &t) 
    {
        if(!t) return;//如果t为空节点

        BinaryNode* par = nullptr; // 父节点的指针
        BinaryNode* cur = t;

        // 找到要删除的节点和它的父节点
        while (cur != nullptr && cur->element != x) 
        {
            par = cur;
            if (x < cur->element) {
                cur = cur->left;
            } else {
               cur = cur->right;
            }
        }
        if(!cur) return;
        if(!(cur ->left) || !(cur -> right))//要删除的节点至多只有一个child节点
        {
            if(!par)//如果删除根节点
            {
                t = (cur -> left)? cur->left : cur->right;//修改根节点
            }
            if(par -> left == cur)//t是par的左节点
            {
                par -> left = (cur -> left)? cur->left : cur->right;
            }else//cur is parent's right
            {
                par -> right = (cur -> left)? cur->left : cur->right;
            }
            delete cur;
            cur =nullptr;
        }else//有两个child节点
        {
            BinaryNode* min = detachMin(cur->right);

            min -> left = cur -> left;// 将当前节点的左子树链接到后继节点
            min -> right = cur -> right;// 将当前节点的右子树链接到后继节点
            if(!par)//如果删除根节点
            {
                t = min;//修改根节点
            }
            else if(par -> left == cur)//cue是par的左节点
            {
                par -> left = min;// 父节点指向后继节点
            }else//cur是右节点
            {
                par -> right = min;// 父节点指向后继节点
            }
            delete cur;
            cur = nullptr;
        }

        while (par != nullptr) 
        {
            int oldHeight = par->height; // 记录平衡前的高度
            balance(par); // 调整 cur 的平衡
            par->height = max(height(par->left), height(par->right)) + 1; // 更新 cur 的高度

            if (par->height == oldHeight) break; // 如果高度没有变化，提前停止

            par = findParent(t,par -> element);
        }
    }
    BinaryNode* findParent(BinaryNode* &subroot, const Comparable &x)
    {
        if (subroot == nullptr || subroot->element == x) return nullptr; // 根节点为空或根节点即为目标节点

        BinaryNode* parent = nullptr;
        BinaryNode* cur = subroot;

        while (cur != nullptr && cur->element != x)
        {
            parent = cur;
            if (x < cur->element)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }
        if (cur == nullptr) return nullptr;//没有找到

        // 确保 parent 和 cur 的关系正确
        if ((parent->left == cur || parent->right == cur) && cur->element == x)
        {
        return parent;
        }

        return nullptr;
        
        //return (cur != nullptr) ? parent : nullptr; // 如果找到目标节点，返回父节点，否则返回 nullptr
    }



    /**
     * @brief 递归克隆树的结构
     * 
     * @param t 当前节点指针
     * @return 新的节点指针
     */
    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right),t->height};
    }
    /**
     * @brief 查找以 t 为根的子树中的最小节点，返回这个节点，并从原子树中删除这个节点
     * 
     * @param t 当前节点指针
     * @return 以t 为根的子树中的最小节点
     */
    BinaryNode* detachMin(BinaryNode *&t)
    {
        if(!t) return nullptr;

        if(!t ->left)//判断是否为叶子节点
        {
            BinaryNode* minNode = t;
            t = t->right;
            return minNode; 
        }
        else
        {
            return detachMin(t -> left);
        }
    }

    void inorder(BinaryNode* node) {
        if (node) {
            inorder(node->left);
            std::cout << node->element << " ";
            inorder(node->right);
        }
    }

    void drawTree(BinaryNode* node, int space , bool isLeft) {
        if (!node) return;

        space += 10; // 增加空间以便于显示

        // 先打印右子树
        drawTree(node->right, space , false);

        // 打印当前节点
        std::cout << std::endl;
        for (int i = 10; i < space; i++) {
            std::cout << ' '; // 输出空格
        }

        if (isLeft) {
            std::cout << " \\"; // 左子树的枝
        } else if (space > 10) {
            std::cout << " / "; // 右子树的枝
        }

        std::cout << " " << node->element << "\n"; // 打印节点值

        // 打印左子树
        drawTree(node->left, space , true);
    }

    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( BinaryNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ){


            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        }
        
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
        {
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
        }
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

        void rotateWithLeftChild( BinaryNode * & k2 )
    {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( BinaryNode * & k1 )
    {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( BinaryNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( BinaryNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }

    int height( BinaryNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }
    void DrawTree(BinaryNode *t, std::ostream &out, std::string prePrint = "", int numofChild = 1, bool noBrother = 1) const {
        // 根节点输出 "root"
        if (t == this->root) {
            out << "root" << std::endl;
        }

    // 当前节点非空则输出数据
        if (t != nullptr) {
            DrawTree(t->left, out, prePrint + (numofChild < 1 ? "    " : "│   "), 0, t->right == nullptr);
        
            // 打印前导输出
            out << prePrint
                // 判断当前节点是否是最后一个子节点，输出不同的枝杈
                << (numofChild < 1 ? "┌───" : "└───")
                << t->element
                << std::endl;

        // 判断当前节点是否是最后一个子节点，添加不同的前导输出
        // 判断是否有兄弟节点
            DrawTree(t->right, out, prePrint + (numofChild < 1 ? "│   " : "    "), 1, t->left == nullptr);
        }
    // 若当前节点为空但有兄弟节点，输出 #
        else if (!noBrother) {
            out << prePrint << (numofChild < 1 ? "┌───" : "└───") << "#" << std::endl;
        }
    }




};

