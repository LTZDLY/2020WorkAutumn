#include <iostream>
#include <cctype>
#include <cmath>
#include <vector>
#include <string>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;

/* 返回每个运算符对应的优先级 */
inline int priority(const char &ch)
{
    switch (ch)
    {
    // 加减的优先级最低，我们设为1
    case '+':
    case '-':
        return 1;
    // 乘除的优先级其次，设为2
    case '*':
    case '/':
        return 2;
    // 注意这里有乘方运算，而样例里没有，最开始我就栽在这里了QwQ
    // 乘方的优先级最高，设为3
    case '%':
        return 3;
    case '^':
        return 4;
    // 括号优先级另行处理，这里可以不写
    case '(':
    case ')':
        return 0;
    // 防止意外情况导致RE，default可写可不写
    default:
        return -1;
    }
}

/* 将中缀表达式转换为后缀表达式 */
inline string toSuffix(const string &s)
{
    string ret = ""; // 用于返回的后缀表达式
    stack<char> st;  // 用于实现转换的栈
    for (register int i = 0; i < s.size(); i++)
    { // 枚举每一位
        if (isdigit(s[i]))
        { // 如果为数字，直接输出到结果中
            ret += s[i];
        }
        else if (s[i] == '(')
        { // 如果为左括号，直接加入栈中
            st.push(s[i]);
        }
        else if (s[i] == ')')
        {                                  // 如果为右括号，
            while (st.top() != '(')        // 一直弹出并输出直到遇到左括号，
                ret += st.top(), st.pop(); // 并弹出左括号
            st.pop();
        }
        else
        { // 否则即为普通的运算符，
            while (!st.empty() && priority(st.top()) >= priority(s[i]))
                ret += st.top(), st.pop(); // 一直弹出并输出直到遇到比当前优先级低的运算符，
            st.push(s[i]);                 // 最后把当前运算符压入栈中
        }
    }
    while (!st.empty()) // 最后如果栈中还有剩余的字符，直接弹出并输出
        ret += st.top(), st.pop();
    return ret; // 最后返回结果
}

/* 根据运算符计算相应的运算结果 */
inline int calcNum(const int &a, const int &b, const int &symbol)
{
    switch (symbol)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '%':
        return a % b;
    case '^':
        return (int)pow(a, b);
    default: // 与上面同理，default可写可不写
        return -1;
    }
}

/* 将后缀表达式加上空格后输出 */
inline void printSuffix(const string &s)
{
    for (register int i = 0; i < s.size(); i++)
        cout << s[i] << ' ';
    cout << endl;
}

/* 计算后缀表达式并输出计算过程 */
inline void calc(const string &s)
{
    /**
     * 实现计算的数字栈，为了输出方便(不需要将每个元素弹出)
     * 并且为了使压入和弹出操作的时间复杂度降到O(1)，
     * 这里没有使用vector而是使用了list(链表)
     */
    list<int> st;
    printSuffix(s); // 注意要先输出后缀表达式，我之前栽在这里了QwQ
    for (register int i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i]))
        { // 如果遇到数字直接压入栈
            st.push_back(s[i] - '0');
        }
        else
        {                      // 否则计算结果并压入栈
            register int a, b; //取出栈顶的两个元素
            a = st.back();
            st.pop_back();
            b = st.back();
            st.pop_back();
            st.push_back(calcNum(b, a, s[i])); // 注意计算顺序
            // 每计算一次输出一次计算过程
            for (list<int>::iterator it = st.begin(); it != st.end(); ++it)
                cout << *it << ' '; // 输出栈中已计算过的数
            for (register int j = i + 1; j < s.size(); j++)
                cout << s[j] << ' '; // 再输出还未计算过的数
            cout << endl;
        }
    }
}

void loop(){
    string s;
    string ss = "";
    cout << "输入表达式：";
    cin >> s;    
    int flag = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        if ((s[i] == '+' || s[i] == '-') && (i == 0 || (s[i - 1] != ')' && !isdigit(s[i - 1]))))
        {
            ss += '(';
            ss += '0';
            ss += s[i];
            flag++;
            continue;
        }
        ss += s[i];
        for (size_t i = 0; i < flag; i++)
            ss += ')';
        flag = 0;
    }
    cout << ss << endl;
    calc(toSuffix(ss));
}

int main()
{
    char flag;
    do
    {
        loop();
        cout << "是否继续？(y, n)";
        char c;
        cin >> c;
        flag = c;
    } while (flag == 'y');
}