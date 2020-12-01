#include <iostream>
#include <string>

using namespace std;
template <class T>
class GenList {
    GenList();
    ~GenList();

};

template <class T>
class GenListNode {
    int utype;
    GenListNode<T>* next;
    union {
        int ref;
        T val;
        GenListNode<T>* lval;
    };
    
};