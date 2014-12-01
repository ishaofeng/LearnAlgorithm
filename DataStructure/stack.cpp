#include <iostream>
#include <stack>

using namespace std;

string inorderToPostOrder(string &s)
{
    stack<char> ss;
    string r;
    for (int i = 0; i < s.length(); ++i)
    {
        switch (s[i])
        {
            case '*':
                if (ss.empty() || ss.top() == '+' || ss.top() == '(')
                {
                    ss.push('*');
                }
                else
                {
                    r.push_back('*');
                }
                break;

            case '+':
                while (!ss.empty() && (ss.top() == '*' || ss.top() == '+') && ss.top() != '(')
                {
                    r.push_back(ss.top());
                    ss.pop();
                }
                ss.push('+');
                break;

            case '(':
                ss.push('(');
                break;

            case ')':
                while (!ss.empty() && ss.top() != '(')
                {
                    r.push_back(ss.top());
                    ss.pop();
                }
                if (!ss.empty())
                {
                    ss.pop();
                }
                break;

            default:
                r.push_back(s[i]);
        }
    }

    while (!ss.empty())
    {
        r.push_back(ss.top());
        ss.pop();
    }

    return r;
}

int main()
{
    string s = "a+b*c+(d*e+f)*g";
    cout << inorderToPostOrder(s) << endl;
}
