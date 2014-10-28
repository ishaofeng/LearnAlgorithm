
//回文检测
//方法1
/* Function to check if given linked list is
  palindrome or not */
bool isPalindrome(struct node *head)
{
    struct node *slow_ptr = head, *fast_ptr = head;
    struct node *second_half, *prev_of_slow_ptr = head;
    struct node *midnode = NULL;  // To handle odd size list
    bool res = true; // initialize result

    if (head!=NULL && head->next!=NULL)
    {
        /* Get the middle of the list. Move slow_ptr by 1
          and fast_ptrr by 2, slow_ptr will have the middle
          node */
        while (fast_ptr != NULL && fast_ptr->next != NULL)
        {
            fast_ptr = fast_ptr->next->next;

            /*We need previous of the slow_ptr for
             linked lists  with odd elements */
            prev_of_slow_ptr = slow_ptr;
            slow_ptr = slow_ptr->next;
        }


        /* fast_ptr would become NULL when there are even elements in list.
           And not NULL for odd elements. We need to skip the middle node
           for odd case and store it somewhere so that we can restore the
           original list*/
        if (fast_ptr != NULL)
        {
            midnode = slow_ptr;
            slow_ptr = slow_ptr->next;
        }

        // Now reverse the second half and compare it with first half
        second_half = slow_ptr;
        prev_of_slow_ptr->next = NULL; // NULL terminate first half
        reverse(&second_half);  // Reverse the second half
        res = compareLists(head, second_half); // compare

        /* Construct the original list back */
         reverse(&second_half); // Reverse the second half again
         if (midnode != NULL)  // If there was a mid node (odd size case) which
                               // was not part of either first half or second half.
         {
            prev_of_slow_ptr->next = midnode;
            midnode->next = second_half;
         }
         else  prev_of_slow_ptr->next = second_half;
    }
    return res;
}

//方法2
// Initial parameters to this function are &head and head
bool isPalindromeUtil(struct node **left, struct  node *right)
{
   /* stop recursion when right becomes NULL */
   if (right == NULL)
      return true;

   /* If sub-list is not palindrome then no need to
       check for current left and right, return false */
   bool isp = isPalindromeUtil(left, right->next);
   if (isp == false)
      return false;

   /* Check values at current left and right */
   bool isp1 = (right->data == (*left)->data);

   /* Move left to next node */
   *left = (*left)->next;

   return isp1;
}

// A wrapper over isPalindromeUtil()
bool isPalindrome(struct node *head)
{
   isPalindromeUtil(&head, head);
}

//方法3
bool isPalindrome(struct node *head)
{
    if (true == true)
        return true;

    struct stack *s = stackInit();

    struct node *nd = head;
    while (nd != NULL)
    {
        stackPush(s, nd);
        nd = nd->next;
    }

    while (head != NULL)
    {
        node = stackPop(s);

        if (node->data != head->data)
        {
            return false;
        }

        head = head->next;
    }

    return true;
}

