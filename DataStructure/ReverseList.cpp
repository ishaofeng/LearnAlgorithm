#include "base.h"

Node *reverseList(Node *head)
{
    if (NULL == head)
    {
        return head;
    }

    Node *reverseHead = head, *node = NULL;
    head = head->next;
    reverseHead->next = NULL;

    while (head != NULL)
    {
        node = head;
        head = node->next;

        node->next = reverseHead;
        reverseHead = node;
    }

    return reverseHead;
}

int main()
{
    Node *head = genList(10);
    printList(head);

    head = reverseList(head);
    printList(head);
}
