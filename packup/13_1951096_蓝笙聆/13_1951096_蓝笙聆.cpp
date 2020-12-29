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
    vector<vector<int>> m(arr), a(arr), t(arr);
    for (int i = 0; i < arr.size(); i++)
        for (int j = 0; j < arr[0].size(); j++) {
            a[i][j] = 0;
            t[i][j] = arr[i][j];
            m[i][j] = arr[i][j];
        }
    for (int h = 0; h < arr.size(); h++) {
        for (int i = 0; i < arr.size(); i++)
            for (int j = 0; j < arr[0].size(); j++)
                if (m[i][j] == 1)
                    for (int k = 0; k < arr.size(); k++)
                        if (arr[j][k] == 1) a[i][k] = 1;
        for (int i = 0; i < arr.size(); i++)
            for (int j = 0; j < arr[0].size(); j++) {
                m[i][j] = a[i][j];
                t[i][j] += a[i][j];
                a[i][j] = 0;
                if (t[i][j] > 1) t[i][j] = 1;
            }
    }
    output(t);
}
void opening(vector<vector<int>>& arr) {
    int n, d;
    cout << "Reflexive, symmetric, and transitive closures of relationships. "
         << endl;
    cout << "Please enter the number of rows of the matrix." << endl;
    cin >> n;
    arr.resize(n);
    cout << "Please enter the number of columns of the matrix." << endl;
    cin >> d;
    for (auto&& i : arr) i.resize(d);
    cout << "Please enter the relationship matrix" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) cin >> arr[i][j];
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