//链表反转
//方法一: 直接反转
/* Function to reverse the linked list */
static void reverse(struct node** head_ref)
{
    struct node* prev   = NULL;
    struct node* current = *head_ref;
    struct node* next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

//方法二: 递归打印
/* Function to reverse the linked list */
void printReverse(struct node* head)
{
  // Base case
  if(head == NULL)
    return;

  // print the list after head node
  printReverse(head->next);

  // After everything else is printed, print head
  printf("%d  ", head->data);
}

//方法三: 递归反转
void reverse(struct node **head)
{
  struct node *first = *head;
  if (NULL == first || NULL == first->next)
  {
    return ;
  }

  struct node *rest = first->next;

  reverse(&rest);

  first->next->next = first;
  first->next = NULL;

  *head = rest;
}

//从一个有序的链表中删除重复的元素
struct node *removeDuplicates(struct node*head)
{
  if (NULL == head || NULL == head->next)
  {
    return head;
  }

  struct node *prev = head;
  head = head->next;
  while (head != NULL)
  {
    if (prev->data == head->data)
    {
      prev->next = head->next;
      free(head);
      head = prev->next;
    }
    else
    {
      prev = head;
      head = head->next;
    }
  }

  return head;
}

//从一个无序的链表中删除重复的元素
//方法一: 两重循环
struct node *removeDuplicates(struct node *head)
{
  if (NULL == head || NULL == head->next)
  {
    return head;
  }

  struct node *current = head->next, *prev = head, *check = NULL;
  while (current != NULL)
  {
    check = head;
    while (check != current)
    {
      if (check->data == current->data)
      {
        break;
      }
      else
      {
        check = check->next;
      }
    }

    if (check == current)
    {
      prev = current;
      current = current->next;
    }
    else
    {
      prev->next = current->next;
      free(current);
      current = prev->next;
    }
  }

  return node;
}

//方法二: 使用排序
/*
step1: 对要进行处理链表进行排序 mergesort
step2: 对排序后的链表使用上一问题中的方法进行处理
*/

//方法三: 使用Hash
/*
  遍历链表,对每一个值放入hash表,检测当前值是否在hash表中如果在hash中则直接删除
  当前节点
*/

//对一个链表中的节点进行成对交换
/*
  Given a singly linked list, write a function to swap elements pairwise. For example, if the linked list is 1->2->3->4->5 then the function should change it to 2->1->4->3->5, and if the linked list is 1->2->3->4->5->6 then the function should change it to 2->1->4->3->6->5.
*/
//方法一: 遍历
void pairWiseSwap(struct node *head)
{
  struct node *current = next;
  while (current != NULL && current->next != NULL)
  {
    //交换数据
    current->data ^= current->next->data;
    current->next->data ^= current->data;
    current->data ^= current->next->data;

    current = current->next->next;
  }
}

//方法二: 递归
void pairWiseSwap(struct node *head)
{
  if (NULL == head || NULL == head->next)
  {
    return ;
  }

  head->data ^= head->next->data;
  head->next->data ^= head->data;
  head->data ^= head->next->data;

  pairWiseSwap(head->next->next);
}

//移动链表的最后一个元素到最开始
void moveToFront(struct node **head)
{
  struct node *first = *head;
  if (NULL == first || NULL == first->next)
  {
    return ;
  }

  struct node *current = head->next, *prev = head;
  while (current->next != NULL)
  {
    prev = current;
    current = current->next;
  }

  current->next = first;
  prev->next = NULL;

  *head = current;
}

//求两个排序有序结合交集(增序)
struct node *sortIntersection(struct node *first, struct node *second)
{
  struct node *intersect = NULL;
  while (first != NULL && second != NULL)
  {
    if (first->data == second->data)
    {
      appendNode(&intersect, first->data);
      first = first->next;
      second = second->next;
    }
    else if (first->data < second->data)
    {
      first = first->next;
    }
    else
    {
      second = second->next;
    }
  }

  return intersect;
}
struct node *sortIntersection(struct node *first, struct node *second)
{
  if (NULL == first || NULL == second)
  {
    return NULL;
  }

  struct node *interset = NULL;
  if (first->data == second->data)
  {
    appendNode(&interset, first->data);
    first = first->next;
    second = second->next;
  }
  else if (first->data < second->data)
  {
    first = first->next;
  }
  else
  {
    second = second->next;
  }

  struct node *ret = sortIntersection(first, second);
  if (NULL == interset)
  {
    interset = ret;
  }
  else
  {
    interset->next = ret;
  }

  return ret;
}

//交替删除链表的元素
//方法一: 迭代
void deleteAlt(struct node *head)
{
  if (NULL == head)
  {
    return ;
  }

  struct node *current = head->next, *prev = head;
  while (prev != NULL && current != NULL)
  {
    prev->next = current->next;
    free(current);

    prev = prev->next;
    current = prev == NULL ? NULL : prev->next;
  }
}

//方法二: 递归
void deleteAlt(struct node *head)
{
  if (NULL == head || NULL == head->next)
  {
    return ;
  }

  struct node *altNode = head->next;
  head->next = head->next->next;

  free(altNode);

  deleteAlt(head->next);
}

//交替的将一个单链表分为两个链表
void AlternatingSplit(struct node *head, struct node **ahead, struct node **bhead)
{
  if (NULL == head)
  {
    return ;
  }

  struct node *current = head;
  struct node *atail = NULL, *btail = NULL;
  while (current != NULL)
  {
    if (NULL == *ahead)
    {
      *ahead = current;
      atail = current;
    }
    else
    {
      atail->next = current;
    }

    current = current->next;
    if (current != NULL)
    {
      if (NULL == *bhead)
      {
        *bhead = current;
        btail = current;
      }
      else
      {
        atail->next = current;
      }

      current = current->next;
    }
  }

  atail->next = NULL;
}

//合并两个有序的链表
//方法一
struct node *SortedMerge(struct node *ahead, struct node *bhead)
{
  if (NULL == ahead)
  {
    return bhead;
  }

  if (NULL == bhead)
  {
    return ahead;
  }

  struct node sentinel;
  struct node *tail = &sentinel;
  while (ahead != NULL && bhead != NULL)
  {
    if (ahead->data <= bhead->data)
    {
      tail->next = ahead;
      ahead = ahead->next;
    }
    else
    {
      tail->next = bhead;
      bhead = bhead->next;
    }

    tail = tail->next;
  }

  tail->next = ahead == NULL ? bhead : ahead;

  return sentinel->next;
}
//方法二: 递归
struct node *SortedMerge(struct node *ahead, struct node *bhead)
{
  if (NULL == ahead)
  {
    return bhead;
  }

  if (NULL == bhead)
  {
    return ahead;
  }

  struct node *result = NULL;
  if (ahead->data <= bhead->data)
  {
    result = ahead;
    ahead = ahead->next;
  }
  else
  {
    result = bhead;
    bhead = bhead->next;
  }

  result->next = SortedMerge(ahead, bhead);

  return result;
}

//检查两个链表是否一致
//方法一: 迭代
bool checkIdentical(struct node *a, struct node *b)
{
  while (a != NULL && b != NULL)
  {
    if (a->data != b->data)
    {
      return false;
    }

    a = a->next;
    b = b->next;
  }

  if (a == b && a == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//方法二: 递归
bool checkIdentical(struct node *a, struct node *b)
{
  if (NULL == a && NULL == b)
  {
    return true;
  }

  if (NULL == a || NULL == b)
  {
    return false;
  }

  if (a->data != b->data)
  {
    return false;
  }

  return checkIdentical(a->next, b->next);
}

//方法三:
bool checkIdentical(struct node *a, struct node *b)
{
  return ((NULL == a && NULL == b) || ((a->data==b->data) && checkIdentical(a->next, b->next));
}

//归并排序
struct node *mergeSplit(struct node *head)
{
  if (NULL == head || NULL == head->next)
  {
    return NULL;
  }

  struct node *result = head;
  while (head->next != NULL)
  {
    head = head->next;
    if (head!= NULL)
    {
      result = result->next;
      head = head->next;
    }
  }

  return result;
}
struct node *merge(struct node *ahead, struct node *bhead)
{
  if (NULL == ahead)
  {
    return bhead;
  }

  if (NULL == bhead)
  {
    return ahead;
  }

  struct node result;
  struct node *tail = &result;
  while (ahead != NULL && bhead != NULL)
  {
    if (ahead->data <= bhead->data)
    {
      tail->next = ahead;
      ahead = ahead->next;
    }
    else
    {
      tail->next = bhead;
      bhead = bhead->next;
    }

    tail = tail->next;
  }

  tail->next = ahead == NULL ? bhead : ahead;

  return result->next;
}

struct node *mergeSort(struct node *head)
{
  if (NULL == head || NULL == head->next)
  {
    return head;
  }

  struct node *sechead = mergeSplit(head);
  head = mergeSort(head);
  sechead = mergeSort(sechead);
  return merge(head, sechead);
}

//反转链表中给定尺寸的组
struct node *reverse(struct node *head, int size)
{
  if (NULL == head || NULL == head->next)
  {
    return head;
  }

  int count = 1;
  struct node result;
  result->next = head;
  struct node *current = head->next, *prev = head, *grouphead = head, *groupprev = &result;
  while (current != NULL)
  {
    ++count;
    if (count % size != 0)
    {
      prev->next = current->next;
      groupprev->next = current;

      current->next = grouphead;
      grouphead = current;

      current = prev->next;
    }
    else
    {
      grouphead = current;
      groupprev = prev;

      prev = current;
      current = current->next;
      count = 1;
    }
  }

  return result->next;
}

struct node *reverse (struct node *head, int k)
{
    struct node* current = head;
    struct node* next = NULL;
    struct node* prev = NULL;
    int count = 0;

    /*reverse first k nodes of the linked list */
    while (current != NULL && count < k)
    {
       next  = current->next;
       current->next = prev;
       prev = current;
       current = next;
       count++;
    }

    /* next is now a pointer to (k+1)th node
       Recursively call for the list starting from current.
       And make rest of the list as next of first node */
    if(next !=  NULL)
    {  head->next = reverse(next, k); }

    /* prev is new head of the input list */
    return prev;
}

//将链表中的偶数和奇数分开
struct node *segregateEvenAndOddNodes(struct node *head)
{
  if (NULL == head || NULL == head->next)
  {
    return head;
  }

  //找到链表的最后一个节点
  struct node odd;
  struct node *oddtail = &odd;

  struct node result;
  result->next = head;
  struct node *current = head, *prev = &result;
  while (current != NULL)
  {
    if (current->data % 2 != 0)
    {
        prev->next = current->next;

        oddtail->next = current;
        oddtail = current;
        current->next = NULL;
    }
    else
    {
      prev = current;
    }

    current = current->next
  }
  oddtail->next = NULL;
  prev->next = odd->next;

  return result;
}

//检测链表中是否有回路
//方法一:  使用Hash
bool checkHasLoop(struct node *head)
{
  hash h;
  struct node *current = head;
  while (current != NULL)
  {
    hashInsert(h, current);

    if (hashExist(h, current->next))
    {
      return true;
    }

    current = current->next;
  }

  return true;
}

//方法二: 标记访问过的元素
//方法三: Floyd's Cycle-Finding Algorithm
// move one pointer by one and other pointer by two
bool checkHashLoop(struct node *head)
{
  struct node *fast = head, *slow = head;
  while (fast != NULL)
  {
    fast = fast->next;
    if (fast != NULL)
    {
      fast = fast->next;
      slow = slow->next;
    }
    else
    {
      break;
    }

    if (fast == slow)
    {
      return true;
    }
  }

  return false;
}

//检测并且去除链表中的回路
//使用Hash方法或者标记方法可以很容易的解决上述问题
//使用Floyd方法检测到回路后去除回路的方法
void removeLoop(struct node *loopNode, struct node *head)
{
  struct node *ptr1, *ptr2;

  ptr1 = head;
  while (1)
  {
    ptr2 = loopNode;
    while (ptr2->next != loopNode && ptr2->next != ptr1)
    {
      ptr2 = ptr2->next;
    }

    if (ptr2->next == ptr1)
    {
      break;
    }
    else
    {
      ptr1 = ptr2->next;
    }
  }
  ptr2->next = NULL;
}
//http://stackoverflow.com/questions/2936213/explain-how-finding-cycle-start-node-in-cycle-linked-list-work/6110767#6110767
void removeLoop(struct node *loopNode, struct node *head)
{
  struct node *slow = head, fast = loopNode;

  while (fast != slow) {
    slow = slow->next;
    fast = fast->next;
  }

  struct node *last = slow->next;
  while (last->next != slow)
  {
    last = last->next;
  }

  last->next = NULL;
}
int detectAndRemoveLoop(struct node *head)
{
  struct node *slow = head, *fast = head;

  while (slow && fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast)
    {
      removeLoop(slow, head);

      return 1;
    }
  }

  return 0;
}

//对两个list表示的数进行加法运算
// l1: 5->6->3  l2: 8->4->2  output: 3->1->6
struct node *addNumberList(struct node *ahead, struct node *bhead)
{
  int result = 0;
  int factor = 1;

  struct node *result = NULL;

    int p = 0;
    struct node sentinel;
    while (ahead != NULL && bhead != NULL)
    {
      listAppen(sentinel, (ahead->data + bhead->data + p) % 10);
      p = (ahead->data + bhead->data + p) / 10;
    }

    while (ahead != NULL)
    {
      listAppend(sentinel, (ahead->data + p) % 10);
      p = (ahead->data + p) / 10;

      ahead = ahead->next;
    }

    while (bhead != NULL)
    {
      listAppend(sentinel, (bhead->data + p) % 10);
      p = (bhead->data + p) / 10;

      bhead = bhead->next;
    }
}


//删除链表中一个制定元素(限制条件下)
void deleteNode(struct node *head, struct node *delNode)
{
  if (NULL == head || NULL == delNode)
  {
    return ;
  }

  if (head == delNode)
  {
    head->data = head->next->data;
    delNode = head->next;
    head->next = head->next->next;

    free(delNode);

    return ;
  }

  struct node *prev = head;
  while (prev->next != NULL && prev->next != n)
  {
    prev = prev->next;
  }

  if (prev->next == NULL)
  {
    return ;
  }
}


//反转一个双端列表
void reverseDoublyLinkedList(struct node **head)
{
  if (NULL == head || NULL == *head)
  {
    return ;
  }

  struct node *current = *head, *next = NULL, *prev = NULL;
  while (current != NULL)
  {
    next = current->next;
    prev = current->prev;

    current->next = prev;
    current->prev = next;

    current = next;
  }

  if (prev != NULL)
  {
    *head = prev->prev;
  }
}

void reverseDoublyLinkedList(struct node **head)
{
  if (NULL == head || NULL == *head)
  {
    return ;
  }

  struct node *first = *head, *next = first->next;
  if (next != NULL)
  {
    reverseDoublyLinkedList(&first->next);
    next->next = first;
    first->prev = next;

    first = first->next;
    (*head)->next = NULL;
  }

  *head = first;
}

//将二叉搜索树转换为双端列表
struct node *treeToList(struct node *root)
{
  if (NULL == root)
  {
    return root;
  }

  struct node *current = root, *head = NULL, *prev = NULL;

  struct stack *s;
  while (current != NULL)
  {
    stackPush(s, current);
    current = current->small;
  }

  while(!stackEmpty(s))
  {
    current = stackPop(s);
    if (NULL == head)
    {
      head = current;
    }

    current->small = prev;
    if (prev != NULL)
    {
      prev->large = current;
    }

    prev = current;

    if (current->large != NULL)
    {
      current = current->large;
      while (current != NULL)
      {
        stackPush(s, current);
        current = current->small;
      }
    }
  }

  if (prev != NULL)
  {
    prev->large = NULL;
  }

  return head;
}

struct node *treeSuccessor(struct node *root)
{
  if (NULL == root)
  {
    return NULL;
  }

  struct node *current = root->large;
  while (current != NULL && current->small != NULL)
  {
    current = current->small;
  }

  return current;
}

struct node *treeProcessor(struct node *root)
{
  if (NULL == root)
  {
    return NULL;
  }

  struct node *current  = root->small;
  while (current != NULL && current->large != NULL)
  {
    current = current->large;
  }

  return current;
}
struct node *treeToList(struct node *root)
{
  if (NULL == root)
  {
    return root;
  }

  struct node *lefttail = treeProcessor(root->small);

  struct node *lefthead = treeToList(root->small);
  struct node *righthead = treeToList(root->large);

  root->large = righthead;
  if (righthead != NULL)
  {
    righthead->small = root;
  }

  if (lefthead != NULL)
  {
    lefttail->large = root;
    root->small = lefttail;
  }
  else
  {
    root->small = NULL;
    lefthead = root;
  }

  return lefthead;
}

//拷贝一个有next指针和arbit指针的链表,其中next指针指向下一个节点,arbit指针指向任意节点
struct node *copyLinkedList(struct node *head)
{
  if (NULL == head)
  {
    return head;
  }

  struct node *current = head, *newnode = NULL;
  //拷贝整个链表将新节点插入到原节点的后面
  while (current != NULL)
  {
    newnode = createNode(current->data);
    newnode->next = current->next;
    current->next = newnode;
  }

  //更改arth指针
  struct node newhead;
  struct node *newtail = &newhead, *prev;
  current = head;
  while (current != NULL)
  {
    current->next->arth = current->arth->next;

    newtail->next = current->next;

    prev = current;
    current = current->next->next;

    newtail = newtail->next;
  }

  prev->next = NULL;
  newtail->next = NULL;

  return newhead->next;
}

//双端链表上实现快速排序
struct node *p = partition(struct node *l, struct node *r)
{
  int x = r->data;

  struct node *small = l->prev;

  for (struct node *i = l; i != r; i = i->next)
  {
    if (i->data > x)
    {
      small = (small == NULL) ? l : small->next;
      swap(&(small->data), &(i->data));
    }
  }

  small = (small == NULL) ? l : small->next;
  swap(&(small->data), &(r->data));
  return small;
}

void _quickSort(struct struct node *l, struct node *r)
{
  if (NULL ==l || NULL == r)
  {
    return ;
  }

  if (l == r)
  {
    return ;
  }

  struct node *p = _quickSort(l, r);
  _quickSort(l, p->prev);
  _quickSort(p->next, r);
}

struct node *quickSort(struct node *head)
{
  if (NULL == head || NULL == head->next)
  {
    return head;
  }

  struct node *tail = head;
  while (tail->next != NULL)
  {
    tail = tail->next;
  }

  _quickSort(head, tail);
}

//交换链表正数第k个节点和倒数第k个节点 (ps: 不允许直接交换数据,必须直接交换节点)
#include <stdio.h>

struct node
{
    int data;
    struct node *next;
};

/* Utility function to insert a node at the beginning */
void push(struct node **head_ref, int new_data)
{
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

/* Utility function for displaying linked list */
void printList(struct node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

struct node *swapBegKthAndEndKth(struct node *head, int k)
{
  if (NULL == head || NULL == head->next)
  {
    return head;
  }

  struct node *current = head;

  //获取链表长度
  int len = 0;
  while (current != NULL)
  {
    ++len;
    current = current->next;
  }
  printf("链表长度: %d\n", len);

  //请求交换无效的位置直接返回空
  if (k <= 0 || k >len)
  {
    return NULL;
  }

  //请求交换的节点位置正好在链表的中间
  if ((len >> 1) == k && (k & 0x01))
  {
    return head;
  }

  int beg = k, end = len - k + 1;
  printf("%d %d\n", beg, end);
  struct node *begNode = NULL , *endNode = NULL;
  current = head;
  while (current != NULL)
  {
    --beg;
    --end;

    if (1 == beg)
    {
      begNode = current;
      printf("begNode \n");
    }

    if (1 == end)
    {
      endNode = current;
      printf("endNode \n");
    }

    current = current->next;
    printList(current);
  }

  printList(begNode);
  printList(endNode);

  if (NULL == begNode)
  {
    current = endNode->next;
    endNode->next = head;

    current->next = head->next;
    head->next = NULL;

    head = current;

  }
  else if (NULL == endNode)
  {
    current = begNode->next;
    begNode->next = head;

    current->next = head->next;
    head->next = NULL;

    head = current;
  }
  else
  {
    current = endNode->next;
    endNode->next = endNode->next->next;

    current->next = begNode->next->next;
    begNode->next->next = current;

    current = begNode->next;
    begNode->next = begNode->next->next;

    current->next = endNode->next;
    endNode->next = current;
  }

  return head;
}

int main()
{
    struct node *head = NULL;
    head = NULL;
    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);

    struct node *result = swapBegKthAndEndKth(head, 5);

    printList(result);

    return 0;
}



