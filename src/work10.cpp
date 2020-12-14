#include <time.h>

#include <iostream>
#include <random>
#include <sstream>
#include <vector>

using namespace std;

double random(double start, double end) {
    return start + (end - start) * rand() / (RAND_MAX + 1.0);
}

// 1、冒泡排序
template <class T>
int bubbleSort(vector<T>& arr) {
    unsigned swpnum = 0;
    unsigned cmpnum = 0;
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 1; i < arr.size(); i++) {
            cmpnum++;
            if (arr[i] < arr[i - 1]) {
                swpnum++;
                swap(arr[i], arr[i - 1]);
                flag = true;
            }
        }
    }
    return swpnum;
}

// 2、选择排序
template <class T>
int selctionSort(vector<T>& arr) {
    unsigned swpnum = 0;
    for (int i = 0; i < arr.size(); i++) {
        T* min = &arr[i];
        for (int j = i + 1; j < arr.size(); j++)
            if (*min > arr[j]) {
                min = &arr[j];
            }
        if (*min != arr[i]) {
            swap(arr[i], *min);
            swpnum++;
        }
    }
    return swpnum;
}

// 3、插入排序
template <class T>
int insertionSort(vector<T>& arr) {
    unsigned swpnum = 0;
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = i + 1; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
                swpnum++;
            } else
                break;
        }
    }
    return swpnum;
}

// 4、希尔排序
template <class T>
int shellSort(vector<T>& arr) {
    unsigned swpnum = 0;
    int incre = arr.size();
    while (true) {
        incre = incre / 2;
        for (int k = 0; k < incre; k++)
            for (int i = k + incre; i < arr.size(); i++)
                for (int j = i; j >= k; j -= incre) {
                    if (j - incre >= k && arr[j] < arr[j - incre]) {
                        swap(arr[j], arr[j - incre]);
                        swpnum++;
                    } else
                        break;
                }
        if (incre == 1) break;
    }
    return swpnum;
}

// 5、快速排序
template <class T>
int quickSort(vector<T>& arr, int left, int right) {
    unsigned swpnum = 0;
    int mid = (left + right) / 2;
    int temp, j, i, middle = arr[mid];
    i = left;
    j = right;
    while (j >= i) {
        while (middle > arr[i]) (i++);
        while (middle < arr[j]) (j--);
        if (i <= j) {
            swap(arr[i], arr[j]);
            swpnum++;
            i++;
            j--;
        }
    }
    if (i < right) (swpnum += quickSort(arr, i, right));
    if (j > left) (swpnum += quickSort(arr, left, j));
    return swpnum;
}

// 6、归并排序
template <class T>
int merge(vector<T>& nums, int l1, int r1, int l2, int r2) {
    unsigned swpnum = 0;
    int i = l1;                             //左半部分起始位置
    int j = l2;                             //右半部分起始位置
    int n = (r1 - l1 + 1) + (r2 - l2 + 1);  //要合并的元素个数
    vector<T> temp(n);                      //辅助数组
    int k = 0;                              //辅助数组其起始位置
    while (i <= r1 && j <= r2) {  //挑选两部分中最小的元素放入辅助数组中
        swpnum++;
        if (nums[i] < nums[j])
            temp[k++] = nums[i++];
        else
            temp[k++] = nums[j++];
    }
    //如果还有剩余，直接放入到辅助数组中
    while (i <= r1) temp[k++] = nums[i++];
    while (j <= r2) temp[k++] = nums[j++];
    //更新原始数组元素
    for (int i = 0; i < n; i++) {
        nums[l1 + i] = temp[i];
    }
    return swpnum;
}
/*二路归并排序（递归实现）*/
template <class T>
int mergeSort(vector<T>& nums, int start, int end) {
    unsigned swpnum = 0;
    if (start < end) {
        int mid = (start + end) >> 1;           //分割序列
        swpnum += mergeSort(nums, start, mid);  //对序列左半部分进行规并排序
        swpnum += mergeSort(nums, mid + 1, end);  //对序列右半部分进行规并排序
        swpnum +=
            merge(nums, start, mid, mid + 1, end);  //合并已经有序的两个序列
    }
    return swpnum;
}

// 7、堆排序
template <class T>
int MaxSort(vector<T>& arr, int i, int n) {
    int swpnum = 0;
    int j = 2 * i + 1;  //找到当前结点的左孩子
    int temp = arr[i];  //把当前结点的数赋给temp变量，后面会发现这个变量很有用
    while (j < n)  //判断必须条件，大于或等于该结点都属于数组越界
    {
        if (j + 1 < n && arr[j] < arr[j + 1])
            //判断条件，第一个条件是判断是不是最后一个结点。第二个判断条件是找出孩子结点最大的数方便与结点交换。
            ++j;  //如果后面的大，那么交换的变成后面的孩子。
        if (temp > arr[j])
            break;  //因为我们是MaxSort所以如果父结点本身就大不用判断直接跳出循环。
        else {  //判断过程，把最大的孩子结点的数赋给父结点。并利用递归思想找出子节点的子节点。
            arr[i] = arr[j];
            i = j;
            j = 2 * i + 1;
            swpnum++;
        }
    }  // i已经成为了孩子结点的下标，赋值temp，也就是原本父结点的值，达成交换。
    arr[i] = temp;
    return swpnum;
}
//堆排序
template <class T>
int heapSort(vector<T>& arr, int n) {
    int swpnum = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
        swpnum += MaxSort(arr, i, n);  //从最后一个结点的父结点开始“向前遍历”。
    for (int i = n - 1; i >= 1; i--) {
        swap(arr[i], arr[0]);
        swpnum++;
        swpnum += MaxSort(arr, 0, i);
    }  //逆序
    return swpnum;
}

