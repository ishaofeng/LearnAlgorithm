#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <iterator>
#include <map>
#include <unordered_set>
#include <string.h>
#include <unordered_map>
#include <tuple>
#include <limits>
#include <memory>

using namespace std;

//2.1 求二进制数中的1的个数
//扩展: 求整数A,B，将A转换为B需要改变多少位
//      A ^ B, 然后使用count计数
int count(unsigned int n)
{
    int c = 0;
    while (n)
    {
        n &= (n - 1);
        ++c;
    }

    return c;
}

//2.3 寻找发帖水王
//删除不同的ID, 剩下的"水王"出现次数仍然超过一半
int find(int ids[], int n)
{
    assert(ids != NULL && n > 0);

    int candidate;
    int times, i;
    for (times = i = 0; i < n; ++i)
    {
        if (times == 0)
        {
            candidate = ids[i];
            times = 1;
        }
        else
        {
            if (candidate == ids[i])
            {
                ++times;
            }
            else
            {
                --times;
            }
        }
    }
}

//2.5 寻找最大的k个数
//如果k值特别小可以直接使用部分排序  O(N*K)
//如果数据量本身特别小可以直接对数据进行排序
//方法一: 快速排序的partition思路, 改变数组的数
int partition(int data[], int beg, int end)
{
    if (data == NULL || beg > end)
    {
        return -1;
    }

    /*
    int p = end;
    --end;
    while (beg < end)
    {
        while (beg < end && data[beg] < data[p])
        {
            ++beg;
        }

        if (beg == end)
        {
            break;
        }

        while (beg < end && data[end] > data[p])
        {
            --end;
        }

        if (beg == end)
        {
            break;
        }

        swap(data[beg], data[end]);
    }

    swap(data[beg], data[p]);
    */
    int pivot = data[beg];
    while(beg < end)
    {
        while (beg < end && data[end] >= pivot)
        {
            --end;
        }
        data[beg] = data[end];
        while (beg < end && data[beg] <= pivot)
        {
            ++beg;
        }
        data[end] = data[beg];
    }
    data[beg] = pivot;

    return beg;
}
void kmax1(int data[], int n, int k)
{
    if (data == NULL || n <= 0 || k > n)
    {
        return ;
    }

    int kth = n - k;
    int beg = 0;
    int end = n - 1;
    while (beg < end)
    {
        int p = partition(data, beg, end);
        if (p == -1)
        {
            return ;
        }

        if (p < kth)
        {
            beg = p + 1;
        }
        else if (p > kth)
        {
            end = p - 1;
        }
        else
        {
            break;
        }
    }

    copy(data + kth, data + n, ostream_iterator<int>(cout, " "));
    cout << endl;
}

void quick_sort_help(int data[], int beg, int end)
{
    if (beg < end)
    {
        int p = partition(data, beg, end);
        quick_sort_help(data, beg, p - 1);
        quick_sort_help(data, p + 1, end);
    }
}

void quick_sort(int data[], int n)
{
    if (data == NULL || n <= 0)
    {
        return ;
    }

    quick_sort_help(data, 0, n - 1);

    cout << "quick sort: ";
    copy(data, data + n, ostream_iterator<int>(cout, " "));
    cout << endl;
}

struct Heap
{
    int size;
    int *data;
    int count;

    Heap(int size) : size(size), data(new int[size]), count(0)
    {

    }

    int top()
    {
        assert(size > 0);

        return data[0];
    }

    void push(int a)
    {
        assert((count + 1) <= size);

        data[count] = a;
        shift_up(count);
        ++count;
    }

    void replacetop(int a)
    {
        data[0] = a;
        shift_down(0);
    }

    void shift_up(int i)
    {
        while (i != 0)
        {
            int pi = (i+1) / 2 - 1;
            if (data[i] < data[pi])
            {
                swap(data[i], data[pi]);
                i = pi;
            }
            else
            {
                break;
            }

        }
    }

