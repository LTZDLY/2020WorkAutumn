#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

template <class T>
struct TreeNode {
    T val;
    TreeNode* prev;  //上一个节点
    vector<TreeNode*> children;
    TreeNode();
    TreeNode(T x);
    ~TreeNode();
};

template <class T>
TreeNode<T>::TreeNode(T x) {
    this->val = x;
    this->prev = nullptr;
}
template <class T>
TreeNode<T>::TreeNode() {
    this->val = 0;
    this->prev = nullptr;
}
template <class T>
TreeNode<T>::~TreeNode() {
    if (!this->children.empty()) {
        for (auto&& i : this->children) delete i;
    }
}

template <class T>
class Tree {
   private:
    TreeNode<T>* root;

   public:
    TreeNode<T>* search(const T val);
    void inschild(const T node, const T val);
    void inschild(const T node, const vector<T> val);
    void changename(const T prev, const T cur);
    void del(const T val);
    void printchildren(ostream& os, const T p);
    TreeNode<T>* bfs(queue<TreeNode<T>*> tree, const T val);
    Tree();
    Tree(T x);
};

template <class T>
Tree<T>::Tree(T x) {
    this->root = new TreeNode<T>(x);
}
template <class T>
Tree<T>::Tree() {
    this->root = new TreeNode<T>;
}

template <class T>
TreeNode<T>* Tree<T>::bfs(queue<TreeNode<T>*> tree, T val) {
    queue<TreeNode<T>*> children;
    while (!tree.empty()) {
        TreeNode<T>* i = tree.front();
        tree.pop();
        if (i->val == val) return i;
        for (auto&& j : i->children) children.push(j);
    }
    if (!children.empty()) return bfs(children, val);
    return nullptr;
}

template <class T>
TreeNode<T>* Tree<T>::search(T val) {
    if (this->root->val == val) return root;
    queue<TreeNode<T>*> children;
    for (auto&& j : this->root->children) children.push(j);
    if (!children.empty()) return bfs(children, val);
    return nullptr;
}

template <class T>
void Tree<T>::inschild(const T par, const T val) {
    TreeNode<T>* node = this->search(par);
    auto child = new TreeNode<T>(val);
    child->prev = node;
    node->children.push_back(child);
    return;
}
template <class T>
void Tree<T>::inschild(const T par, const vector<T> children) {
    TreeNode<T>* node = this->search(par);
    for (auto&& i : children) {
        auto child = new TreeNode<T>(i);
        child->prev = node;
        node->children.push_back(child);
    }
}
template <class T>
void Tree<T>::del(const T val) {
    TreeNode<T>* node = this->search(val);
    TreeNode<T>* parent = node->prev;
    for (int i = 0; i < parent->children.size(); i++) {
        if (parent->children[i]->val == val) {
            auto v = parent->children;
            parent->children.clear();
            for (auto&& i : v)
                if (i->val != val) parent->children.push_back(i);
            delete v[i];
        }
    }
}
template <class T>
void Tree<T>::changename(const T prev, const T cur) {
    auto i = this->search(prev);
    if (i == NULL) throw "error";
    i->val = cur;
    return;
}
template <class T>
void Tree<T>::printchildren(ostream& os, const T p) {
    auto i = this->search(p);
    if (i == NULL) throw "error";
    auto c = i->children;
    os << p << "的第一代子孙是：";
    for (auto&& i : c) os << i->val << ' ';
    os << endl;
    return;
}

bool loop(Tree<string>& family) {
    cout << "\n请选择要执行的操作：";
    char temp = '\0';
    cin >> temp;
    int num = 0;
    string p = "";
    string child = "";
    vector<string> children = {};
    switch (temp) {
        case '1':
            // add children
            cout << "请输入要建立家庭的人的姓名：";
            cin >> p;
            cout << "请输入" << p << "的儿女人数：";
            cin >> num;
            cout << "请依次输入" << p << "的儿女姓名：";
            for (int i = 0; i < num; i++) {
                cin >> child;
                children.push_back(child);
            }
            family.inschild(p, children);
            family.printchildren(cout, p);
            return true;
        case '2':
            // add a child;
            cout << "请输入要添加儿子/女儿的人的姓名：";
            cin >> p;
            cout << "请输入" << p << "新添加的儿子/女儿的姓名：";
            cin >> child;
            family.inschild(p, child);
            family.printchildren(cout, p);
            return true;
        case '3':
            // delete sub tree;
            cout << "请输入要建立家庭的人的姓名：";
            cin >> p;
            cout << "要解散家庭的人是" << p << endl;
            family.printchildren(cout, p);
            family.del(p);
            return true;
        case '4':
            // change name;
            cout << "请输入要更改姓名的人的目前姓名：";
            cin >> p;
            cout << "请输入要更改后的姓名：";
            cin >> child;
            family.changename(p, child);
            cout << p << "已更名为" << child << endl;
            return true;
        default:
            return false;
    }
}

int main() {
    cout << "**                 家谱管理系统                 **" << endl
         << "==================================================" << endl
         << "**             请选择要执行的操作：             **" << endl
         << "**             1 —— 完善家谱                  **" << endl
         << "**             2 —— 添加家庭成员              **" << endl
         << "**             3 —— 解散局部家庭              **" << endl
         << "**             4 —— 更改家庭成员姓名          **" << endl
         << "**             5 —— 解散家庭                  **" << endl;

    cout << "首先建立一个家谱" << endl << "请输入祖先的姓名：";
    string temp = "";
    cin >> temp;
    Tree<string> tree(temp);
    cout << "此家谱的祖先是：" << temp << endl << endl;

    while (loop(tree))
        ;
    return 0;
}