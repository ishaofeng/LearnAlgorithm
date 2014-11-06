#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>
using namespace std;

//数据结构
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *nextRight;
    struct Node *next;

    Node(int data) : data(data), left(NULL), right(NULL), nextRight(NULL), next(NULL) {}
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

//DoubleTree
//将一个二叉树转换为DoubleTree, 每一个节点创建一个新节点作为原有节点的副本
Node *doubleTree(Node *root)
{
    if (NULL == root)
    {
        return root;
    }

    stack<Node *> s;

    Node *current = root;
    while (current != NULL)
    {
        s.push(current);
        current = current->left;
    }

    Node *duplicateNode = NULL;
    while (!s.empty())
    {
        current = s.top();
        s.pop();

        cout << current->data << endl;

        //添加新节点
        duplicateNode = new Node(current->data);
        duplicateNode->left = current->left;
        current->left = duplicateNode;

        current = current->right;
        while (current != NULL)
        {
            s.push(current);
            current = current->left;
        }
    }

   return root;
}

//求二叉树的最大宽度
//method1: 使用level travel
int getLevelWidth(Node *root, int level)
{
    if (NULL == root)
    {
        return 0;
    }

    if (0 == level)
    {
        return 1;
    }

    return getLevelWidth(root->left, level -1) + getLevelWidth(root->right, level - 1);
}
int getMaxWidthOftree(Node *root)
{
    if (NULL == root)
    {
        return 0;
    }

    int height = treeHeight(root);
    int maxWidth = -1, width;
    for (int i = 0; i < height; ++i)
    {
        width = getLevelWidth(root, i);
        if (maxWidth < width)
        {
            maxWidth = width;
        }
    }

    return maxWidth;
}

//method2: 使用先序遍历
void getMaxWidthOfTreeHelp(Node *root, int count[], int level)
{
    if (NULL == root || level < 0)
    {
        return ;
    }

    count[level]++;
    getMaxWidthOfTreeHelp(root->left, count, level + 1);
    getMaxWidthOfTreeHelp(root->right, count, level + 1);
}

int getMaxWidthOftree2(Node *root)
{
    if (NULL == root)
    {
        return 0;
    }

    int height = treeHeight(root);
    int *count = new int[height];
    memset(count, 0, sizeof(int) * height);

    getMaxWidthOfTreeHelp(root, count, 0);

    int maxWidth = -1;
    for (int i = 0; i < height; ++i)
    {
        if (count[i] > maxWidth)
        {
            maxWidth = count[i];
        }
    }

    delete [] count;

    return maxWidth;
}

//给定树上的一个节点获取该节点所在的层次
int getNodeLevelHelp(Node *root, int value, int level)
{
    if (NULL == root)
    {
        return 0;
    }
    if (root->data == value)
    {
        return level;
    }

    int nodelevel = getNodeLevelHelp(root->left, value, level + 1);
    if (nodelevel != 0)
    {
        return nodelevel;
    }

    return getNodeLevelHelp(root->right, value, level + 1);
}

int getNodeLevel(Node *root, int value)
{
    return getNodeLevelHelp(root, value, 1);
}

//给定一个节点，打印该节点的所有祖先节点
//method1: 自己写的 这个方法麻烦
int printNodeAncestorHelp(Node *root, int key, int *ancestor, int level)
{
    if (NULL == root)
    {
        return -1;
    }

    ancestor[level] = root->data;

    if (root->data == key)
    {
        return level;
    }

    int find = printNodeAncestorHelp(root->left, key, ancestor, level+1);
    if (find != -1)
    {
        return find;
    }

    return printNodeAncestorHelp(root->right, key, ancestor, level+1);
}

void printNodeAncestor(Node *root, int key)
{
    if (NULL == root)
    {
        return ;
    }

    int height = treeHeight(root);
    int *ancestor = new int[height];

    int find = printNodeAncestorHelp(root, key, ancestor, 0);
    if (find >= 0)
    {
        for (int i = 0; i < find; ++i)
        {
            cout << ancestor[i] << " ";
        }
    }
    else
    {
        cout << "no this node";
    }
    cout << endl;

    delete [] ancestor;
}

//method2:
bool printNodeAncestor2(Node *root, int key)
{
    if (NULL == root)
    {
        return false;
    }

    if (root->data == key)
    {
        return true;
    }

    if (printNodeAncestor2(root->left, key) || printNodeAncestor2(root->right, key))
    {
        cout << root->data << " ";
        return true;
    }
    else
    {
        return false;
    }
}

