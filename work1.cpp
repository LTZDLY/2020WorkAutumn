#include <iostream>
#include <string>
#include <sstream>

struct Student
{
    int _id = 0;
    int _age = 0;
    std::string _sex;
    std::string _name;
    std::string _choice;
    friend std::ostream &operator<<(std::ostream &output, const Student &D);
    friend std::istream &operator>>(std::istream &input, const Student &D);
    bool operator==(const Student D);
    void operator=(const Student D);
};
bool Student::operator==(const Student D) { return (this->_id == D._id); }
void Student::operator=(const Student D)
{
    this->_age = D._age;
    this->_choice = D._choice;
    this->_id = D._id;
    this->_name = D._name;
    this->_sex = D._sex;
}
std::ostream &operator<<(std::ostream &output, const Student &D)
{
    output << D._id << '\t' << D._name << '\t' << D._sex << '\t' << D._age << '\t' << D._choice << std::endl;
    return output;
}
std::istream &operator>>(std::istream &input, Student &D)
{
    input >> D._id >> D._name >> D._sex >> D._age >> D._choice;
    return input;
}

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
List<T>::List(/* args */)
{
    this->_head = new Node<T>;
    this->_len = 0;
}

template <class T>
List<T>::~List()
{
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
    if (p->_next == nullptr)
        node->_next = nullptr;
    else
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
    Node<T> *p = this->_head->_next;
    int i = 0;
    while (1)
    {
        if (p->_data == data)
            return i;
        if (p->_next == nullptr)
        {
            throw "no find";
            return -1;
        }
        p = p->_next;
        i++;
    }
}

template <class T>
int List<T>::listLen() const { return this->_len; }

template <class T>
void List<T>::listChange(int n, T data)
{
    Node<T> *p = this->_head->_next;
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
    Node<T> *p = this->_head->_next;
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

void opening(int &num, List<Student> &list)
{
    std::cout << "首先建立考生信息系统！" << std::endl
            << "请输入考生人数：";
    std::cin >> num;
    std::cout << "请依次输入考生的学号，姓名，性别，年龄及报考类别！（用空格分隔）" << std::endl;
    for (int i = 0; i < num; i++)
    {
        Student temp;
        std::cin >> temp;
        list.listIns(i, temp);
    }
}

void printList(const List<Student> &list)
{
    std::cout << "\n考号" << '\t' << "姓名" << '\t' << "性别" << '\t' << "年龄" << '\t' << "报考类别" << std::endl;
    for (int i = 0; i < list.listLen(); i++)
    {
        std::cout << list.listPrint(i);
    }
}

void insList(List<Student> &list)
{
    std::cout << "请输入要插入的考生位置：";
    int i;
    std::cin >> i;
    if (i < 0 || i > list.listLen())
        throw "error";
    std::cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别" << std::endl;
    Student temp;
    std::cin >> temp;
    list.listIns(i, temp);
    printList(list);
}

void delList(List<Student> &list)
{
    std::cout << "请输入要删除的考生的考号：";
    int i;
    std::cin >> i;
    Student temp;
    temp._id = i;
    std::cout << "所删除的考生信息为：\n"
            << list.listPop(temp);
    printList(list);
}
void findList(List<Student> &list)
{
    std::cout << "请输入要查找的考生的考号：";
    int i;
    std::cin >> i;
    Student temp;
    temp._id = i;
    int n = list.listFind(temp);
    std::cout << "考号" << '\t' << "姓名" << '\t' << "性别" << '\t' << "年龄" << '\t' << "报考类别" << std::endl
            << list.listPrint(n);
}
void exchangeList(List<Student> &list)
{
    std::cout << "请输入要修改的考生考号：";
    int i;
    std::cin >> i;
    Student temp;
    temp._id = i;
    int n = list.listFind(temp);
    std::cout << "请依次输入修改后的考生的考号，姓名，性别，年龄及报考类别" << std::endl;
    std::cin >> temp;
    list.listChange(n, temp);
    printList(list);
}

bool loop(List<Student> &list)
{
    std::cout << "请选择您要进行的操作：";
    int i = 0;
    std::cin >> i;
    try
    {
        switch (i)
        {
        case 1:
            insList(list);
            return true;
        case 2:
            delList(list);
            return true;
        case 3:
            findList(list);
            return true;
        case 4:
            exchangeList(list);
            return true;
        case 5:
            printList(list);
            return true;
        default:
            return false;
        }
    }
    catch (const char *e)
    {
        std::cerr << e;
    }
    return true;
}

int main()
{
    List<Student> list;
    int num;
    opening(num, list);
    printList(list);
    std::cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << std::endl;
    while (loop(list))
        ;
    return 0;
}