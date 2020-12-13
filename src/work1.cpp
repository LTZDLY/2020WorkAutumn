#include <iostream>
#include <sstream>
#include <string>

struct Student {
    int id = 0;          //学号
    int age = 0;         //年龄
    std::string sex;     //性别
    std::string name;    //姓名
    std::string choice;  //志愿
    friend std::ostream &operator<<(std::ostream &output, const Student &D);
    friend std::istream &operator>>(std::istream &input, const Student &D);
    bool operator==(const Student D);
    void operator=(const Student D);
};
bool Student::operator==(const Student D) { return (this->id == D.id); }
void Student::operator=(const Student D) {
    this->age = D.age;
    this->choice = D.choice;
    this->id = D.id;
    this->name = D.name;
    this->sex = D.sex;
}
std::ostream &operator<<(std::ostream &output, const Student &D) {
    output << D.id << '\t' << D.name << '\t' << D.sex << '\t' << D.age
           << '\t' << D.choice << std::endl;
    return output;
}
std::istream &operator>>(std::istream &input, Student &D) {
    input >> D.id >> D.name >> D.sex >> D.age >> D.choice;
    return input;
}

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
    if (this->Empty()) throw "Error: The list is empty.";
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
    if (this->Empty()) throw "Error: The list is empty.";

    auto p = this->_head->_next;
    for (int i = 0; i < n; i++) {
        if (p->_next == nullptr) throw "Error: Not so many nodes.";
        p = p->_next;
    }
    p->_data = data;
}

template <class T>
std::string List<T>::ListPrint(int n) const {
    if (this->Empty()) throw "Error: The list is empty.";

    auto p = this->_head->_next;
    for (int i = 0; i < n; i++) {
        if (p->_next == nullptr) throw "Error: Not so many nodes.";
        p = p->_next;
    }
    std::stringstream ss;
    ss << p->_data;
    return ss.str();
}

int opening(List<Student> &list) {
    std::cout << "First set up the examinee information system" << std::endl;
    int num = 0;
    do {
        std::cout << "Please enter the number of students: ";
        std::cin >> num;
        if (num == 0) return num;
        if (num < 0)
            std::cerr << "Error: Invalid input, Please try again." << std::endl;
    } while (num < 0);
    std::cout << "Please input the student's id, name, gender, age and first "
                 "choice in turn. (separated by ' ')"
              << std::endl;
    for (int i = 0; i < num; i++) {
        Student temp;
        std::cin >> temp;
        list.ListIns(i, temp);
    }
    return num;
}

void printList(std::ostream &os, const List<Student> &list) {
    if (list.Empty()) throw "Error: The list is empty.";
    os << "\nid" << '\t' << "name" << '\t' << "gender" << '\t' << "age" << '\t'
       << "first choise" << std::endl;
    for (int i = 0; i < list.ListLen(); i++) {
        os << list.ListPrint(i);
    }
}

void insList(List<Student> &list) {
    std::cout << "Please enter the student location to insert: ";
    int i;
    std::cin >> i;
    if (i < 0 || i > list.ListLen()) throw "Error: Invalid input.";
    std::cout << "Please input the student's id, name, gender, age and first "
                 "choice in turn."
              << std::endl;
    Student temp;
    std::cin >> temp;
    list.ListIns(i, temp);
    printList(std::cout, list);
}

void delList(List<Student> &list) {
    if (list.Empty()) throw "Error: The list is empty.";
    std::cout << "Please enter the id of the student to delete: ";
    int i;
    std::cin >> i;
    Student temp;
    temp.id = i;
    auto s = list.ListPop(temp);
    std::cout << "The student information you deleted is: \n" << s;
    if (!list.Empty()) printList(std::cout, list);
}
void findList(List<Student> &list) {
    if (list.Empty()) throw "Error: The list is empty.";
    std::cout << "Please enter the id of the student you are looking for: ";
    int i;
    std::cin >> i;
    Student temp;
    temp.id = i;
    int n = list.ListFind(temp);
    if (n == -1) throw "Error: Data no find.";
    std::cout << "\nid" << '\t' << "name" << '\t' << "gender" << '\t' << "age"
              << '\t' << "first choise" << std::endl
              << list.ListPrint(n);
}
void changeList(List<Student> &list) {
    if (list.Empty()) throw "Error: The list is empty.";
    std::cout << "Please input the id of the student to be changed: ";
    int i;
    std::cin >> i;
    Student temp;
    temp.id = i;
    int n = list.ListFind(temp);
    if (n == -1) throw "Error: Data no find.";
    std::cout << "Please enter the change student's id, name, gender, age and "
                 "first choise in turn"
              << std::endl;
    std::cin >> temp;
    list.ListChange(n, temp);
    printList(std::cout, list);
}

bool loop(List<Student> &list) {
    std::cout << std::endl
              << "Please enter the number of random numbers to generate: ";
    char i = '\0';
    std::cin >> i;
    try {
        switch (i) {
            case '1':
                insList(list);
                return true;
            case '2':
                delList(list);
                return true;
            case '3':
                findList(list);
                return true;
            case '4':
                changeList(list);
                return true;
            case '5':
                printList(std::cout, list);
                return true;
            default:
                return false;
        }
    } catch (const char *e) {
        std::cerr << e << std::endl;
    }
    return true;
}

int main() {
    List<Student> list;
    std::cout << "**             Examination Enrollment System            **"
              << std::endl
              << "=========================================================="
              << std::endl
              << "**         Please select the action to perform:         **"
              << std::endl
              << "**           1 --- Insert the students                  **"
              << std::endl
              << "**           2 --- Delete the students                  **"
              << std::endl
              << "**           3 --- Search the students                  **"
              << std::endl
              << "**           4 --- change the students                  **"
              << std::endl
              << "**           5 --- Print the list                       **"
              << std::endl
              << "**           Others --- Exit                            **"
              << std::endl
              << std::endl;
    int num = opening(list);
    if (num != 0) printList(std::cout, list);
    while (loop(list))
        ;
    std::cout << "Thanks for using it. See you next time! " << std::endl;
    return 0;
}