//检测一个二叉树是否是加和树
//加和树是指任意非叶子节点的值等于左右子树的值的加和
bool checkSumTreeHelp(Node *root, int *sum)
{
    if (NULL == root)
    {
        *sum = 0;
        return true;
    }

    int sumleft = 0, sumright = 0;
    if (checkSumTreeHelp(root->left, &sumleft) && checkSumTreeHelp(root->right, &sumright))
    {
        if ((sumleft + sumright) == root->data)
        {
            *sum = root->data << 1;
            return true;
        }
    }

    return false;
}

bool checkSumTree(Node *root)
{
    int sum;
    return checkSumTreeHelp(root, &sum);
}

//使用固定的额外空间连接同一层次的节点
//在数据结构Node上启用nextRight指针
void printConnectTree(Node *root)
{
    if (NULL == root)
    {
        return ;
    }

    queue<Node *> q;
    q.push(root);

    cout << "========PRINT CONNECT TREE========" << endl;
    Node *current = NULL;
    while (!q.empty())
    {
        current = q.front();
        q.pop();

        if (current->left != NULL)
        {
            q.push(current->left);
        }

        if (current->right != NULL)
        {
            q.push(current->right);
        }

        cout << current->data;
        if (NULL == current->nextRight)
        {
            cout << "  NULL" << endl;
        }
        else
        {
            cout << "  " << current->nextRight->data << "  #  ";
        }
    }
}

//method1: O(nlgn) 额外空间o(1)
void connectLevelNodeHelp(Node *root, int level, Node **prev)
{
    if (NULL == root)
    {
        return ;
    }

    if (0 == level)
    {
        if (*prev != NULL)
        {
            (*prev)->nextRight = root;
        }

        *prev = root;
    }
    else
    {
        connectLevelNodeHelp(root->left, level - 1, prev);
        connectLevelNodeHelp(root->right, level - 1, prev);
    }
}
Node *connectLevelNode(Node *root)
{
    if (NULL == root)
    {
        return root;
    }

    Node *prev = NULL;
    int height = treeHeight(root);
    for (int i = 0; i < height; ++i)
    {
        prev = NULL;
        connectLevelNodeHelp(root, i, &prev);
    }
}


//method2: time o(n)  space: o(lgn)
void connectLevelNodeHelp1(Node *root, int level, Node **prev)
{
    if (NULL == root)
    {
        return ;
    }

    if (prev[level] != NULL)
    {
        prev[level]->nextRight = root;
    }
    prev[level] = root;

    connectLevelNodeHelp(root->left, level + 1, prev);
    connectLevelNodeHelp(root->right, level + 1, prev);
}

Node *connectLevelNode1(Node *root)
{
    if (NULL == root)
    {
        return root;
    }

    int height = treeHeight(root);
    Node **prev = new Node*[height];
    memset(prev, 0, sizeof(Node*) * height);

    connectLevelNodeHelp(root, 0, prev);

    delete [] prev;

    return root;
}

//设置所有节点的next指向中序遍历的后续节点
void populateInorderTravel(Node *root, Node **prev)
{
    if (NULL == root)
    {
        return ;
    }

    populateInorderTravel(root->left, prev);

    if (*prev != NULL)
    {
        (*prev)->next = root;
    }
    *prev = root;

    populateInorderTravel(root->right, prev);
}

Node *populateInorderSuccessor(Node *root)
{
    if (NULL == root)
    {
        return root;
    }

    Node *prev = NULL;

    populateInorderTravel(root, &prev);
}

void printPopulateInorderSuccessor(Node *root)
{
    if (NULL == root)
    {
        return ;
    }

    printPopulateInorderSuccessor(root->left);

    cout << "Node: " << root->data << "   Next: ";
    if (root->next != NULL)
    {
        cout << root->next->data;
    }
    else
    {
        cout << "NULL";
    }
    cout << endl;

    printPopulateInorderSuccessor(root->right);
}

