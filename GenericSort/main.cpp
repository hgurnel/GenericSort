#include <iostream>
#include "Array.h"

using namespace std;

int main()
{
    int myArr[9] = {7, 5, 4, 3, 2, 1, 10, 6, -1};
    Array<int> a(myArr, 9);
    a.bubbleSort();
    a.print();
    return 0;
}