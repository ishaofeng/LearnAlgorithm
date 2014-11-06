#include <iostream>

using namespace std;

/*
 * 三叉搜索树 (每个节点包含三个指针)
 * 1. 左指针指向节点值小于当前节点值的节点
 * 2. 中指针指向节点值等于当前节点值的节点
 * 3. 右指针指向节点值大于当前节点值的节点
 *
 * 用途:
 *      1. 自动完成   2. 拼写检查
 */
struct Node
{
    Node *left, *center, *right;
    bool bFinal;
    char value;

    Node(char v) : value(v), bFinal(false), left(NULL), center(NULL), right(NULL) {}
};

//插入值
void insert(Node *&root, char *word)
{
    if (*word == '\0')
    {
        return ;
    }
    if (root == NULL)
    {
        root = new Node(*word);
    }

    if (root->value > *word)
    {
        insert(root->left, word);
    }
    else if (root->value < *word)
    {
        insert(root->right, word);
    }
    else
    {
        word += 1;
        if (*word == '\0')
        {
            root->bFinal = true;
        }
        else
        {
            insert(root->center, word);
        }
    }
}

//查找
bool search(Node *root, char *word)
{
    if (root == NULL || word == NULL)
    {
        return false;
    }

    if (*word == '\0')
    {
        return false;
    }

    if (root->value < *word)
    {
        return search(root->left, word);
    }
    else if (root->value > *word)
    {
        return search(root->right, word);
    }
    else
    {
        word += 1;
        if (*word == '\0')
        {
            return root->bFinal;
        }
        return search(root->center, word);
    }
}

//遍历
void travelHelp(Node *root, char buffer[], int depth)
{
    if (root)
    {
        travelHelp(root->left, buffer, depth);

        buffer[depth] = root->value;
        if (root->bFinal)
        {
            buffer[depth+1] = '\0';
            cout << "travel: " << buffer << endl;
        }
        travelHelp(root->center, buffer, depth + 1);

        travelHelp(root->right, buffer, depth);
    }
}

void travel(Node *root)
{
    if (root == NULL)
    {
        return ;
    }

    char buffer[65535];
    travelHelp(root, buffer, 0);
}

void print(Node *root)
{
    if (root == NULL)
    {
        return ;
    }

    cout << "# " << root->value << endl;
    print(root->center);
}

void deleteWord(Node *&root, char *word)
{
    if (root == NULL)
    {
        return ;
    }
    cout << *word << "#" << root->value  << endl;
    if (*word < root->value)
    {
        deleteWord(root->left, word);
    }
    else if (*word > root->value)
    {
        deleteWord(root->right, word);
    }
    else
    {
        word += 1;
        if (*word)
        {
            deleteWord(root->center, word);
        }
        else
        {
            cout << "outer" << endl;
            if (root->left == NULL && root->right == NULL)
            {
                cout << "inner" << endl;
                delete root;
                root = NULL;
            }
        }

    }
}

int main()
{
    Node *root = NULL;
    char a[] = "abc";
    char b[] = "bdkf";
    char c[] = "cehb";
    char d[] = "bdhk";
    insert(root, b);
    insert(root,  a);
    insert(root, c);
    insert(root, d);

    deleteWord(root, a);
    travel(root);
}