// 8、基数排序
/*获得数组中数值的最大位数*/
int maxBit(const vector<int> arr) {
    int len = 0;
    for (auto&& i : arr) {
        int c = 0;
        int tmp = i;
        while (tmp > 0) {
            tmp /= 10;
            c++;
        }
        if (len < c) len = c;
    }
    return len;
}
/*基于int型数组的基数排序简单实现*/
int radixSort(vector<int>& arr) {
    const int BUCKETS = 10;                //设置桶的个数
    vector<vector<int>> buckets(BUCKETS);  //设置基数桶
    int len = maxBit(arr);  //获得数组中数值的最大位数，依次决定排序次数
    int r = 1;
    for (int i = 0; i < len; ++i) {  //从低位到高位进行基数排序，依次方法桶中
        for (int& s : arr) {  //此循环按相应基数排序
            int k = s / r;
            int q = k % BUCKETS;
            buckets[q].push_back(std::move(s));
        }
        int idx = 0;
        for (auto& thisBucket : buckets) {  //循环每个桶中的元素
            for (int& s : thisBucket)  //将每个桶中的元素放入原始数组中
                arr[idx++] = std::move(s);
            thisBucket.clear();
        }
        r = r * 10;
    }
    return 0;
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

bool loop(long temp) {
    srand((unsigned int)(time(NULL)));
    vector<int> arr;
    for (int i = 0; i < temp; i++) {
        arr.push_back((int)random(0, 10000));
    }
    // for (auto&& i : arr) cout << i << " ";
    char ctemp = '\0';
    cout << "Enter which command you want to use. ";
    cin >> ctemp;
    bool flag = false;
    if (ctemp >= '1' && ctemp <= '8')
        flag = true;
    else if (ctemp == '9')
        flag = false;
    else
        return false;
    for (int i = 0; i < 8; i++) {
        if (flag) i = ctemp - '0' - 1;
        vector<int> arrc = arr;
        unsigned a = 0;
        double t = 0.0;
        clock_t begin;
        clock_t end;
        switch (i) {
            case 0:
                cout << "Bubble Sort: " << endl;
                begin = clock();
                a = bubbleSort(arrc);
                end = clock();
                break;
            case 1:
                cout << "Selction Sort: " << endl;
                begin = clock();
                a = selctionSort(arrc);
                end = clock();
                break;
            case 2:
                cout << "Insertion Sort: " << endl;
                begin = clock();
                a = insertionSort(arrc);
                end = clock();
                break;
            case 3:
                cout << "Shell Sort: " << endl;
                begin = clock();
                a = shellSort(arrc);
                end = clock();
                break;
            case 4:
                cout << "Quick Sort: " << endl;
                begin = clock();
                a = quickSort(arrc, 0, arrc.size() - 1);
                end = clock();
                break;
            case 5:
                cout << "Merge Sort: " << endl;
                begin = clock();
                a = mergeSort(arrc, 0, arrc.size() - 1);
                end = clock();
                break;
            case 6:
                cout << "Heap Sort: " << endl;
                begin = clock();
                a = heapSort(arrc, arrc.size());
                end = clock();
                break;
            case 7:
                cout << "Radix Sort: " << endl;
                begin = clock();
                a = radixSort(arrc);
                end = clock();
                break;
            default:
                return false;
        }
        t = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
        cout << "Running time: " << t << "ms" << endl;
        cout << "Exchange time: " << a << endl << endl;
        if (flag) return true;
    }
    // for (auto&& i : arr) cout << i << " ";
    return true;
}
void opening() {
    cout << "**                Sorting algorithm comparison                **"
         << endl
         << "==============================================================="
         << endl
         << endl
         << "Enter the number of random numbers, and enter which command you "
            "want to use. "
         << endl
         << "1. Bublle Sort" << endl
         << "2. Selction Sort" << endl
         << "3. Insertion Sort" << endl
         << "4. Shell Sort" << endl
         << "5. Quick Sort" << endl
         << "6. Merge Sort" << endl
         << "7. Heap Sort" << endl
         << "8. Radix Sort" << endl
         << "9. All methods above execute once in sequence." << endl;
}
int main() {
    opening();
    long temp = 0;
    string temps;
    while (true) {
        cout << endl
             << "Please enter the number of random numbers to generate: ";
        cin >> temps;
        if (isNum(temps)) {
            temp = str2num(temps);
            if (temp <= 0) {
                cout << "Error: Invalid input detected. Please try again.";
            } else
                break;
        } else
            cout << "Error: Invalid input detected. Please try again.";
    }
    while (loop(temp))
        ;
    return 0;
}