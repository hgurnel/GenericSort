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

    ///// BUBBLE SORT, O(n^2)

    ///// SELECTION SORT, O(n^2) /////

    ///// BUCKET SORT, O(n+m), n = nb items and m = nb distinct items ///// 

    ///// QUICK SORT, O(n log(n)) expected, O(n^2) worst case /////

    void quickSort(size_t first, size_t last)
    {
        if (first < last) // Recursion stopping condition: when only one element in partition, ie first = last
        {
            // Get pivot index, ie its sorted location 
            size_t j = partition(first, last);
            // Sort array part located left to pivot
            quickSort(first, j);
            // Sort array part located right to pivot
            quickSort(j+1, last);
        }
    }

    size_t partition(size_t first, size_t last)
    {
        // Pivot arbitrarily chosen as first element of partition
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

    ///// MERGE SORT, O(n log(n)) expected and worst case /////

    void mergeSort(size_t first, size_t last)
    {
        if (first < last)
        {
            size_t middle = (first + last) / 2;
            mergeSort(first, middle);
            mergeSort(middle + 1, last);
            merge(first, middle, last);
        }
    }

    void merge(size_t first, size_t middle, size_t last)
    {
        T* tmp = new T[last - first + 1];
        size_t i = first, j = middle + 1, k = 0;

        while (i <= middle && j <= last)
        {
            if (m_arr[i] <= m_arr[j])
            {
                tmp[k] = m_arr[i];
                ++k; ++i;
            }
            else
            {
                tmp[k] = m_arr[j];
                ++k; ++j;
            }
        }

        while (i <= middle)
        {
            tmp[k] = m_arr[i];
            ++k; ++i;
        }

        while (j <= last)
        {
            tmp[k] = m_arr[j];
            ++k; ++j;
        }

        for (i = first; i <= last; ++i)
        {
            m_arr[i] = tmp[i - first];
        }
    }
};

#endif // !_ARRAY_H