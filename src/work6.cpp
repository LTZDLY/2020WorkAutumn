#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <class T>
struct TreeNode {
    T _val;                       //节点的值
    TreeNode* _prev;              //上一个节点
    vector<TreeNode*> _children;  //所有的孩子节点
    TreeNode();
    TreeNode(T x);
    ~TreeNode();
};

template <class T>
TreeNode<T>::TreeNode(T x) {
    this->_val = x;
    this->_prev = nullptr;
}
template <class T>
TreeNode<T>::TreeNode() {
    this->_val = 0;
    this->_prev = nullptr;
}
template <class T>
TreeNode<T>::~TreeNode() {
    if (!this->_children.empty()) {
        for (auto&& i : this->_children) delete i;
    }
}

template <class T>
class Tree {
   private:
    TreeNode<T>* _root;

   public:
    TreeNode<T>* GetRoot() const { return this->_root; }  //返回根节点
    TreeNode<T>* Search(const T val);                  //搜索是否存在val
    void InsChild(const T node, const T val);          //插入一个孩子
    void InsChild(const T node, const vector<T> val);  //插入多个孩子
    void ChangeName(const T prev, const T cur);  //对存在的孩子修改他的名字
    void Del(const T val);  //对存在的孩子进行删除
    void PrintChildren(ostream& os, const T p);  //输出这个孩子
    TreeNode<T>* Bfs(queue<TreeNode<T>*> tree,
                     const T val);  //使用广度优先搜索进行搜索
    Tree();
    Tree(T x);
};

template <class T>
Tree<T>::Tree(T x) {
    this->_root = new TreeNode<T>(x);
}
template <class T>
Tree<T>::Tree() {
    this->_root = new TreeNode<T>;
}

template <class T>
TreeNode<T>* Tree<T>::Bfs(queue<TreeNode<T>*> tree, T val) {
    queue<TreeNode<T>*> children;
    while (!tree.empty()) {
        TreeNode<T>* i = tree.front();
        tree.pop();
        if (i->_val == val) return i;
        for (auto&& j : i->_children) children.push(j);
    }
    if (!children.empty()) return Bfs(children, val);
    return nullptr;
}

template <class T>
TreeNode<T>* Tree<T>::Search(T val) {
    if (this->_root->_val == val) return _root;
    queue<TreeNode<T>*> children;
    for (auto&& j : this->_root->_children) children.push(j);
    if (!children.empty()) return Bfs(children, val);
    return nullptr;
}

template <class T>
void Tree<T>::InsChild(const T par, const T val) {
    TreeNode<T>* node = this->Search(par);
    if (node == nullptr) throw "Error: Data not found. ";
    auto child = new TreeNode<T>(val);
    child->_prev = node;
    node->_children.push_back(child);
    return;
}
template <class T>
void Tree<T>::InsChild(const T par, const vector<T> children) {
    TreeNode<T>* node = this->Search(par);
    if (node == nullptr) throw "Error: Data not found. ";
    for (auto&& i : children) {
        auto child = new TreeNode<T>(i);
        child->_prev = node;
        node->_children.push_back(child);
    }
}
template <class T>
void Tree<T>::Del(const T val) {
    TreeNode<T>* node = this->Search(val);
    if (node == nullptr) throw "Error: Data not found. ";
    TreeNode<T>* parent = node->_prev;
    for (int i = 0; i < parent->_children.size(); i++) {
        if (parent->_children[i]->_val == val) {
            auto v = parent->_children;
            parent->_children.clear();
            for (auto&& i : v)
                if (i->_val != val) parent->_children.push_back(i);
            delete v[i];
        }
    }
}
template <class T>
void Tree<T>::ChangeName(const T prev, const T cur) {
    auto i = this->Search(prev);
    if (i == nullptr) throw "Error: Data not found. ";
    i->_val = cur;
    return;
}
template <class T>
void Tree<T>::PrintChildren(ostream& os, const T p) {
    auto i = this->Search(p);
    if (i == nullptr) throw "Error: Data not found. ";
    auto c = i->_children;
    os << "The first generations of " << p << " are: ";
    for (auto&& i : c) os << i->_val << ' ';
    os << endl;
    return;
}

double str2num(string s) {
    stringstream ss;
    double d = 0.0;
    ss << s;
    ss >> d;
    return d;
}

bool isNum(string str) {
    for (auto&& i : str)
        if (!isdigit(i)) return false;
    return true;
}

