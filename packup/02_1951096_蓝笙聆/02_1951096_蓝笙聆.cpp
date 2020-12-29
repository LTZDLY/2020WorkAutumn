#include <iostream>
#include <sstream>
#include <string>

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
    T ListPop(T data);    //查找链表中的数据返回并删除节点
    int ListFind(T id);   //查找数据在链表中的位置
    int ListLen() const;  //返回链表长度
    bool Empty() const;   //返回是否为空
    void ListChange(int n, T data);      //修改链表第n个节点的值
    std::string ListPrint(int n) const;  //将链表输出
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
void findIntersection(List<T> &list_a, List<T> &list_b, List<T> &list_c) {
    for (int i = 0; i < list_a.ListLen(); i++) {
        if (list_b.ListFind(list_a[i]) != -1)
            list_c.ListIns(list_c.ListLen(), list_a[i]);
    }
}
void opening() {
    std::cout << "The Intersection of Two Ordered Chain List Sequences"
              << std::endl
              << "Please enter two ordered lists, ending with '-1'"
              << std::endl;
}
template <class T>
void insert(List<T> &list) {
    T temp;
    while (1) {
        std::cin >> temp;
        if (temp == "-1") break;
        list.ListIns(list.ListLen(), temp);
    }
}
template <class T>
void print(std::ostream &os, List<T> &list) {
    if (list.ListLen() == 0)
        os << "NULL";
    else
        for (int i = 0; i < list.ListLen(); i++) os << list.ListPrint(i) << ' ';
    std::cout << std::endl;
}
bool loop(){
    opening();
    List<std::string> list_a;
    List<std::string> list_b;
    List<std::string> list_c;
    insert(list_a);
    insert(list_b);
    findIntersection(list_a, list_b, list_c);
    print(std::cout, list_c);

    std::cout << "Again? (y for yes, n for no)";
    char c;
    std::cin >> c;
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