    void shift_down(int i)
    {
        while (i < count)
        {
            /*
            int sm = i;
            int l = (i+1) * 2 - 1;
            int r = (i+1) * 2 ;

            if (l < count && data[l] < data[sm])
            {
                sm = l;
            }
            if (r < count && data[r] < data[sm])
            {
                sm = r;
            }

            if (sm != i)
            {
                swap(data[sm], data[i]);
                i = sm;
            }
            else
            {
                break;
            }
            */
            int q = 2 * i + 1;
            if (q >= count)
            {
                break;
            }
            if ((q < count - 1) && (data[q + 1] < data[q]))
            {
                q = q + 1;
            }

            if (data[q] < data[i])
            {
                swap(data[q], data[i]);
                i = q;
            }
            else
            {
                break;
            }
        }
    }

    int getCount()
    {
        return count;
    }

    void print()
    {
        for (int i = 0; i < count; ++i)
        {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

void kmax2(int data[], int n, int k)
{
    Heap h(k);
    for (int i = 0; i < n; ++i)
    {
        if (h.getCount() == k)
        {
            if (h.top() < data[i])
            {
                h.replacetop(data[i]);
            }
        }
        else
        {
            h.push(data[i]);
        }
    }
    h.print();
}


//2.12 寻找满足条件的两个数:  简化问题, 保证序列中存在这样的对
typedef pair<int, int> SumPair;
//方法一:  暴力法
SumPair findSum(int data[], int n, int sum)
{
    assert(data != NULL && n > 0);

    int value;
    int i, j;
    for (i = 0; i < n; ++i)
    {
        value = sum - data[i];
        for (j = i + 1; j < n; ++j)
        {
            if (data[j] == value)
            {
                return make_pair(data[i], data[j]);
            }
        }
    }
}

//方法二: 排序法  需要改变输入数据
SumPair findSum2(int data[], int n, int sum)
{
    assert(data != NULL && n > 0);

    //对序列进行排序
    sort(data, data + n);

    int value;
    for (int i = 0; i < n; ++i)
    {
        value = sum - data[i];
        auto lower = lower_bound(data, data + n, value);
        if (lower != (data + i) && lower != (data + n))
        {
            return make_pair(data[i], value);
        }
    }
}

//方法三: hash  需要额外的hash空间
SumPair findSum3(int data[], int n, int sum)
{
    assert(data != NULL && n > 0);

    //将数据插入到hash表中
    unordered_set<int> m;
    int value;
    for (int i = 0; i < n; ++i)
    {
        value = sum - data[i];
        if (m.find(value) != m.end())
        {
            return make_pair(data[i], value);
        }

        m.insert(data[i]);
    }
}

//方法四: 排序方法二
SumPair findSum4(int data[], int n, int sum)
{
    assert(data != NULL && n > 0);

    //对序列进行排序
    sort(data, data + n);

    int i = 0;
    int j = n - 1;
    while (i < j)
    {
        if (data[i] + data[j] == sum)
        {
            return make_pair(data[i], data[j]);
        }
        else if (data[i] + data[j] > sum)
        {
            --j;
        }
        else
        {
            ++i;
        }
    }
}

//扩展
//1) 将两个数改为三个数
typedef tuple<int,int,int> ThreeTuple;
ThreeTuple findThreeSum(int data[], int n, int sum)
{
    assert(data != NULL && n > 0);

    //将序列中的所有值加入到hash中并进行计数
    unordered_map<int, int> m;
    for (int i = 0; i < n; ++i)
    {
        m[data[i]]++;
    }

    int value;
    for (int i = 0; i < n; ++i)
    {
        value = sum - data[i];
        m[data[i]]--;
        for (int j = i + 1; j < n; ++j)
        {
            value -= data[j];
            m[data[j]]--;

            if (m.find(value) != m.end() && m[value] > 0)
            {
                return make_tuple(data[i], data[j], value);
            }

            m[data[j]]++;
            value += data[j];
        }
        m[data[i]]++;
    }
}

//2) 找两个数的和最接近
SumPair findSumClose(int data[], int n, int sum)
{
    assert(data != NULL && n > 0);

    //对序列进行排序
    sort(data, data + n);

    int off = numeric_limits<int>::max();
    int i = 0;
    int j = n - 1;

    SumPair result;
    while (i < j)
    {
        if (abs(data[i] + data[j] - sum) < off)
        {
            off = abs(data[i] + data[j] - sum);
            result.first = data[i];
            result.second = data[j];
        }

        if (off == 0)
        {
            result = make_pair(data[i], data[j]);
            break;
        }
        else if (data[i] + data[j] > sum)
        {
            --j;
        }
        else
        {
            ++i;
        }
    }

    return result;
}


//2.13 子数组最大乘积
//给定一个长度为N的整数数组, 只允许使用乘法, 不能用除法, 计算任意(N-1)个数的组合中乘积最大的一组, 并写出计算的时间复杂度
//方法一: 暴力法 时间复杂度为 O(n*2)
long long maxMultiplySubset1(int data[], int n)
{
    assert(data != NULL && n > 0);

    long long max = numeric_limits<int>::min();
    long long result;
    for (int i = 0; i < n; ++i)
    {
        result = 1;
        for (int j = 0; j < i; ++j)
        {
            result *= data[j];
        }

        for (int j = i + 1; j < n; ++j)
        {
            result *= data[j];
        }

        if (result > max)
        {
            max = result;
        }
    }

    return max;
}

//方法二:  书上解法一 空间换时间
long long maxMultiplySubset2(int data[], int n)
{
    assert(data != NULL && n > 3);

    long long *l = new long long[n];
    long long *r = new long long[n];

    long long multiply = 1;
    for (int i = 0; i < n; ++i)
    {
        multiply *= data[i];
        l[i] = multiply;
    }
    multiply = 1;
    for (int i = n - 1; i >= 0; --i)
    {
        multiply *= data[i];
        r[i] = multiply;
    }

    long long max = numeric_limits<int>::min();
    for (int i = 0; i < n; ++i)
    {
        multiply = (i == 0) ? 1 : l[i-1];
        multiply *= (i == n - 1) ? 1 : l[i+1];

        if (multiply > max)
        {
            max = multiply;
        }
    }

    return max;
}

//2.14 求数组的子数组之和的最大值

//方法一:  暴力法   O(n*2)
int findSubMaxSum0(int data[], int n)
{
    assert(data != NULL && n > 0);

    int sum = 0, maxsum = numeric_limits<int>::min();
    for (int i = 0; i < n; ++i)
    {
        sum = 0;
        for (int j = i; j < n; ++j)
        {
            sum += data[j];
            if (sum > maxsum)
            {
                sum = maxsum;
            }
        }
    }

    return maxsum;
}

//方法二: 分治法 O(n*logn)
int findSubMaxSum1_help(int data[], int beg, int end)
{
    if (beg == end)
    {
        return data[beg];
    }

    int mid = beg + (end - beg) / 2;

    int leftmax = findSubMaxSum1_help(data, beg, mid);
    int rightmax = findSubMaxSum1_help(data, mid + 1, end);

    int maxsum = max(leftmax, rightmax);

    leftmax = numeric_limits<int>::min();
    rightmax = numeric_limits<int>::min();

    int leftsum = 0;
    int rightsum = 0;

    //求左侧的最大值
    for (int i = mid; i >=0; --i)
    {
        leftsum += data[i];
        if (leftsum > leftmax)
        {
            leftmax = leftsum;
        }
    }

    //求右侧的最大值
    for (int i = mid + 1; i <= end; ++i)
    {
        rightsum += data[i];
        if (rightsum > rightmax)
        {
            rightmax = rightsum;
        }
    }

    maxsum = max(maxsum, leftmax + rightmax);

    return maxsum;
}


int findSubMaxSum1(int data[], int n)
{
    assert(data != NULL && n > 0);

    return findSubMaxSum1_help(data, 0, n - 1);
}

int findSubMaxSum(int data[], int n)
{
    assert(data != NULL && n > 0);

    int sum = 0, maxsum = numeric_limits<int>::min();
    for (int i = 0; i < n; ++i)
    {
        sum += data[i];
        if (sum > maxsum)
        {
            maxsum = sum;
        }

        if (sum < 0)
        {
            sum = 0;
        }
    }

    return maxsum;
}

//2.16  求数组中最长递增子序列
//方法一:
int LIS(int data[], int n)
{
    assert(data != NULL && n > 0);

    vector<int> lis(n, 1);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (data[j] < data[i] && lis[j] + 1 > lis[i])
            {
                lis[i] = lis[j] + 1;
            }
        }
    }

    return *max_element(lis.begin(), lis.end());
}


//方法二: 好好想一下该方法， 以及改进方式
int LIS1(int data[], int n)
{
    assert(data != NULL && n > 0);

    vector<int> maxv(n + 1);
    maxv[0] = *min_element(data, data + n) - 1;
    maxv[1] = data[0];

    vector<int> lis(n, 1);

    int maxlis = 1;
    for (int i = 1; i < n; ++i)
    {
        int j;
        for (j = maxlis; j >= 0; --j)
        {
            if (data[i] > maxv[j])
            {
                lis[i] = j + 1;
                break;
            }
        }

        if (lis[i] > maxlis)
        {
            maxlis = lis[i];
            maxv[lis[i]] = data[i];
        }
        else if (maxv[j] < data[i] && data[i] < maxv[j+1])
        {
            maxv[j+1] = data[i];
        }
    }

    return maxlis;
}


//2.17 数组循环移位
//设计一个算法,把一个含有N个元素的数组循环右移K位, 要求时间复杂度为O(n), 且只允许使用两个附加变量
void reversearray(int data[], int beg, int end)
{
    assert(data != NULL && beg <= end);

    while (beg < end)
    {
        swap(data[beg++], data[end--]);
    }
}

void rotatearray1(int data[], int n, int k)
{
    assert(data != NULL && n > 0);

    k %= n;

    reversearray(data, 0, n - k - 1);
    reversearray(data, n - k, n - 1);

    reversearray(data, 0, n - 1);
}

//2.18 数组分割
//有一个无序, 元素个数为2n的正整数数组, 要求: 如何能把这个数组分割为元素个数为n的两个数组, 并且两个数组的和最接近
//方法一:

//2.19 区间重合判断
//方法二
bool judgeDistance(vector<pair<int, int> > &dest, pair<int, int> &source)
{
    //O(nlogn)
    sort(dest.begin(), dest.end(), [] (const pair<int, int> &a, const pair<int, int> &b) { return a.first < b.first; });

    //O(n)
    vector<pair<int, int> > newdest;
    pair<int, int> p = dest[0];
    for (int i = 1; i < dest.size(); ++i)
    {
        if (p.second >= dest[i].first)
        {
            p.second = dest[i].second;
        }
        else
        {
            newdest.push_back(p);
            p = newdest[i];
        }
    }
    newdest.push_back(p);

    for (int i = 0; i < newdest.size(); ++i)
    {
        if (newdest[i].first <= source.first && newdest[i].second >= source.second)
        {
            return true;
        }
    }

    return false;
}


//3.1 字符串移位包含的问题
//给定两个字符串s1和s2, 要求判断s2是否能够被s1做循环移位,得到的字符串包含
bool containRotate(char *s1, char *s2)
{
    assert(s1 != NULL && s2 != NULL);

    int len1 = strlen(s1);
    int len2 = strlen(s2);

    char *buf = new char[len1 + len2 + 1];
    strcpy(buf, s1);
    strcpy(buf + len1, s2);

    return strstr(buf, s2) != NULL;
}

//3.2 电话号码对应英语单词


//3.3 计算字符串的相似度
//两个不同字符串变化为相同可以下述方法:
//  1) 修改一个字符
//  2) 增加一个字符
//  3) 删除一个字符
//把两个字符串变化为相同操作的次数定义为两个字符串的距离, 距离加一的倒数定义为相似度

int calculateStringDistance_help(char *s1, int beg1, int end1, char *s2, int beg2, int end2, map<pair<int, int>, int> &keep)
{
    if (beg1 > end1 && beg2 > end2)
    {
        return 0;
    }
    else if (beg1 > end1)
    {
        return end2 - beg2 + 1;
    }
    else if (beg2 > end2)
    {
        return end1 - beg1 + 1;
    }

    pair<int, int> p = make_pair(beg1, beg2);
    if (keep.find(p) != keep.end())
    {
        return keep[p];
    }

    int d;
    if (s1[beg1] == s2[beg2])
    {
        d = calculateStringDistance_help(s1, beg1 + 1, end1, s2, beg2 + 1, end2, keep);
    }
    else
    {
        int d1 = calculateStringDistance_help(s1, beg1, end1, s2, beg2 + 1, end2, keep);
        int d2 = calculateStringDistance_help(s1, beg1 + 1, end1, s2, beg2, end2, keep);
        int d3 = calculateStringDistance_help(s1, beg1 + 1, end1, s2, beg2 + 1, end2, keep);

        d = min({d1, d2, d3}) + 1;
    }

    keep[p] = d;

    return d;
}

int calculateStringDistance(char *s1, char *s2)
{
    assert(s1 != NULL && s2 != NULL);

    int len1 = strlen(s1);
    int len2 = strlen(s2);
    map<pair<int, int>, int> keep;
    return calculateStringDistance_help(s1, 0, len1 - 1, s2, 0, len2 - 1, keep);
}

//3.4 从无头链表中删除节点
struct Node
{
    int data;
    Node *next;

