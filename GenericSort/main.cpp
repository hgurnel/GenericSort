#include <iostream>
#include "Array.h"

using namespace std;

int main()
{
    int myArr[8] = {7, 5, 4, 3, 2, 1, 0, 6};
    Array<int> a(myArr, 8);
    
    return 0;
}