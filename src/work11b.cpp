#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <list>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

double str2num(string s) {
    stringstream ss;
    double d = 0.0;
    ss << s;
    ss >> d;
    return d;
}

inline bool isVariable(char c) { return (c == '1' || (c >= 'a' && c <= 'z')); }

/* 返回每个运算符对应的优先级 */
int priority(const char &ch) {
    switch (ch) {
        // 规定五个联结词优先级顺序是 ￢ ∧ ∨ -> <->
        // 等值式的优先级最低，我们设为1
        case '~':
            return 1;
        // 蕴含式的优先级其次，设为2
        case '^':
            return 2;
        // 或的优先级其次，设为3
        case '|':
            return 3;
        // 与的优先级其次，设为4
        case '&':
            return 4;
        // 非的优先级最高，设为5
        case '-':
            return 5;
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
string toSuffix(const string &s) {
    string ret = "";                      // 用于返回的后缀表达式
    stack<char> st;                       // 用于实现转换的栈
    for (int i = 0; i < s.size(); i++) {  // 枚举每一位
        if (isVariable(s[i])) {  // 如果为数字或小数点，直接输出到结果中
            ret += s[i];
        } else if (s[i] == '(') {  // 如果为左括号，直接加入栈中
            st.push(s[i]);
        } else if (s[i] == ')') {  // 如果为右括号，
            while (st.top() != '(')  // 一直弹出并输出直到遇到左括号，
                ret += ' ', ret += st.top(), st.pop();  // 并弹出左括号
            st.pop();
        } else {  // 否则即为普通的运算符，
            ret += ' ';
            while (!st.empty() && priority(st.top()) >= priority(s[i]))
                ret += st.top(), ret += ' ',
                    st.pop();  // 一直弹出并输出直到遇到比当前优先级低的运算符，
            st.push(s[i]);  // 最后把当前运算符压入栈中
        }
    }
    while (!st.empty())  // 最后如果栈中还有剩余的字符，直接弹出并输出
        ret += ' ', ret += st.top(), st.pop();
    return ret;  // 最后返回结果
}

/* 根据运算符计算相应的运算结果 */
int calcNum(const int &a, const int &b, const int &symbol) {
    switch (symbol) {
        case '&':
            return a & b;
        case '|':
            return a | b;
        case '-':
            return a - b;
        case '^':
            return (1 - a) | b;
        case '~':
            return 1 - (a ^ b);
        default:  // 与上面同理，default可写可不写
            return -1;
    }
}

/* 计算后缀表达式并输出计算过程 */
int calc(string s, vector<char> v, vector<int> num) {
    /**
     * 实现计算的数字栈，为了输出方便(不需要将每个元素弹出)
     * 这里使用vector
     */
    while (num.size() != v.size()) num.push_back(0);
    for (int i = 0; i < v.size(); i++)
        for (auto &&j : s)
            if (j == v[v.size() - i - 1]) j = num[i] + '0';
    vector<int> st;
    // cout << s << endl;  // 先输出后缀表达式
    string str;
    for (int i = 0; i <= s.size(); i++) {
        if (i != s.size() && s[i] != ' ')
            str += s[i];
        else {
            int temp = -1;
            if (isdigit(str[0])) {  // 如果遇到数字直接压入栈
                temp = str2num(str);
                st.push_back(temp);
            } else {       // 否则计算结果并压入栈
                int a, b;  //取出栈顶的两个元素
                a = st.back();
                st.pop_back();
                b = st.back();
                st.pop_back();
                st.push_back(calcNum(b, a, str[0]));  // 注意计算顺序
                // 每计算一次输出一次计算过程
                /*
                for (auto &&i : st) cout << i << ' ';  // 输出栈中已计算过的数
                for (int j = i + 1; j < s.size(); j++)
                    cout << s[j];  // 再输出还未计算过的数
                cout << endl;
                */
            }
            str = "";
        }
    }
    return st[0];
}
bool effective(string s) {
    if (s.size() == 0 || (s.size() == 1 && !isVariable(s[0]))) return false;
    int brackets = 0;
    if (s[0] == '(') brackets++;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == '(')
            brackets++;
        else if (s[i] == ')')
            brackets--;
        if (brackets < 0) return false;
        if (!isVariable(s[i]) && !isVariable(s[i - 1])) {
            if (s[i] != '!' && s[i] != '(' && s[i - 1] != ')') return false;
        }
    }
    if (brackets != 0) return false;
    return true;
}
bool loop() {
    string s;
    string ss = "";
    vector<char> v;
    cout << "Please enter an expression. " << endl;
    cin >> s;
    while (!effective(s)) {
        cout << "An invalid expression was detected. Please try again." << endl;
        cin >> s;
    }
    for (auto &&i : s) {
        bool fflag = true;
        if (isVariable(i)) {
            for (auto &&j : v)
                if (i == j) {
                    fflag = false;
                    break;
                }
            if (fflag) v.push_back(i);
        }
    }
    sort(v.begin(), v.end());
    int flag = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if ((s[i] == '!') &&
            (i == 0 || (s[i - 1] != ')' && !isVariable(s[i - 1])))) {
            ss += '(';
            ss += '1';
            ss += '-';
            flag++;
            continue;
        }
        ss += s[i];
        if (i != s.size() - 1 && isVariable(s[i + 1])) continue;
        for (size_t i = 0; i < flag; i++) ss += ')';
        flag = 0;
    }
    auto sss = toSuffix(ss);
    int len = pow(2, v.size());
    vector<int> mdisjunctive;  //主析取范式
    vector<int> mconjunctive;  //主合取范式
    vector<int> num(v.size());
    for (auto &&i : v) cout << i << "    ";
    cout << s << endl;
    for (int i = 0; i < len; i++) {
        int n = i;
        int j = 0;
        while (n >= 2) {
            num[j] = n % 2;
            n /= 2;
            j++;
        }
        num[j] = n;
        j++;
        for (j; j < v.size(); j++) num[j] = 0;
        int temp = calc(sss, v, num);
        for (auto &&k : num) cout << k << "    ";
        cout << temp << endl;
        if (temp == 1)
            mdisjunctive.push_back(i);
        else
            mconjunctive.push_back(i);
    }
    if (mconjunctive.size() == 0)
        cout << "There is no principal conjunctive normal form in this proposition formula." << endl;
    else {
        cout << "The main conjunctive normal form of the proposition formula is as follows:" << endl;
        cout << "    M(" << mconjunctive[0] << ")";
        for (int i = 1; i < mconjunctive.size(); i++)
            cout << "\\/M(" << mconjunctive[i] << ")";
        cout << endl;
    }
    if (mdisjunctive.size() == 0)
        cout << "There is no principal disjunctive normal form in the propositional formula." << endl;
    else {
        cout << "The main disjunctive normal form of the proposition formula is as follows:" << endl;
        cout << "    m(" << mdisjunctive[0] << ")";
        for (int i = 1; i < mdisjunctive.size(); i++)
            cout << "/\\m(" << mdisjunctive[i] << ")";
        cout << endl;
    }
    cout << "Again? (y for yes, n for no)";
    char c;
    cin >> c;
    if (c == 'y')
        return true;
    else
        return false;
}

int main() {
    while (loop())
        ;
    std::cout << "Thanks for using it. See you next time! " << std::endl;
    return 0;
}