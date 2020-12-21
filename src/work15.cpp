#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

template <class T>
class HuffmanTree;
template <class T>
struct tmp2;
template <class T>
void dfs(HuffmanTree<T>* t, vector<int>& code,
         vector<pair<T, vector<int>>>& ans);

template <class T>
class HuffmanTree {
   private:
    T _val;
    HuffmanTree* _left;
    HuffmanTree* _right;

   public:
    friend struct tmp2<T>;
    friend void dfs<>(HuffmanTree<T>*, vector<int>& code,
                      vector<pair<int, vector<int>>>& ans);
    HuffmanTree() : _val(), _left(nullptr), _right(nullptr) {}
    HuffmanTree(T x) : _val(x), _left(nullptr), _right(nullptr) {}
    HuffmanTree(HuffmanTree* t1, HuffmanTree* t2);
    bool operator<(const HuffmanTree& v2) const {
        return (this->_val < v2._val);
    };
    bool operator>(const HuffmanTree& v2) const {
        return (this->_val > v2._val);
    };
    bool operator<=(const HuffmanTree& v2) const {
        return (this->_val <= v2._val);
    };
    bool operator>=(const HuffmanTree& v2) const {
        return (this->_val >= v2._val);
    };
    bool operator==(const HuffmanTree& v2) const {
        return (this->_val == v2._val);
    };
    ~HuffmanTree();
};

template <class T>
HuffmanTree<T>::~HuffmanTree() {
    if (this->left != nullptr) {
        delete this->left;
        this->left = nullptr;
    }
    if (this->right != nullptr) {
        delete this->right;
        this->right = nullptr;
    }
}

template <class T>
HuffmanTree<T>::HuffmanTree(HuffmanTree<T>* t1, HuffmanTree<T>* t2) {
    if (t1->_val < t2->_val) {
        this->_left = t1;
        this->_right = t2;
    } else {
        this->_right = t1;
        this->_left = t2;
    }
    this->_val = t1->_val + t2->_val;
}

template <class T>
struct tmp2  //重写仿函数
{
    bool operator()(HuffmanTree<T>* a, HuffmanTree<T>* b) {
        return a->_val > b->_val;  //大顶堆
    }
};

template <class T>
void dfs(HuffmanTree<T>* t, vector<int>& code,
         vector<pair<T, vector<int>>>& ans) {
    if (t->_left == nullptr && t->_right == nullptr) {
        pair<T, vector<int>> k = {t->_val, code};
        ans.push_back(k);
        return;
    } else {
        if (t->_left != nullptr) {
            code.push_back(0);
            dfs(t->_left, code, ans);
            code.pop_back();
        }
        if (t->_right != nullptr) {
            code.push_back(1);
            dfs(t->_right, code, ans);
            code.pop_back();
        }
        return;
    }
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

void opening() {
    cout << "Application of Hoffman Tree in Communication Coding." << endl
         << "The input is a line of positive integers. " << endl
         << "The first number is N followed by N communication symbols. " << endl
         << "Now enter a line of positive integers. " << endl;
    return;
}

int main() {
    opening();
    priority_queue<HuffmanTree<int>*, vector<HuffmanTree<int>*>, tmp2<int>>
        heap;
    string temp;
    int num = 0;
    while (true) {
        cin >> temp;
        if (!isNum(temp))
            cout << "Error: Invalid input detected. Please try again." << endl;
        else {
            num = str2num(temp);
            break;
        }
    }
    for (int i = 0; i < num; i++) {
        cin >> temp;
        if (!isNum(temp)) {
            i--;
            cout << "Error: Invalid input detected. Please try again." << endl;
        } else {
            HuffmanTree<int>* t = new HuffmanTree<int>((int)str2num(temp));
            heap.push(t);
        }
    }
    while (heap.size() > 1) {
        auto temp = heap.top();
        heap.pop();
        auto temp2 = new HuffmanTree<int>(temp, heap.top());
        heap.pop();
        heap.push(temp2);
    }
    vector<int> code;
    vector<pair<int, vector<int>>> ans;
    dfs(heap.top(), code, ans);
    std::sort(ans.begin(), ans.end(),
              [](pair<int, vector<int>>& s1, pair<int, vector<int>>& s2) {
                  return s1.first < s2.first;
              });
    for (auto&& i : ans) {
        cout << "Weight = " << i.first << "  Code = ";
        for (auto&& j : i.second) cout << j;
        cout << endl;
    }
    return 0;
}