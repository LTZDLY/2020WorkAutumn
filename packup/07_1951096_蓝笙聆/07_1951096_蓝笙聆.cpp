#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template <class T>
class MinHeap {
   private:
    T* _mHeap;       // 数据
    int _mCapacity;  // 总的容量
    int _mSize;      // 实际容量

   private:
    void FilterDown(int start, int end);  // 最小堆的向下调整算法
    void FilterUp(
        int start);  // 最小堆的向上调整算法(从start开始向上直到0，调整堆)

   public:
    MinHeap();
    MinHeap(int capacity);
    ~MinHeap();

    T Top();               //返回堆顶元素
    int GetIndex(T data);  // 返回data在二叉堆中的索引
    void Remove(T data);   // 删除最小堆中的data
    void RemoveFront();    // 删除最小堆中的第一个元素
    void Insert(T data);   // 将data插入到二叉堆中
    void Print();          // 打印二叉堆
    int Size() const { return _mSize; }
    bool Empty() { return (_mSize == 0 ? true : false); }
};

template <class T>
MinHeap<T>::MinHeap() {
    new (this) MinHeap(30);
}

template <class T>
MinHeap<T>::MinHeap(int capacity) {
    _mSize = 0;
    _mCapacity = capacity;
    _mHeap = new T[_mCapacity];
}
template <class T>
MinHeap<T>::~MinHeap() {
    _mSize = 0;
    _mCapacity = 0;
    delete[] _mHeap;
}
template <class T>
T MinHeap<T>::Top() {
    if (this->Empty()) throw "Error: The heap is Empty.";
    return _mHeap[0];
}
template <class T>
int MinHeap<T>::GetIndex(T data) {
    for (int i = 0; i < _mSize; i++)
        if (data == _mHeap[i]) return i;
    return -1;
}

/*
 * 最小堆的向下调整算法
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
template <class T>
void MinHeap<T>::FilterDown(int start, int end) {
    int c = start;      // 当前(current)节点的位置
    int l = 2 * c + 1;  // 左(left)孩子的位置
    T tmp = _mHeap[c];   // 当前(current)节点的大小

    while (l <= end) {  // "l"是左孩子，"l+1"是右孩子
        if (l < end && _mHeap[l] > _mHeap[l + 1])
            l++;  // 左右两孩子中选择较小者，即_mHeap[l+1]
        if (tmp <= _mHeap[l])
            break;  //调整结束
        else {
            _mHeap[c] = _mHeap[l];
            c = l;
            l = 2 * l + 1;
        }
    }
    _mHeap[c] = tmp;
}

/*
 * 删除最小堆中的data
 *
 * 返回值：
 *      0，成功
 *     -1，失败
 */
template <class T>
void MinHeap<T>::Remove(T data) {
    int index;
    if (this->Empty()) throw "Error: The heap is Empty.";

    // 获取data在数组中的索引
    index = GetIndex(data);
    if (index == -1) throw "Error: Data not found.";

    _mHeap[index] = _mHeap[--_mSize];  // 用最后元素填补
    FilterDown(index, _mSize - 1);  // 从index号位置开始自上向下调整为最小堆
}
template <class T>
void MinHeap<T>::RemoveFront() {
    if (this->Empty()) throw "Error: The heap is Empty.";
    T val = this->Top();
    this->Remove(val);
}

/*
 * 最小堆的向上调整算法(从start开始向上直到0，调整堆)
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被上调节点的起始位置(一般为数组中最后一个元素的索引)
 */
template <class T>
void MinHeap<T>::FilterUp(int start) {
    int c = start;        // 当前节点(current)的位置
    int p = (c - 1) / 2;  // 父(parent)结点的位置
    T tmp = _mHeap[c];     // 当前节点(current)的大小

    while (c > 0) {
        if (_mHeap[p] <= tmp)
            break;
        else {
            _mHeap[c] = _mHeap[p];
            c = p;
            p = (p - 1) / 2;
        }
    }
    _mHeap[c] = tmp;
}

template <class T>
void MinHeap<T>::Insert(T data) {
    _mHeap[_mSize] = data;  // 将"数组"插在表尾
    FilterUp(_mSize);      // 向上调整堆
    _mSize++;              // 堆的实际容量+1
}

template <class T>
void MinHeap<T>::Print() {
    for (int i = 0; i < _mSize; i++) cout << _mHeap[i] << " ";
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
    cout << "Repair Ranch" << endl
         << "The input is a line of positive integers. " << endl
         << "The first number is N followed by N pieces of wood. "
         << endl
         << "Now enter a line of positive integers. " << endl;
    return;
}

bool loop(){ 
    opening();
    MinHeap<int> heap;
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
		}
		else
			heap.Insert((int)str2num(temp));
	}
    int sum = 0;
    while (heap.Size() > 1) {
        int temp = 0;
        temp += heap.Top();
        heap.RemoveFront();
        temp += heap.Top();
        heap.RemoveFront();
        heap.Insert(temp);
        sum += temp;
    }
    cout << sum << endl;
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