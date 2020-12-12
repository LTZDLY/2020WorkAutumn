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
    void listIns(int n, T data);  //将数据插入第n个节点中
    T listPop(T data);    //查找链表中的数据返回并删除节点
    int listFind(T id);   //查找数据在链表中的位置
    int listLen() const;  //返回链表长度
    bool empty() const;   //返回是否为空
    void listChange(int n, T data);      //修改链表第n个节点的值
    std::string listPrint(int n) const;  //将链表输出
    List();
    ~List();
};

template <class T>
bool List<T>::empty() const {
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
void List<T>::listIns(int n, T data) {
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
T List<T>::listPop(T data) {
    if (this->empty()) throw "Error: The list is empty.";
    int n = this->listFind(data);
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
int List<T>::listFind(T data) {
    if (this->empty()) return -1;
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
T &List<T>::operator[](int n) {
    if (this->empty()) throw "Error: The list is empty.";
    auto p = this->_head->_next;
    for (int i = 0; i < n; i++) {
        if (p->_next == nullptr) throw "Error: Not so many nodes.";
        p = p->_next;
    }
    return p->_data;
}

template <class T>
int List<T>::listLen() const {
    return this->_len;
}

template <class T>
void List<T>::listChange(int n, T data) {
    if (this->empty()) throw "Error: The list is empty.";

    auto p = this->_head->_next;
    for (int i = 0; i < n; i++) {
        if (p->_next == nullptr) throw "Error: Not so many nodes.";
        p = p->_next;
    }
    p->_data = data;
}

template <class T>
std::string List<T>::listPrint(int n) const {
    if (this->empty()) throw "Error: The list is empty.";

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
    for (int i = 0; i < list_a.listLen(); i++) {
        if (list_b.listFind(list_a[i]) != -1)
            list_c.listIns(list_c.listLen(), list_a[i]);
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
        list.listIns(list.listLen(), temp);
    }
}
template <class T>
void print(std::ostream &os, List<T> &list) {
    if (list.listLen() == 0)
        os << "NULL";
    else
        for (int i = 0; i < list.listLen(); i++) os << list.listPrint(i) << ' ';
    std::cout << std::endl;
}

int main() {
    opening();
    List<std::string> list_a;
    List<std::string> list_b;
    List<std::string> list_c;
    insert(list_a);
    insert(list_b);
    findIntersection(list_a, list_b, list_c);
    print(std::cout, list_c);
    return 0;
}