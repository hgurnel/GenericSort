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
        //for (auto i : m_arr)
        //    m_arr[i] = arr[i];
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
        std::for_each(std::begin(m_arr), std::end(m_arr), std::cout);
    }

    void swap(T arr[], size_t a, size_t b)
    {
        T tmp = arr[a];
        arr[a] = arr[b];
        arr[b] = tmp;
    }
};

#endif // !_ARRAY_H