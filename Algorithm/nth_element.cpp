#include <iostream>

using namespace std;

int median(int a, int b, int c)
{
    if (a < b)
    {
        if (b < c)
        {
            return b;
        }
        else if (a < c)
        {
            return c;
        }
        else
        {
            return a;
        }
    }
    else if (a < c)
    {
        return a;
    }
    else if (b < c)
    {
        return c;
    }
    else
    {
        return b;
    }
}
int partition(int *data, int b, int e, int me)
{
    while (true)
    {
        while (data[b] < me)
        {
            ++b;
        }
        while (data[e] > me)
        {
            --e;
        }

        if (b >= e)
        {
            return b;
        }

        swap(data[b], data[e]);
        ++b;
    }
}

void insertion_sort(int *data, int b, int e)
{

}
void nth_element_help(int *data, int b, int e, int n)
{
    while (e - b > 3)
    {
        int privo = partition(data, b, e, median(data[b], data[e], data[b + (e - b) / 2]));
        if (privo <= n)
        {
            b = privo;
        }
        else
        {
            e = privo;
        }
    }

    insertion_sort(data, b, e);
}
