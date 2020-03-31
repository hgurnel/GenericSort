#ifndef _ARRAY_H
#define _ARRAY_H

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
    Array(T arr[], size_t size)
    {
        m_size = size;
        m_arr = new T[size];
        for (size_t i=0; i<size; ++i)
            m_arr[i] = arr[i];
    }

    // Dtor
    ~Array()
    {
        delete[] m_arr;
    }

    T& operator[](size_t index)
    {
        return m_arr[index];
    }

    void print()
    {
        for (size_t i = 0; i < m_size; ++i)
            std::cout << m_arr[i] << std::endl;
    }

    void swap(T arr[], size_t a, size_t b)
    {
        T tmp = arr[a];
        arr[a] = arr[b];
        arr[b] = tmp;
    }
};

#endif // !_ARRAY_H