    Node(int d) : data(d), next(NULL) {}
};

void deleteNode(Node *&root, Node *delNode)
{
    assert(root != NULL && delNode != NULL);

    Node *next = delNode->next;
    if (next != NULL)
    {
        delNode->data = next->data;
        delNode->next = next->next;

        delete next;
    }
    else
    {
        if (root == delNode)
        {
            root = NULL;
            delete delNode;

            return ;
        }

        next = root;
        while (next->next != delNode)
        {
            next = next->next;
        }

        next->next = NULL;

        delete delNode;
    }
}

Node *reverseList(Node *root)
{
    assert(root != NULL);

    Node *head = NULL;
    Node *next = NULL;
    while (root != NULL)
    {
        next = root->next;

        root->next = head;
        head = root;

        root = next;
    }

    return head;
}

Node *reverseListRecu(Node *root)
{
    assert(root != NULL);

    if (root->next == NULL)
    {
        return root;
    }

    Node *head = reverseListRecu(root->next);
    root->next->next = root;
    root->next = NULL;

    return head;
}

//3.6 编程判断两个链表是否相交
//方法一: 直观判断 O(n*2)
bool twoList(Node *l1, Node *l2)
{
    if (l1 == NULL || l2 == NULL)
    {
        return false;
    }

    Node *cur = NULL;
    while (l1 != NULL)
    {
        cur = l2;
        while (cur != NULL)
        {
            if (cur == l1)
            {
                return false;
            }
        }
    }

    return true;
}

//方法二: hash法 O(n)  需要O(n)空间
bool twoList1(Node *l1, Node *l2)
{
    if (l1 == NULL || l2 == NULL)
    {
        return false;
    }

    unordered_set<Node *> m;
    while (l1 != NULL)
    {
        m.insert(l1);
        l1 = l1->next;
    }

    while (l2 != NULL)
    {
        if (m.find(l2) != m.end())
        {
            return false;
        }
    }

    return true;
}

//方法三: 转转为已知问题方法  (将问题转换为判断链表中是否有圆)  破坏了输入数据
bool twoList2(Node *l1, Node *l2)
{
    if (l1 == NULL || l2 == NULL)
    {
        return false;
    }

    Node *cur = l1;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }

