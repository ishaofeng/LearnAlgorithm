#include <iostream>
#include <queue>
#include <stack>
using namespace std;

//数据结构
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int data) : data(data), left(NULL), right(NULL) {}
};

//计算一颗数叶子节点的数量
int getTreeLeafCount(Node *root)
{
    if (NULL == root)
    {
        return 0;
    }

    if (NULL == root->left && NULL == root->right)
    {
        return 1;
    }


    return getTreeLeafCount(root->left) + getTreeLeafCount(root->right);
}

//螺旋形状遍历打印树结构
int treeHeight(Node *root)
{
    if (NULL == root)
    {
        return 0;
    }

    if (NULL == root->left && NULL == root->right)
    {
        return 1;
    }

    return 1 + max(treeHeight(root->left), treeHeight(root->right));
}
void printSpiralLevel(Node *root, int level, bool bOdd)
{
    if (NULL == root)
    {
        return ;
    }

    if (0 == level)
    {
        cout << root->data << " ";
    }
    else
    {
        if (bOdd)
        {
            printSpiralLevel(root->right, level - 1, bOdd);
            printSpiralLevel(root->left, level - 1, bOdd);
        }
        else
        {
            printSpiralLevel(root->left, level - 1, bOdd);
            printSpiralLevel(root->right, level - 1, bOdd);
        }
    }
}

//时间复杂度为O(n^2)
void printSpiral(Node *root)
{
    if (NULL == root)
    {
        return ;
    }

    int height = treeHeight(root);
    for (int i = 0; i < height; ++i)
    {
        printSpiralLevel(root, i, (i + 1) % 2 == 1);
    }

    cout << endl;
}

void printSpiral_2(Node *root)
{
    if (NULL == root)
    {
        return ;
    }

    stack<Node *> q;
    stack<Node *> s;

    q.push(root);

    Node *current = NULL;
    while (q.empty() == false || s.empty() == false)
    {
        //当前处理层为正序层
        if (q.empty() == false)
        {
            while (!q.empty())
            {
                current  = q.top();
                cout << current->data << " ";

                if (current->right != NULL)
                {
                    s.push(current->right);
                }
                if (current->left != NULL)
                {
                    s.push(current->left);
                }

                q.pop();
            }
        }
        else //当前处理层为逆序层
        {
            while (!s.empty())
            {
                current = s.top();
                cout << current->data << " ";

                if (current->left != NULL)
                {
                    q.push(current->left);
                }
                if (current->right != NULL)
                {
                    q.push(current->right);
                }

                s.pop();
            }
        }
    }

    cout << endl;
}

int main()
{
    Node *root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(6);
    root->left->left = new Node(1);
    root->left->right = new Node(3);
    root->right->left = new Node(5);

    cout << "树的叶子节点数为: " << getTreeLeafCount(root) << endl;
    cout << "树的高度: " << treeHeight(root) << endl;

    cout << "螺旋打印: ";
    printSpiral(root);

    cout << "螺旋打印 2: ";
    printSpiral_2(root);

    return 0;
}
