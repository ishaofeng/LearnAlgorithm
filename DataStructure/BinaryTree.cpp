#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
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

//二叉树的直径: 一颗树上叶子节点之间的最长路径的节点个数
//问题分解:
//  1. 最大直径在左子树上
//  2. 最大直径在右子树上
//  3. 最大直径通过根节点（左子树高度 + 右子树高度 + 1)
int diameterOfBinaryTree(Node *root)
{
    if (NULL == root)
    {
        return 0;
    }

    int diameterLeft = diameterOfBinaryTree(root->left);
    int diameterRight = diameterOfBinaryTree(root->right);
    int diameterRoot = treeHeight(root->left) + treeHeight(root->right) + 1;

    return max(max(diameterLeft, diameterRight), diameterRoot);
}

//检测一个二叉树是否是高度平衡的
//时间复杂度为O(n^2)
bool checkTreeHeightBalanced(Node *root)
{
    if (NULL == root)
    {
        return true;
    }

    int lh = treeHeight(root->left);
    int rh = treeHeight(root->right);
    if (abs(lh - rh) > 1)
    {
        return false;
    }

    return checkTreeHeightBalanced(root->left) && checkTreeHeightBalanced(root->right);
}
//时间复杂度为O(n)在递归过程中直接计算树的高度
bool checkTreeHeightBalanced2(Node *root, int *height)
{
    if (NULL == root)
    {
        *height = 0;
        return 1;
    }

    int hl = 0, hr = 0;
    bool cl = checkTreeHeightBalanced2(root->left, &hl);
    bool cr = checkTreeHeightBalanced2(root->right, &hr);

    *height = max(hl, hr) + 1;
    if (abs(hl - hr) > 1)
    {
        return 0;
    }

    return cl && cr;
}

//不使用递归的中序遍历树
void InorderTravel(Node *root)
{
    if (NULL == root)
    {
        return ;
    }

    stack<Node *> s;
    Node *current = root;

    while (current != NULL)
    {
        s.push(current);
        current = current->left;
    }

    while (!s.empty())
    {
        current = s.top();
        s.pop();

        cout << current->data << " ";

        current = current->right;
        while (current != NULL)
        {
            s.push(current);
            current = current->left;
        }
    }

    cout << endl;
}

//不使用递归也不使用栈中序遍历树 ***
void MorrisTravel(Node *root)
{
    if (NULL == root)
    {
        return ;
    }

    Node *current, *pre;
    while (current != NULL)
    {
        if (NULL == current->left)
        {
            cout << current->data << " ";
            current = current->right;
        }
        else
        {
            pre = current->left;
            while (pre->right != NULL && pre->right != current)
            {
                pre = pre->right;
            }

            if (NULL == pre->right)
            {
                pre->right = current;
                current = current->left;
            }
            else
            {
                pre->right = NULL;
                cout << current->data << " ";
                current = current->right;
            }
        }
    }
}

//从先序遍历和中序遍历构造树
Node *buildTreeFromPreorderAndInorder(int inorder[], int preorder[], int len)
{
    if (NULL == inorder || NULL == preorder || len <= 0)
    {
        return NULL;
    }

    Node *root = new Node(preorder[0]);
    if (len != 1)
    {
        int rootIndex = -1;
        for (int i = 0; i < len; ++i)
        {
            if (inorder[i] == preorder[0])
            {
                rootIndex = i;
                break;
            }
        }

        Node *left = buildTreeFromPreorderAndInorder(inorder, preorder + 1, rootIndex);
        Node *right = buildTreeFromPreorderAndInorder(inorder + rootIndex + 1, preorder + 1 + rootIndex, len - rootIndex -1);

        root->left = left;
        root->right = right;
    }

    return root;
}


int main()
{
    Node *root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(6);
    root->left->left = new Node(1);
    root->left->right = new Node(3);
    root->right->left = new Node(5);
    root->left->left->left = new Node(7);
    root->left->left->left->left = new Node(8);

    cout << "树的叶子节点数为: " << getTreeLeafCount(root) << endl;
    cout << "树的高度: " << treeHeight(root) << endl;

    cout << "螺旋打印: ";
    printSpiral(root);

    cout << "螺旋打印 2: ";
    printSpiral_2(root);

    cout << "二叉树直径: " << diameterOfBinaryTree(root) << endl;

    cout << "检测二叉树高度是否平衡: " << checkTreeHeightBalanced(root) << endl;
    int height = 0;
    cout << "检测二叉树高度是否平衡: " << checkTreeHeightBalanced2(root, &height) << endl;

    cout << "中序遍历: ";
    InorderTravel(root);

    int inorder[] = {8, 7, 1, 2, 3, 4, 5, 6};
    int preorder[] = {4, 2, 1, 7, 8, 3, 6, 5};
    Node *tree = buildTreeFromPreorderAndInorder(inorder, preorder , 8);

    cout << "中序遍历: ";
    InorderTravel(tree);


    return 0;
}
