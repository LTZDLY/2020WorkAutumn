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
    os << "The first generations of " << p << " are: ";
    for (auto&& i : c) os << i->val << ' ';
    os << endl;
    return;
}

bool loop(Tree<string>& family) {
    cout << "\nPlease enter a command:";
    char temp = '\0';
    cin >> temp;
    int num = 0;
    string p = "";
    string child = "";
    vector<string> children = {};
    switch (temp) {
        case '1':
            // add children
            cout << "Please enter the name of the person who will establish a "
                    "family:";
            cin >> p;
            cout << "Please enter the number of children of " << p << ".";
            cin >> num;
            cout << "Please enter the name of children of " << p << " in turn.";
            for (int i = 0; i < num; i++) {
                cin >> child;
                children.push_back(child);
            }
            family.inschild(p, children);
            family.printchildren(cout, p);
            return true;
        case '2':
            // add a child;
            cout << "Please enter the name of the person you want to add the "
                    "child to:";
            cin >> p;
            cout << "Please enter the name of the child " << p << " will add:";
            cin >> child;
            family.inschild(p, child);
            family.printchildren(cout, p);
            return true;
        case '3':
            // delete sub tree;
            cout << "Please enter the name of the person whose family you want "
                    "to dissolve";
            cin >> p;
            cout << "The person whose family will be dissolved is " << p
                 << ".\n";
            family.printchildren(cout, p);
            family.del(p);
            return true;
        case '4':
            // change name;
            cout << "Please enter the current name of the person whose name "
                    "you want to change:";
            cin >> p;
            cout << "Please enter the name you want to change:";
            cin >> child;
            family.changename(p, child);
            cout << p << " has been renamed " << child << ".\n";
            return true;
        default:
            return false;
    }
}

int main() {
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
         << "**             5 --- Exit                                    **"
         << endl;

    cout << "Start with a family tree." << endl
         << "Please enter the name of the ancestor:";
    string temp = "";
    cin >> temp;
    Tree<string> tree(temp);
    cout << "The ancestors of this family tree is " << temp << ".\n" << endl;

    while (loop(tree))
        ;
    return 0;
}