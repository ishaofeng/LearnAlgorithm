#include <stdio.h>

//延迟相等检测，能够减少比较的次数，并且对于一连串相等的数能够返回第一个出现的
//http://en.wikipedia.org/wiki/Binary_search_algorithm
int binary_search(int A[], int n, int key)
{
    if (NULL == A || n <= 0)
    {
        return -1;
    }

    int start = 0, end = n - 1, mid;
    while (start < end)
    {
        //该求中值的方法能够避免对于n特别大的时候出现溢出的问题
        mid = start + ((end - start) >> 1);

        if (A[mid] < key)
        {
            start = mid + 1;
        }
        else
        {
            end = mid;
        }
    }

    if (start == end && A[start] == key)
    {
        return start;
    }
    else
    {
        return -1;
    }
}

int main()
{
    int A[] = {1, 2 ,3, 3, 4, 5, 5, 8};
    int len = sizeof(A) / sizeof(A[0]);
    int i;
    for (i = 0; i < len; ++i)
    {
        printf("search %d : %d\n", A[i], binary_search(A, len, A[i]));
    }

    return 0;
}
