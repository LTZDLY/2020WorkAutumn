#include <string>
#include <sstream>

template <class T>
struct Node
{
    T _data;
    Node *_next;
    Node();
};

template <class T>
Node<T>::Node()
{
    this->_next = nullptr;
}

template <class T>
class List
{
private:
    Node<T> *_head;
    int _len;

public:
    T &operator[](int i);
    void listIns(int n, T data);
    std::string listPop(T data);
    int listFind(T id);
    int listLen() const;
    void listChange(int n, T data);
    std::string listPrint(int n) const;
    List(/* args */);
    ~List();
};

template <class T>
T &List<T>::operator[](int n)
{
    Node<T> *p = this->_head;
    if (p->_next == nullptr)
    {
        throw "error0";
    }
    p = p->_next;
    for (int i = 0; i < n; i++)
    {
        if (p->_next == nullptr)
            throw "error";
        p = p->_next;
    }
    return p->_data;
}

template <class T>
List<T>::List(/* args */)
{
    this->_head = new Node<T>;
    this->_len = 0;
}

template <class T>
List<T>::~List()
{
    Node<T> *p = this->_head;
    if (p->_next == nullptr)
    {
        delete p;
        return;
    }
    p = p->_next;
    while (p->_next != nullptr)
    {
        auto node = p;
        p = p->_next;
        delete node;
    }
    delete this->_head;
}

template <class T>
void List<T>::listIns(int n, T data)
{
    Node<T> *p = this->_head;
    for (int i = 0; i < n; i++)
    {
        if (p->_next == nullptr)
            throw "error";
        p = p->_next;
    }
    Node<T> *node = new Node<T>;
    node->_data = data;
    node->_next = p->_next;
    p->_next = node;
    this->_len++;
}

template <class T>
std::string List<T>::listPop(T data)
{
    int n = this->listFind(data);
    Node<T> *p = this->_head;
    for (int i = 0; i < n; i++)
    {
        if (p->_next == nullptr)
            throw "error";
        p = p->_next;
    }
    std::string str = listPrint(n);
    Node<T> *node = p->_next;
    p->_next = p->_next->_next;
    delete node;
    this->_len--;
    return str;
}

template <class T>
int List<T>::listFind(T data)
{
    Node<T> *p = this->_head;
    if (p->_next == nullptr)
    {
        throw "error0";
    }
    p = p->_next;
    int i = 0;
    while (1)
    {
        if (p->_data == data)
            return i;
        if (p->_next == nullptr)
            return -1;
        p = p->_next;
        i++;
    }
}

template <class T>
int List<T>::listLen() const { return this->_len; }

template <class T>
void List<T>::listChange(int n, T data)
{
    Node<T> *p = this->_head;
    if (p->_next == nullptr)
    {
        throw "error0";
    }
    p = p->_next;
    for (int i = 0; i < n; i++)
    {
        if (p->_next == nullptr)
            throw "error";
        p = p->_next;
    }
    p->_data = data;
}

template <class T>
std::string List<T>::listPrint(int n) const
{
    Node<T> *p = this->_head;
    if (p->_next == nullptr)
    {
        throw "error0";
    }
    p = p->_next;
    for (int i = 0; i < n; i++)
    {
        if (p->_next == nullptr)
            throw "error";
        p = p->_next;
    }
    std::stringstream ss;
    ss << p->_data;
    return ss.str();
}
