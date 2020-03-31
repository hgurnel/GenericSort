#include "Array.h"

int main()
{
    int myArr[5] = {1, 2, 3, 4, 5};
    Array<int> a(myArr, 5);
    a.print();
    return 0;
}