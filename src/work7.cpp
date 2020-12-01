#include <iostream>
#include <vector>

using namespace std;
int main()
{
    int N, i, k, r, t, flag;
    vector<int> a;
    long sum = 0;
    cin >> N;
    for (i = 0; i <= N - 1; i++)
    {
        int temp;
        cin >> temp;
        a.push_back(temp);
    }
    while (a.size() > 2)
    {
        for (i = 0; i <= 1; i++)
        {
            flag = 0;
            k = a[i];
            for (r = i + 1; r <= (int)a.size() - 1; r++)
            {
                if (k > a[r])
                {
                    flag = 1;
                    t = r;
                    k = a[r];
                }
            }
            if (flag == 1)
            {
                a[t] = a[i];
                a[i] = k;
            }
        }
        sum += a[0] + a[1];
        a[0] += a[1];
        a[1] = a[(int)a.size() - 1];
        a.pop_back();
    }
    sum += a[0] + a[1];
    cout << sum;
    return 0;
}