    cur->next = l2;

    //判断链表中是否有圆
    Node *slow = l1;
    Node *fast = l1;
    while (fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            return false;
        }
    }


    return true;
}

//方法四:  最简单的方法
bool twoList3(Node *l1, Node *l2)
{
    if (l1 == NULL || l2 == NULL)
    {
        return false;
    }

    while (l1->next != NULL)
    {
        l1 = l1->next;
    }

    while (l2->next != NULL)
    {
        l2 = l2->next;
    }


    return l1 == l2;
}

//如果链表上可能有环
//先检测两个链表上是否有环，如果一个链表有环，另一个没有那么肯定没有相交
//对于两个有环的链表，使用乌龟兔子法在环中将链表断开, 然后检测另一个是否还有环

//求出链表相交的第一个点
Node *twoList4(Node *l1, Node *l2)
{
    if (l1 == NULL || l2 == NULL)
    {
        return NULL;
    }

    Node *kl1 = l1;
    Node *kl2 = l2;

    int len1 = 1;
    while (l1->next != NULL)
    {
        l1 = l1->next;
        ++len1;
    }

    int len2 = 1;
    while (l2->next != NULL)
    {
        l2 = l2->next;
        ++len2;
    }

    if (l1 != l2)
    {
        return NULL;
    }

    l1 = kl1;
    l2 = kl2;
    if (len1 < len2)
    {
        swap(l1, l2);
        swap(len1, len2);
    }

    int off = len1 - len2;
    while (off--)
    {
        l1 = l1->next;
    }

    while (l1 != NULL)
    {
        if (l1 == l2)
        {
            break;
        }

        l1 = l1->next;
        l2 = l2->next;
    }

    return l1;
}