//将一个任意树转换为家和树
//任意一个节点的值为其所有子的加和
Node *convertToSumTree(Node *root)
{
    if (NULL == root)
    {
        return root;
    }

    int sum = 0;
    if (root->left != NULL)
    {
        sum += root->left->data;
        convertToSumTree(root->left);
        sum += root->left->data;
    }

    if (root->right != NULL)
    {
        sum += root->right->data;
        convertToSumTree(root->right);
        sum += root->right->data;
    }

    root->data = sum;

    return root;
}

int convertToSumTree1(Node *root)
{
    if (NULL == root)
    {
        return 0;
    }

    int oldvalue = root->data;

    root->data = convertToSumTree1(root->left) +
        convertToSumTree1(root->right);

    return root->data + oldvalue;
}

//从中序遍历构建一个特殊的二叉树
//该二叉树特点: 所有节点的左节点和右节点都小于父节点
int *indexOfMax(int *inorder, int len)
{
    if (NULL == inorder || len < 1)
    {
        return NULL;
    }

    for (int i = 1; i < len; ++i)
    {
        if (*(inorder + i - 1) > *(inorder + i))
        {
            return inorder + i - 1;
        }

        if (i == (len -1))
        {
            return inorder + i;
        }
    }

    return inorder;
}


Node *constructSpecialTree(int *inorder, int len)
{
    if (NULL == inorder || len <= 0)
    {
        return NULL;
    }

    if (1 == len)
    {
        return new Node(*inorder);
    }

    int *max = indexOfMax(inorder, len);
    int leftlen = max - inorder;

    Node *left = constructSpecialTree(inorder, leftlen);
    Node *right = constructSpecialTree(inorder + leftlen + 1, len -leftlen - 1);

    Node *root = new Node(*max);
    root->left = left;
    root->right = right;

    return root;
}

//打印一颗二叉树的边界节点
//method1: 错误的方法 没有考虑边界的折返
void boundaryTraversalOfBinaryTree(Node *root)
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
        if (current->left != NULL)
        {
            cout << current->data << " ";
        }

        current = current->left;
    }

    while (!s.empty())
    {
        current = s.top();
        s.pop();

        if (current->left == NULL && current->right == NULL)
        {
            cout << current->data << " ";
        }

        current = current->right;
        while (current != NULL)
        {
            s.push(current);
            current = current->left;
        }
    }
    current = root->right;
    while (current != NULL)
    {
        if (!(current->right == NULL && current->left == NULL))
        {
            cout << current->data << " ";
        }

        current = current->right;
    }

    cout << endl;
}
//method2:
//打印左边界
//打印右边界
//打印叶子节点
void travelLeftBoundary(Node *root)
{
    while (root != NULL)
    {
        if (root->left != NULL)
        {
            cout << root->data << " ";
            root = root->left;
        }
        else if (root->right != NULL)
        {
            cout << root->data << " ";
            root = root->right;
        }
        else
        {
            root = NULL;
        }
    }
}

void travelRightBoundary(Node *root)
{
    while (root != NULL)
    {
        if (root->right != NULL)
        {
            cout << root->data << " ";
            root = root->right;
        }
        else if (root->left != NULL)
        {
            cout << root->data << " ";
            root = root->left;
        }
        else
        {
            root = NULL;
        }
    }
}

void travelLeavesBoundary(Node *root)
{
    if (NULL == root)
    {
        return ;
    }

    if (root->left == NULL && root->right == NULL)
    {
        cout << root->data << " ";
    }

    travelLeavesBoundary(root->left);
    travelLeavesBoundary(root->right);
}

void boundaryTraversalOfBinaryTree1(Node *root)
{
    if (NULL == root)
    {
        return ;
    }

    cout << root->data << " ";
    travelLeftBoundary(root->left);
    travelLeavesBoundary(root);
    travelRightBoundary(root->right);
    cout << endl;
}

//从一个给定的先序遍历和后续遍历构建一个完全二叉树
Node *constructFullBinary(int *preorder, int *postorder, int preS, int postS, int len)
{
    Node *root = new Node(preorder[preS]);
    if (len == 1)
    {
        return root;
    }

    int left = preorder[preS+1];
    int leftlen;
    for (int i = 0; i < len; ++i)
    {
        if (postorder[postS+i] == left)
        {
            leftlen = i + 1;
            break;
        }
    }

    root->left = constructFullBinary(preorder, postorder, preS + 1, postS, leftlen);
    root->right = constructFullBinary(preorder, postorder, preS + 1 + leftlen, postS + leftlen, len - leftlen - 1);

    return root;
}
Node *constructFullBinaryTreeFromPreorderAndPostorder(int preorder[], \
        int postorder[], int len)
{
    if (preorder == NULL || postorder == NULL || len <= 0)
    {
        return NULL;
    }

    return constructFullBinary(preorder, postorder, 0, 0, len);
}

