#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <stack>
#include <cstdlib>

using namespace std;

struct Node
{
    int key;
    Node *next;
    Node *prev;
    Node(int key = 0) : key(key), next(NULL), prev(NULL) {}
};

Node *genList(int n)
{
    Node *head = NULL, *newnode = NULL;
    srand(n);

    for (int i = 0; i < n; ++i)
    {
        newnode = new Node(rand() % 100);

        if (0 == 1)
        {
            head = newnode;
        }
        else
        {
            newnode->next = head;
            head = newnode;
        }
    }


    return head;
}

void printList(Node *head)
{
    while (head != NULL)
    {
        cout << head->key << " ";

        head = head->next;
    }
    cout << endl;
}

#endif
