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

template <class T>
struct Node {
    T _data;      //数据
    Node *_next;  //指针域
    Node();
};

template <class T>
Node<T>::Node() {
    this->_next = nullptr;
}

template <class T>
class List {
   private:
    Node<T> *_head;  //表头结点
    int _len;        //链表长度

   public:
    T &operator[](int i);
    void ListIns(int n, T data);  //将数据插入第n个节点中
    void ListDel(int n);          //删除第n个节点
    T ListPop(T data);    //查找链表中的数据返回并删除节点
    int ListFind(T id);   //查找数据在链表中的位置
    int ListLen() const;  //返回链表长度
    bool Empty() const;   //返回是否为空
    void ListChange(int n, T data);  //修改链表第n个节点的值
    Node<T> *GetHead() const { return this->_head; }  //返回头结点
    std::string ListPrint(int n) const;               //将链表输出
    List();
    ~List();
};

template <class T>
T &List<T>::operator[](int n) {
    if (this->Empty()) throw "Error: The list is empty.";
    auto p = this->_head->_next;
    for (int i = 0; i < n; i++) {
        if (p->_next == nullptr) throw "Error: Not so many nodes.";
        p = p->_next;
    }
    return p->_data;
}

template <class T>
bool List<T>::Empty() const {
    if (this->_head->_next == nullptr)
        return true;
    else
        return false;
}
template <class T>
List<T>::List() {
    this->_head = new Node<T>;
    this->_len = 0;
}

template <class T>
List<T>::~List() {
    Node<T> *p = this->_head;
    if (p->_next == nullptr) {
        delete p;
        return;
    }
    p = p->_next;
    while (p->_next != nullptr) {
        auto node = p;
        p = p->_next;
        delete node;
    }
    delete this->_head;
}

template <class T>
void List<T>::ListIns(int n, T data) {
    Node<T> *p = this->_head;
    for (int i = 0; i < n; i++) {
        if (p->_next == nullptr) throw "Error: Not so many nodes.";
        p = p->_next;
    }
    Node<T> *node = new Node<T>;
    node->_data = data;
    node->_next = p->_next;
    p->_next = node;
    this->_len++;
}

template <class T>
void List<T>::ListDel(int n) {
    Node<T> *p = this->_head;
    for (int i = 0; i < n; i++) {
        if (p->_next == nullptr) throw "Error: Not so many nodes.";
        p = p->_next;
    }
    Node<T> *node = p->_next;
    p->_next = p->_next->_next;
    delete node;
    this->_len--;
}

template <class T>
T List<T>::ListPop(T data) {
    if (this->Empty()) throw "Error: The list is Empty.";
    int n = this->ListFind(data);
    if (n == -1) throw "Error: Data not found.";
    Node<T> *p = this->_head;
    for (int i = 0; i < n; i++) {
        if (p->_next == nullptr) throw "Error: Not so many nodes.";
        p = p->_next;
    }
    Node<T> *node = p->_next;
    p->_next = p->_next->_next;
    auto i = node->_data;
    delete node;
    this->_len--;
    return i;
}

template <class T>
int List<T>::ListFind(T data) {
    if (this->Empty()) return -1;
    Node<T> *p = this->_head;
    p = p->_next;
    int i = 0;
    while (true) {
        if (p->_data == data) return i;
        if (p->_next == nullptr) return -1;
        p = p->_next;
        i++;
    }
}

template <class T>
int List<T>::ListLen() const {
    return this->_len;
}

template <class T>
void List<T>::ListChange(int n, T data) {
    if (this->Empty()) throw "Error: The list is Empty.";

    auto p = this->_head->_next;
    for (int i = 0; i < n; i++) {
        if (p->_next == nullptr) throw "Error: Not so many nodes.";
        p = p->_next;
    }
    p->_data = data;
}

template <class T>
std::string List<T>::ListPrint(int n) const {
    if (this->Empty()) throw "Error: The list is Empty.";

    auto p = this->_head->_next;
    for (int i = 0; i < n; i++) {
        if (p->_next == nullptr) throw "Error: Not so many nodes.";
        p = p->_next;
    }
    std::stringstream ss;
    ss << p->_data;
    return ss.str();
}

template <class T>
class Stack : public List<T> {
   public:
    void Push(T val);
    void Pop();
    T Top();
};

template <class T>
void Stack<T>::Push(T val) {
    this->ListIns(0, val);
}
template <class T>
void Stack<T>::Pop() {
    this->ListDel(0);
}
template <class T>
T Stack<T>::Top() {
    if (this->Empty()) throw "Error: The list is Empty.";
    return this->GetHead()->_next->_data;
}