string opening() {
    cout << "**                Genealogy management system                **"
         << endl
         << "==============================================================="
         << endl
         << "**           Please select the action to perform:            **"
         << endl
         << "**             1 --- Perfect the genealogy                   **"
         << endl
         << "**             2 --- Add family members                      **"
         << endl
         << "**             3 --- Disband a part of the family            **"
         << endl
         << "**             4 --- Change the names of family members      **"
         << endl
         << "**             5 --- Find a family member                    **"
         << endl
         << "**             6 --- Exit                                    **"
         << endl;

    cout << "Start with a family tree." << endl
         << "Please enter the name of the ancestor:";
    string temp = "";
    cin >> temp;
    return temp;
}
void addChildren(Tree<string>& family) {
    int num = 0;
    string temps = "";
    string p = "";
    string child = "";
    vector<string> children = {};
    cout << "Please enter the name of the person who will establish a "
            "family: ";
    cin >> p;
    if (family.Search(p) == nullptr)
        throw "Error: Data not found. Please try again. ";
    cout << "Please enter the number of children of " << p << ": ";
    cin >> temps;
    if (isNum(temps))
        num = str2num(temps);
    else
        throw "Error: Invalid input detected. Please try again. ";
    cout << "Please enter the name of children of " << p << " in turn: ";
    for (int i = 0; i < num; i++) {
        cin >> child;
        if (family.Search(child) != nullptr)
            throw "Error: Already in the tree. Please try again. ";
        children.push_back(child);
    }
    family.InsChild(p, children);
    family.PrintChildren(cout, p);
    return;
}
void addAChild(Tree<string>& family) {
    string child = "";
    string p = "";
    cout << "Please enter the name of the person you want to add the "
            "child to: ";
    cin >> p;
    if (family.Search(p) == nullptr)
        throw "Error: Data not found. Please try again. ";
    cout << "Please enter the name of the child " << p << " will add: ";
    cin >> child;
    if (family.Search(child) != nullptr)
        throw "Error: Already in the tree. Please try again. ";
    family.InsChild(p, child);
    family.PrintChildren(cout, p);
    return;
}
void delSubTree(Tree<string>& family) {
    string p = "";
    cout << "Please enter the name of the person whose family you want "
            "to dissolve: ";
    cin >> p;
    auto pp = family.Search(p);
    if (pp == nullptr) throw "Error: Data not found. Please try again.";
    if (pp == family.GetRoot())
        throw "Error: You are not allowed to delete the root node. Please try again.";
    cout << "The person whose family will be dissolved is " << p << ".\n";
    family.PrintChildren(cout, p);
    family.Del(p);
    return;
}
void changeName(Tree<string>& family) {
    string child = "";
    string p = "";
    cout << "Please enter the current name of the person whose name "
            "you want to change: ";
    cin >> p;
    if (family.Search(p) == nullptr)
        throw "Error: Data not found. Please try again. ";
    cout << "Please enter the name you want to change: ";
    cin >> child;
    if (family.Search(child) != nullptr)
        throw "Error: Already in the tree. Please try again. ";
    family.ChangeName(p, child);
    cout << p << " has been renamed " << child << ".\n";
    return;
}
void findMember(Tree<string>& family) {
    string p = "";
    cout << "Please enter the name of the person you want to search: ";
    cin >> p;
    auto pp = family.Search(p);
    if (pp == nullptr)
        cout << "Can not find the person. ";
    else {
        if (pp->_prev != nullptr)
            cout << p << "'s parent is " << pp->_prev->_val;
        else
            cout << p << " is the root parent.";
        cout << endl;
        if (pp->_children.size() != 0) {
            cout << "The first generations of " << p << " are: ";
            for (auto&& i : pp->_children) cout << i->_val << ' ';
            cout << endl;
        } else
            cout << p << " do not have any children.";
    }
    cout << endl;
    return;
}
bool loop(Tree<string>& family) {
    cout << "\nPlease enter a command:";
    char temp = '\0';
    cin >> temp;
    try {
        switch (temp) {
            case '1':
                // add children
                addChildren(family);
                return true;
            case '2':
                // add a child;
                addAChild(family);
                return true;
            case '3':
                // delete sub tree;
                delSubTree(family);
                return true;
            case '4':
                // change name;
                changeName(family);
                return true;
            case '5':
                // find member;
                findMember(family);
                return true;
            default:
                return false;
        }
    } catch (const char* e) {
        std::cerr << e << '\n';
        return true;
    }
}

int main() {
    string p = opening();
    Tree<string> tree(p);
    cout << "The ancestors of this family tree is " << p << ".\n" << endl;
    while (loop(tree))
        ;
    return 0;
}