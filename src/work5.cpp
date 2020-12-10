#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int num;
    cin >> num;
    vector<int> a, b;
    for (int i = 0; i < num; i++) {
        int temp;
        cin >> temp;
        if (temp % 2 == 1)
            a.push_back(temp);
        else
            b.push_back(temp);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int i = 0;
    while (a.size() >= 2 * i + 1 || b.size() >= i + 1) {
        if (a.size() >= 2 * i + 1) cout << a[2 * i] << ' ';
        if (a.size() >= 2 * i + 2) cout << a[2 * i + 1] << ' ';
        if (b.size() >= i + 1) cout << b[i] << ' ';
        i++;
    }

    return 0;
}