double str2num(string s) {
    stringstream ss;
    double d = 0.0;
    ss << s;
    ss >> d;
    return d;
}

/* 返回每个运算符对应的优先级 */
int priority(const char &ch) {
    switch (ch) {
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
string toSuffix(const string &s) {
    string ret = "";                      // 用于返回的后缀表达式
    Stack<char> st;                       // 用于实现转换的栈
    for (int i = 0; i < s.size(); i++) {  // 枚举每一位
        if (s[i] == '.' ||
            isdigit(s[i])) {  // 如果为数字或小数点，直接输出到结果中

            ret += s[i];
        } else if (s[i] == '(') {  // 如果为左括号，直接加入栈中
            st.Push(s[i]);
        } else if (s[i] == ')') {  // 如果为右括号，
            while (st.Top() != '(')  // 一直弹出并输出直到遇到左括号，
                ret += ' ', ret += st.Top(), st.Pop();  // 并弹出左括号
            st.Pop();
        } else {  // 否则即为普通的运算符，
            ret += ' ';
            while (!st.Empty() && priority(st.Top()) >= priority(s[i]))
                ret += st.Top(), ret += ' ',
                    st.Pop();  // 一直弹出并输出直到遇到比当前优先级低的运算符，
            st.Push(s[i]);  // 最后把当前运算符压入栈中
        }
    }
    while (!st.Empty())  // 最后如果栈中还有剩余的字符，直接弹出并输出
        ret += ' ', ret += st.Top(), st.Pop();
    return ret;  // 最后返回结果
}

/* 根据运算符计算相应的运算结果 */
double calcNum(const double &a, const double &b, const int &symbol) {
    switch (symbol) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '%':
            return fmod(a, b);
        case '^':
            return (double)pow(a, b);
        default:  // 与上面同理，default可写可不写
            return -1;
    }
}

/* 将后缀表达式加上空格后输出 */
void printSuffix(const string &s) {
    for (int i = 0; i < s.size(); i++) cout << s[i];
    cout << endl;
}

/* 计算后缀表达式并输出计算过程 */
void calc(const string &s) {
    /**
     * 实现计算的数字栈，为了输出方便(不需要将每个元素弹出)
     * 这里使用vector
     */
    vector<double> st;
    printSuffix(s);  // 先输出后缀表达式
    string str;
    for (int i = 0; i <= s.size(); i++) {
        if (i != s.size() && s[i] != ' ')
            str += s[i];
        else {
            double temp = -1;
            if (isdigit(str[0])) {  // 如果遇到数字直接压入栈
                temp = str2num(str);
                st.push_back(temp);
            } else {          // 否则计算结果并压入栈
                double a, b;  //取出栈顶的两个元素
                a = st.back();
                st.pop_back();
                b = st.back();
                st.pop_back();
                st.push_back(calcNum(b, a, str[0]));  // 注意计算顺序
                // 每计算一次输出一次计算过程
                for (auto &&i : st) cout << i << ' ';  // 输出栈中已计算过的数
                for (int j = i + 1; j < s.size(); j++)
                    cout << s[j];  // 再输出还未计算过的数
                cout << endl;
            }
            str = "";
        }
    }
}
bool effective(string s) {
    if (s.size() == 0 || (s.size() == 1 && !isdigit(s[0]))) return false;
    int brackets = 0;
    if (s[0] == '(') brackets++;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == '(')
            brackets++;
        else if (s[i] == ')')
            brackets--;
        if (brackets < 0) return false;
        if (!isdigit(s[i]) && !isdigit(s[i - 1])) {
            if (s[i] != '+' && s[i] != '-' && s[i] != '(' && s[i - 1] != ')')
                return false;
        }
    }
    if (brackets != 0) return false;
    return true;
}
bool loop() {
    string s;
    string ss = "";
    cout << "Please enter an expression. " << endl;
    cin >> s;
    while (!effective(s)) {
        cout << "An invalid expression was detected. Please try again." << endl;
        cin >> s;
    }
    int flag = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if ((s[i] == '+' || s[i] == '-') &&
            (i == 0 || (s[i - 1] != ')' && !isdigit(s[i - 1])))) {
            ss += '(';
            ss += '0';
            ss += s[i];
            flag++;
            continue;
        }
        ss += s[i];
        if (i != s.size() - 1 && isdigit(s[i + 1])) continue;
        for (size_t i = 0; i < flag; i++) ss += ')';
        flag = 0;
    }
    cout << ss << endl;
    calc(toSuffix(ss));

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