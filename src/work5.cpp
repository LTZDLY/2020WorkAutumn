#include <algorithm>
#include <iostream>
#include <sstream>
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
class Priorityqueue : public List<T> {
   private:
   public:
    void Push(T val);  //插入元素并按升序排列
    void Pop();        //移除队首
    T Top();           //返回队首
};

template <class T>
void Priorityqueue<T>::Push(T val) {
    if (this->Empty()) {
        this->ListIns(0, val);
        return;
    }
    int i = 0;
    auto p = this->GetHead();
    while (p->_next != nullptr) {
        p = p->_next;
        if (val < p->_data) {
            this->ListIns(i, val);
            return;
        }
        i++;
    }
    this->ListIns(i, val);
}
template <class T>
void Priorityqueue<T>::Pop() {
    this->ListDel(0);
}
template <class T>
T Priorityqueue<T>::Top() {
    if (this->Empty()) throw "Error: The list is Empty.";
    return this->GetHead()->_next->_data;
}

void opening() {
    cout << "Banking Business" << endl
         << "The input is a line of positive integers. " << endl
         << "The first number is N followed by the number of N customers. "
         << endl
         << "Now enter a line of positive integers. " << endl;
    return;
}
void input(Priorityqueue<int> &a, Priorityqueue<int> &b) {
    string temps;
    int num = 0;
    cin >> temps;
    if (isdigit(temps[0]))
        num = temps[0] - '0';
    else
        throw "Error: Invalid input detected. Please try again.";
    for (int i = 0; i < num; i++) {
        int temp;
        cin >> temps;
        if (isdigit(temps[0]))
            temp = temps[0] - '0';
        else
            throw "Error: Invalid input detected. Please try again.";
        if (temp % 2 == 1)
            a.Push(temp);
        else
            b.Push(temp);
    }
}
int main() {
    opening();
    Priorityqueue<int> a, b;
    while (true) {
        try {
            input(a, b);
            break;
        } catch (const char *e) {
            std::cerr << e << '\n';
        }
    }
    while (!a.Empty() || !b.Empty()) {
        if (!a.Empty()) cout << a.Top() << ' ', a.Pop();
        if (!a.Empty()) cout << a.Top() << ' ', a.Pop();
        if (!b.Empty()) cout << b.Top() << ' ', b.Pop();
    }
    cout << endl;
    return 0;
}