//迭代先序遍历
//method1: 亲 傻了有么有，这个叫中序遍历
void iterativePreorderTraversal(Node *root)
{
    if (NULL == root)
    {
        return ;
    }

    Node *current;
    while (root != NULL)
    {
        current  = root->left;
        if (current == NULL)
        {
            cout << root->data << " ";
            root = root->right;
        }
        else
        {
            while (current->right != NULL && current->right != root)
            {
                current = current->right;
            }

            if (current->right == NULL)
            {
                current->right = root;
                root = root->left;
            }
            else
            {
                cout << root->data << " ";
                root = root->right;
                current->right = NULL;
            }
        }
    }

    cout << endl;
}

//method2: 这才是先序遍历
void iterativePreorderTraversal1(Node *root)
{
    if (NULL == root)
    {
        return ;
    }

    Node *current;
    stack<Node *> s;
    s.push(root);

    while (s.empty() == false)
    {
        current = s.top();
        s.pop();

        cout << current->data << " ";

        if (current->right != NULL)
        {
            s.push(current->right);
        }

        if (current->left != NULL)
        {
            s.push(current->left);
        }
    }

    cout << endl;
}

//Morris Traversal for Preorder
//不适用递归和栈先序遍历
void morrisTravelPreorder(Node *root)
{
    if (NULL == root)
    {
        return ;
    }

    Node *current;
    while (root != NULL)
    {
        current = root->left;
        if (current == NULL)
        {
            cout << root->data << " ";
            root = root->right;
        }
        else
        {
            while (current->right != NULL && current->right != root)
            {
                current = current->right;
            }

            if (current->right == NULL)
            {

                cout << root->data << " ";
                current->right = root;

                root = root->left;
            }
            else
            {
                current->right = NULL;
                root = root->right;
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
    root->right->left->left = new Node(9);
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

    cout << "doubleTree:";
//    tree = doubleTree(root);
//    InorderTravel(tree);

    cout << "求树的最大宽度: " << getMaxWidthOftree(root) << endl;
    cout << "求树的最大宽度2: " << getMaxWidthOftree2(root) << endl;

    cout << "获取给定节点的层次: " << getNodeLevel(root, 8) << endl;
    cout << "打印指定节点的所有父节点: ";
    printNodeAncestor(root, 8);
    cout << "打印制定节点的所有父节点2: ";
    printNodeAncestor2(root, 8);
    cout << endl;

    cout << "加和树: " << checkSumTree(root) << endl;

    cout << "使用固定额外内存连接树上同一层次上的节点: " << endl;
    connectLevelNode(root);
    printConnectTree(root);
    connectLevelNode1(root);
    printConnectTree(root);

    cout << "Populate Inorder Successor for all nodes" << endl;
    populateInorderSuccessor(root);
    printPopulateInorderSuccessor(root);

    cout << "将一个二叉树转换为加和树" << endl;
//    convertToSumTree(root);
//   InorderTravel(root);

    cout << "从一个中序遍历构建一个特殊的二叉树" << endl;
    int inorderdata[] = {5, 10, 40, 30, 28};
    Node *newtree = constructSpecialTree(inorderdata, 5);
    InorderTravel(newtree);


    cout << "打印一棵树的边界: " << endl;
    boundaryTraversalOfBinaryTree(root);
    boundaryTraversalOfBinaryTree1(root);

    cout  << "从先序遍历和后续遍历构造一颗满二叉树:" << endl;
    int pre[] = {1, 2, 4, 8, 9, 5, 3, 6, 7};
    int post[] = {8, 9, 4, 5, 2, 6, 7, 3, 1};
    Node *fulRoot = constructFullBinaryTreeFromPreorderAndPostorder(pre, post,
            sizeof(pre) / sizeof(pre[0]));
    InorderTravel(fulRoot);

    cout << "迭代中序遍历树:" << endl;
    InorderTravel(root);
    iterativePreorderTraversal(root);
    iterativePreorderTraversal1(root);

    cout << "Mirris travel: " << endl;
    morrisTravelPreorder(root);
    return 0;
}
