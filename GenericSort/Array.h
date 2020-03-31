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

    T& operator[](size_t index) const
    {
        return m_arr[index];
    }

    void print() const
    {
        for (size_t i = 0; i < m_size; ++i)
            std::cout << m_arr[i] << std::endl;
    }

    void swap(size_t a, size_t b)
    {
        T tmp = m_arr[a];
        m_arr[a] = m_arr[b];
        m_arr[b] = tmp;
    }

    void quickSort(size_t first, size_t last)
    {
        if (first < last) // Check if there are at least two elements in the array
        {
            size_t j = partition(first, last);
            quickSort(first, j);
            quickSort(j+1, last);
        }
    }

    size_t partition(size_t first, size_t last)
    {
        T pivot = m_arr[first];
        size_t i = first;
        size_t j = last;

        while (i < j)
        {
            while (m_arr[i] <= pivot)
                i++;

            while (m_arr[j] > pivot)
                j--;

            if (i < j)
                swap(i, j);
        }

        swap(first, j);
        return j;
    }
};

#endif // !_ARRAY_H