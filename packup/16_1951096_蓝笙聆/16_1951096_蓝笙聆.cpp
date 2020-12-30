#include <iostream>
#include <vector>

using namespace std;

void output_matrix(vector<vector<int>>& a) {
    int i = 0, j = 0;
    for (i = 0; i < a.size(); i++) {
        for (j = 0; j < a.size(); j++) cout << a[i][j] << " ";
        cout << endl;
    }
}
void warshall(vector<vector<int>>& a) {
    //(1)i＝1；
    //(2)对所有j如果a[j，i]＝1，则对k＝0，1，…，n-1，a[j，k]＝a[j，k]∨a[i，k]；
    //(3)i加1；
    //(4)如果i<n，则转到步骤2，否则停止
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a.size(); j++)
            if (a[j][i])
                for (int k = 0; k < a.size(); k++)
                    a[j][k] = a[j][k] | a[i][k];  //逻辑加
}

bool loop() {
    int n = 0;
    vector<vector<int>> arr;
    cout << "Using Warshall algorithm to find the transfer closure of "
            "relational matrix."
         << endl
         << "Please enter the number of vertices to construct the relationship "
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
            }  //若检测到输入了除了0和1以外的数值则准备提示报错
        if (!flag) break;
        cout << "Invalid input detected, please enter the relationship matrix "
                "again."
             << endl;
    }
    warshall(arr);
    output_matrix(arr);

    cout << "Again? (y for yes, n for no)";
    char c;
    cin >> c;
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