#pragma once

#include <iostream>
#include <algorithm>

template <typename T>
class Array
{
private:
    T* m_arr;
    size_t m_size;

public:
    // Ctor
    Array(T arr[], size_t size);
    // Dtor
    ~Array();

    T & operator[](size_t index);
    void print();
    void swap(T arr[] , size_t a, size_t b);

};

