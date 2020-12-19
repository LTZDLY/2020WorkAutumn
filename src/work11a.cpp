#include <iostream>
#include <string>
using namespace std;

void opening() {
    cout << "****************************************\n"  //标语
         << "**                                    **\n"
         << "**     Welcome to Logical Operator    **\n"
         << "**                                    **\n"
         << "****************************************\n\n";
}

bool loop() {
    int a[4];
    string i, j;
    char s;
    while (true) {
        cout << "Please enter a value for P(0/1): ";
        cin >> i;  //读取P的值
        if (i.size() != 1 || (i[0] != '0' && i[0] != '1')) {
            cout << "Error: Invalue input detected, please try again." << endl;
            continue;
        }
        break;
    }
    while (true) {
        cout << "Please enter a value for Q(0/1): ";
        cin >> j;  //读取Q的值
        if (j.size() != 1 || (j[0] != '0' && j[0] != '1')) {
            cout << "Error: Invalue input detected, please try again." << endl;
            continue;
        }
        break;
    }
    int p = i[0] - '0';
    int q = j[0] - '0';
    a[0] = p && q;     //与运算
    a[1] = p || q;     //或运算
    a[2] = (!p) || q;  //蕴含运算，将其转化为与或非形式
    a[3] = ((!p) || q) && ((!q) || p);  //等值运算，将其转化为与或非形式
    cout << "  P = " << i << "       Q = " << j << endl
         << endl                                             //输出结果
         << "Conjunction:\n       P/\\Q = " << a[0] << endl  //输出结果
         << "Disjunctive:\n       P\\/Q = " << a[1] << endl
         << "Conditional:\n       P->Q = " << a[2] << endl
         << "Biconditional:\n       P<->Q = " << a[3] << endl;
    cout << "Again? (y for yes, n for no)";  //询问是否继续操作
    cin >> s;
    if (s == 'y') return true;
    return false;
}

int main() {
    opening();
    while (loop())
        ;
    cout << "Thanks for using it. See you next time!" << endl;  //退出
    return 0;
}
