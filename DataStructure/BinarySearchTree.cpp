#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
 * 二叉搜索树:
 * 1. 一个节点的左子树只包含节点key值小于当前节点的节点
 * 2. 一个节点的右子树只包含节点key值大于当前节点的节点
 * 3. 左右子树必须也是一个二叉搜索树
 * 4. 不能存在重复的节点
 */

struct Node
{
    int key;
    Node *left;
    Node *right;

    Node() : key(-1), left(NULL), right(NULL) {}
    Node(int key) : key(key), left(NULL), right(NULL) {}
};


//搜索操作
Node *search(Node *root, int key)
{
    if (root == NULL)
    {
        return root;
    }

    if (root->key == key)
    {
        return root;
    }
    else if (key > root->key)
    {
        return search(root->right, key);
    }
    else
    {
        return search(root->left, key);
    }
}

//插入操作
Node *insert(Node *root, int key)
{
    if (root == NULL)
    {
        return new Node(key);
    }

    if (key < root->key)
    {
        root->left = insert(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = insert(root->right, key);
    }

    return root;
}

//删除操作
//1. 删除的节点是叶子节点
//2. 删除的节点只有一个孩子
//3. 删除的节点有两个孩子
Node *deleteNodeHelp(Node *root, Node *&proot, int key)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->key > key)
    {
        return deleteNodeHelp(root->left, root->left, key);
    }
    else if (root->key < key)
    {
        return deleteNodeHelp(root->right, root->right, key);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            proot = NULL;
        }
        else if (root->left == NULL || root->right == NULL)
        {
            proot = root->left == NULL ? root->right : root->left;
        }
        else
        {
            //找到root的下一个节点
            Node *successor = root->right, *psuccessor = root;
            while (successor->left != NULL)
            {
                psuccessor = successor;
                successor = successor->left;
            }

            successor->left = root->left;
            if (psuccessor != root)
            {
                psuccessor->left = successor->right;
                successor->right = root->right;
            }
            proot = successor;
        }
        delete root;
        return proot;
    }
}

Node *deleteNode(Node *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    Node *proot = NULL;
    return deleteNodeHelp(root, proot, key);
}

//最小节点
Node *minimum(Node *root)
{
    while (root != NULL && root->left != NULL)
    {
        root = root->left;
    }

    return root;
}

//最大节点
Node *maxmum(Node *root)
{
    while (root != NULL && root->right != NULL)
    {
        root = root->right;
    }

    return root;
}

//中序遍历的前缀节点
Node *predecessor(Node *root)
{
    Node *current = root->left;
    while (current != NULL && current->right != NULL)
    {
        current = current->right;
    }

    return current;
}

//中序遍历的后缀节点
//这样实现存在问题
Node *successor(Node *root)
{
    Node *current = root->right;
    while (current != NULL && current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

//检测一个二叉树是否是二叉搜索树
//错误的实现
/*
bool isBST(Node *root)
{
    bool result = true;
    if (root->left != NULL)
    {
        result = result && root->left->key < root->key && isBST(root->left);
    }

    if (result && root->right != NULL)
    {
        result = result && root->right->key > root->key && isBST(root->right);
    }

    return result;
}
*/

//可以选择使用迭代版本的中序遍历
bool isBST(Node *root)
{
    //使用一个辅助函数的方式更好
    static Node *prev = NULL;
    if (root)
    {
        if (isBST(root->left) == false)
        {
            return false;
        }

        if (prev != NULL && prev->key >= root->key)
        {
            return false;
        }

        if (isBST(root->right) == false)
        {
            return false;
        }
    }

    return true;
}

//打印二叉搜索树上第k大的数
void printKthNode(Node *root, int k)
{
    if (root == NULL)
    {
        return ;
    }

    printKthNode(root->right, k);

    //检测node位置进行打印

    printKthNode(root->left, k);
}

void printInorder(Node *root)
{
    if (root == NULL)
    {
        return ;
    }

    printInorder(root->left);
    cout << root->key << " ";
    printInorder(root->right);
}

int main()
{
    Node *root = NULL;
    int data[] = {10, 11, 12, 2, 5, 3, 7, 1, 9, 6};
    int len = sizeof(data) / sizeof(data[0]);
    for (int i = 0; i < len; ++i)
    {
        root = insert(root, data[i]);
    }

    printInorder(root);
    cout << endl;
    deleteNode(root, 11);
    printInorder(root);

    cout << endl;

    cout << "minimum: " << minimum(root)->key << endl;
    cout << "maxmum: " << maxmum(root)->key << endl;
    cout << "predecessor: " << predecessor(root)->key << endl;
    cout << "successor: " << successor(root)->key << endl;
    cout << "isBST: " << isBST(root) << endl;
}
