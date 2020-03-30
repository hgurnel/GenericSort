#pragma once

#include <iostream>
#include <algorithm>

template <typename T, size_t size>
class ArrayHG
{
private:
    T m_arr[size];

public:
    // Ctor
    ArrayHG();
    // Dtor
    ~ArrayHG();

    T& operator[](int i);
    void print();
    void swap(T a, T b);
};

