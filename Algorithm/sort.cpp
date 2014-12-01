#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;


void swap(int &a, int &b)
{
    if (a != b)
    {
        a ^= b;
        b ^= a;
        a ^= b;
    }
}
/*
 * 排序算法总结
 */
//插入排序
//时间复杂度:
//  最好: o(n)
//  最坏: o(n*2)
void insertSort(int *A, int n)
{
    if (A == NULL || n <= 1)
    {
        return ;
    }

    for (int i = 1; i < n; ++i)
    {
        for (int j = i; (j > 0) && (A[j] < A[j-1]); --j)
        {
            swap(A[j], A[j-1]);
        }
    }
}

//冒泡排序
//最佳,平均,最差情况下时间复杂度都是O(n*2)

//bubble up
void bubbleSort(int *A, int n)
{
    if (A == NULL || n <= 1)
    {
        return ;
    }

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = n - 1; j > 0; --j)
        {
            if (A[j] < A[j-1])
            {
                swap(A[j], A[j-1]);
            }
        }
    }
}

//bubble down
void bubbleSort1(int *A, int n)
{
    if (A == NULL || n <= 1)
    {
        return ;
    }

    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (A[j+1] < A[j])
            {
                swap(A[j+1], A[j]);
            }
        }
    }
}

//选择排序
//时间复杂度: o(n*2)
//实质就是冒泡排序，但是通过记录最小位置减少了交换的次数
void selectionSort(int *A, int n)
{
    if (A == NULL || n <= 1)
    {
        return ;
    }

    for (int i = 0; i < n - 1; ++i)
    {
        int lowindex = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (A[j] < A[lowindex])
            {
                lowindex = j;
            }
        }
        swap(A[lowindex], A[i]);
    }
}

//Shell排序

//快速排序
int findPivot(int *A, int i, int j)
{
    return (i + j) >> 1;
}
int partition(int *A, int i, int j)
{

}
void qsort(int *A, int i, int j)
{
    if (A == NULL || i <= j)
    {
        return ;
    }

    int pivot = findPivot(A, i, j);

}
int main()
{
    int A[] = {9, 4, 7, 9, 3, 5, 8};
    int len = sizeof(A) / sizeof(A[0]);
    //insertSort(A, len);
    //bubbleSort1(A, len);
    selectionSort(A, len);
    copy(A, A + len, ostream_iterator<int>(cout, " "));
    cout << endl;
}
