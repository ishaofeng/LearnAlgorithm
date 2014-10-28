#include "base.h"
#include <queue>

struct TreeNode
{
    int key;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int key = 0) : key(key), left(NULL), right(NULL) {}
};

void InorderTreeWalk(TreeNode *tree)
{
    if (NULL == tree)
    {
        return ;
    }

    stack<TreeNode *> s;

    TreeNode *node = tree;
    while (node != NULL)
    {
        s.push(node);
        node = node->left;
    }

    while (!s.empty())
    {
        node = s.top();
        s.pop();

        cout << node->key << " ";
        if (node->right != NULL)
        {
            node = node->right;
            while (node != NULL)
            {
                s.push(node);
                node = node->left;
            }
        }
    }
}

void PreorderTreeWalk(TreeNode *tree)
{
    if (NULL == tree)
    {
        return ;
    }

    stack<TreeNode *> s;
    s.push(tree);

    TreeNode *node = NULL;
    while (!s.empty())
    {
        node = s.top();
        s.pop();

        cout << node->key << " ";

        if (node->right != NULL)
        {
            s.push(node->right);
        }

        if (node->left != NULL)
        {
            s.push(node->left);
        }
    }
    cout << endl;
}

void PostorderTreeWalk(TreeNode *tree)
{
    if (NULL == tree)
    {
        return ;
    }
}


//层次遍历
void LevelTreeWalk(TreeNode *tree)
{
    if (NULL == tree)
    {
        return ;
    }

    queue<TreeNode *> q;
    q.push(tree);

    TreeNode *current = NULL;
    while (!q.empty())
    {
        current = q.front();
        q.pop();

        cout << current->key << " ";

        if (current->left != NULL)
        {
            q.push(current->left);
        }

        if (current->right != NULL)
        {
            q.push(current->right);
        }
    }
    cout << endl;
}
int main()
{
    TreeNode *tree = new TreeNode(1);
    tree->left = new TreeNode(2);
    tree->right = new TreeNode(3);
    tree->left->left = new TreeNode(4);
    tree->left->right = new TreeNode(5);
    tree->right->left = new TreeNode(6);
    tree->right->right = new TreeNode(7);

    cout << "先序遍历: ";
    PreorderTreeWalk(tree);

    cout << "中序遍历: ";
    InorderTreeWalk(tree);

    cout << "层次遍历: ";
    LevelTreeWalk(tree);
}
