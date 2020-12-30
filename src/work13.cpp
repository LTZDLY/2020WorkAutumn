#include <iostream>
#include <string>
#include <vector>

using namespace std;

void output(vector<vector<int>> arr) {
    cout << "The resulting relationship matrix is:" << endl;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[0].size(); j++) cout << arr[i][j] << " ";
        cout << endl;
    }
}

void reflexive(vector<vector<int>> arr) {
    for (int i = 0; i < arr.size(); i++) arr[i][i] = 1;
    output(arr);
}

void symmetric(vector<vector<int>> arr) {
    vector<vector<int>> s1 = arr;
    for (int i = 0; i < arr.size(); i++)
        for (int j = 0; j < arr[0].size(); j++) {
            arr[i][j] = arr[i][j] + s1[j][i];
            if (arr[i][j] > 1) arr[i][j] = 1;
        }
    output(arr);
}

void transitive(vector<vector<int>> arr) {
    //使用warshall算法实现，具体原理见第6题和文档
    for (int i = 0; i < arr.size(); i++)
        for (int j = 0; j < arr.size(); j++)
            if (arr[j][i])
                for (int k = 0; k < arr.size(); k++)
                    arr[j][k] = arr[j][k] | arr[i][k];  //逻辑加
    output(arr);
}
void opening(vector<vector<int>>& arr) {
    int n;
    cout << "Reflexive, symmetric, and transitive closures of relationships. "
         << endl;
    cout << "Please enter the number of vertices to construct the relationship "
            "matrix."
         << endl;
    while (true) {
        cin >> n;
        if (n > 0) break;
        cout << "Invalid input dected, please try again.";
    }
    arr.resize(n);
    for (auto&& i : arr) i.resize(n);
    cout << "Please enter the relationship matrix" << endl;
    while (true) {
        bool flag = false;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                cin >> arr[i][j];
                if (arr[i][j] != 0 && arr[i][j] != 1) flag = true;
            }
        if (!flag) break;
        cout << "Invalid input detected, please enter the relationship matrix "
                "again."
             << endl;
    }
}

bool loop(vector<vector<int>>& arr) {
    cout << "Please enter a number to select an algorithm" << endl
         << "l:Reflexive closure." << endl
         << "2:Symmetric closure." << endl
         << "3:Transitive closure." << endl
         << "4:Quit" << endl;
    string str;
    cin >> str;
    switch (str[0]) {
        case '1':
            reflexive(arr);
            return true;
        case '2':
            symmetric(arr);
            return true;
        case '3':
            transitive(arr);
            return true;
        default:
            return false;
    }
}

int main() {
    vector<vector<int>> arr;
    opening(arr);
    while (loop(arr))
        ;
    std::cout << "Thanks for using it. See you next time! " << std::endl;
    return 0;
}