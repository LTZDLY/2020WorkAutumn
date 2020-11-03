#include <iostream>
#include <string>
#include <sstream>

#include "..\inc\list.h"

int main()
{
    List<int> list_a;
    int temp = 0;
    while (1)
    {
        std::cin >> temp;
        if (temp == -1)
            break;
        list_a.listIns(list_a.listLen(), temp);
    }
    List<int> list_b;
    temp = 0;
    while (1)
    {
        std::cin >> temp;
        if (temp == -1)
            break;
        list_b.listIns(list_b.listLen(), temp);
    }
    List<int> list_c;
    for (int i = 0; i < list_a.listLen(); i++)
    {
        if (list_b.listFind(list_a[i]) != -1)
            list_c.listIns(list_c.listLen(), list_a[i]);
    }
    if (list_c.listLen() == 0)
        std::cout << "NULL";
    else
        for (int i = 0; i < list_c.listLen(); i++)
            std::cout << list_c[i] << ' ';
    return 0;
}