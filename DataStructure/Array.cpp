#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <iterator>

using namespace std;

int maxSumPathInTwoArrays(vector<int> &ar1, vector<int> &ar2)
{
    int result = 0;
    int car1 = 0;
    int car2 = 0;

    vector<int>::iterator it1 = ar1.begin(), it2 = ar2.begin();
    while (it1 != ar1.end() && it2 != ar2.end())
    {
        if (*it1 == *it2)
        {
        //    if (car1 > car2)
        //    {
        //        result += car1 + *it1;
        //        car1 = 0;
        //        car2 = 0;
        //    }
        //    else if (car1 < car2)
        //    {
        //        result += car2 + *it2;
        //        car1 = 0;
        //        car2 = 0;
        //    }
        //    else
        //    {
        //        car1 += *it1;
        //        car2 += *it2;
        //    }
        //    ++it1;
        //    ++it2;
            result += max(car1, car2);
            car1 = 0;
            car2 = 0;

            while (it1 != ar1.end() && it2 != ar2.end() && *it1 == *it2)
            {
                result += *it1++;
                it2++;
            }
        }
        else if (*it1 < *it2)
        {
        //    car1 += *it1;
        //    ++it1;
            car1 += *it1++;
        }
        else
        {
            car2 += *it2++;
        }
    }
    while (it1 != ar1.end())
    {
        car1 += *it1++;
    }
    while (it2 != ar2.end())
    {
        car2 += *it2++;
    }
    result += max(car1, car2);

    return result;
}
/*
//    vector<int> ar1{2, 3, 7, 10, 12};
//    vector<int> ar2{1, 5, 7, 8};

    vector<int> ar1{2, 3, 7, 10, 12, 15, 30, 34};
    vector<int> ar2{1, 5, 7, 8, 10, 15, 16, 19};
//    vector<int> ar2;

    int result = maxSumPathInTwoArrays(ar1, ar2);
    cout << result << endl;
*/

//Sort an array according to the order defined by another array
//给定两个数组A1, A2, 排序A1使用A2中的元素顺序, 如果剩余元素没有在S2中出现过则直接对其排序
void sortArrayInDefinedOrder(vector<int> &a1, const vector<int> &a2)
{
    /*1) 将数据分为两部分一部分为在A2中出现的, 另一部分为未在A2中出现的, 对数据进行计数
     *2) 通过计数恢复数据
     */
    unordered_map<int, int> m;
    for (int a : a2)
    {
        m[a] = 0;
    }

    //将数据根据是否存在与A2中进行分类
    int b = 0, e = a1.size();
    while (b < e)
    {
        if (m.find(a1[b]) != m.end())
        {
            m[a1[b++]]++;
        }
        else
        {
            swap(a1[b], a1[--e]);
        }
    }

    //对分类右侧数据进行排序
    auto rightIt = a1.begin() + b - 1;
    sort(rightIt, a1.end());

    //恢复数据
    auto it = a2.begin();
    auto itA1 = a1.begin();
    while (it != a2.end())
    {
        if (m.find(*it) != m.end())
        {
            int c = m[*it];
            while (c-- > 0)
            {
                *itA1++ = *it;
            }
        }
        ++it;
    }
}

int main()
{
    vector<int> a1{2, 1, 2, 5, 7, 1, 9, 3, 6, 8, 8};
    vector<int> a2{2, 1, 8, 3};

    sortArrayInDefinedOrder(a1, a2);
    copy(a1.begin(), a1.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}