int main()
{

    int data[] = {49, 49, 36, 38, 65, 76, 13, 27, 49};
    int len = sizeof(data) / sizeof(data[0]);

    copy(data, data + len, ostream_iterator<int>(cout, " "));
    cout << endl;

    kmax1(data, len, 4);

    int data1[] = {5, 6, 1,4, 7, 9, 8};
    int len1 = sizeof(data1) / sizeof(data1[0]);
    SumPair p = findSum(data1, len1, 10);
    p = findSum2(data1, len1, 10);
    p = findSum3(data1, len1, 10);
    p = findSum4(data1, len1, 10);
    cout << p.first << " " << p.second << endl;

    ThreeTuple t = findThreeSum(data1, len1, 14);
    cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;

    p = findSumClose(data1, len1, 4);
    cout << p.first << " " << p.second << endl;

    int data2[] = {-2, 5, 3, -6, 4, -8, 6};
    int len2 = sizeof(data2) / sizeof(data2[0]);
    cout << findSubMaxSum(data2, len2) << endl;
    cout << findSubMaxSum1(data2, len2) << endl;

    int data3[] = {1, -1, 2, -3, 4, -5, 6, -7};
    int len3 = sizeof(data3) / sizeof(data3[0]);
    cout << LIS(data3, len3) << endl;
    cout << LIS1(data3, len3) << endl;

    rotatearray1(data3, len3, 3);
    copy(data3, data3 + len3, ostream_iterator<int>(cout, " "));
    cout << endl;


    vector<pair<int, int> > data4{make_pair(1, 3), make_pair(1, 2), make_pair(1, 5)};
    pair<int, int> source = make_pair(1, 6);
    cout << judgeDistance(data4, source) << endl;

    char s1[] = "AABCD";
    char s2[] = "CDAA";
    cout << containRotate(s1, s2) << endl;

    Node *root = new Node(1);
    root->next = new Node(2);
    root->next->next = new Node(3);
    root->next->next->next = new Node(4);
    root = reverseListRecu(root);
    while (root != NULL)
    {
        cout << root->data << " ";
        root = root->next;
    }
    cout << endl;
    return 0;
}
