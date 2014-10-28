#include <iostream>
#include <stack>

using namespace std;

struct Node
{
    int data;
    Node *small;
    Node *large;

    Node(int data) : data(data), small(NULL), large(NULL) {}
};

void printList(Node *head)
{
    Node *tail = NULL;
    cout << "正序打印: ";
    while (head != NULL)
    {
        cout << head->data << " ";
        tail = head;

        head = head->large;
    }
    cout << endl;

    cout << "逆序打印: ";
    while (tail != NULL)
    {
        cout << tail->data << " ";
        tail = tail->small;
    }

    cout << endl;
}

Node *treeToList(Node *root)
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
        current = current->small;
    }

    Node *head = current, *prev = NULL;
    while (!s.empty())
    {
        current = s.top();
        s.pop();

        if (NULL == head)
        {
            head = current;
        }

        if (prev != NULL)
        {
            prev->large = current;
            current->small = prev;
        }

        prev = current;

        if (current->large != NULL)
        {
            current = current->large;
            while (current != NULL)
            {
                s.push(current);
                current = current->small;
            }
        }
    }

    return head;
}

int main()
{
    Node *root = new Node(4);
    root->small = new Node(2);
    root->small->small = new Node(1);
    root->small->large = new Node(3);
    root->large = new Node(6);
    root->large->small = new Node(5);

    Node *head = treeToList(root);

    printList(head);

    return 0;
}
