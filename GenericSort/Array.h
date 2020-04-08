#ifndef _ARRAY_H
#define _ARRAY_H

#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
class Array
{
private:
    T* m_arr;
    size_t m_size;
    // For bucket sort
    const size_t m_nbBuckets = 4;

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

    void bubbleSort()
    {
        int i, j;
        for (i = 0; i < m_size - 1; ++i) 
            for (j = 0; j < m_size - i - 1; ++j)
                if (m_arr[j] > m_arr[j + 1])
                    swap(j, j + 1);
    }

    ///// SELECTION SORT, O(n^2) /////

    void selectionSort()
    {
        int i, j, min_idx;

        // Move through unsorted part of the array
        for (i = 0; i < m_size - 1; ++i)
        {
            // Find minimum element 
            min_idx = i;
            for (j = i + 1; j < m_size; ++j)
                if (m_arr[j] < m_arr[min_idx])
                    min_idx = j;

            // Swap minimum element with first element of unsorted part of the array  
            swap(min_idx, i);
        }
    }

    ///// BUCKET SORT, O(n) /////

    void bucketSort()
    {
        // Get min of array
        T min = *std::min_element(m_arr, m_arr + m_size);

        // Offset: make min become 0, either by shifting the array by +|min| or -|min|
        if (min < 0)
        {
            for (size_t i = 0; i < m_size; ++i)
            {
                m_arr[i] += std::abs(min);
            }
        }
        else
        {
            for (size_t i = 0; i < m_size; ++i)
            {
                m_arr[i] -= std::abs(min);
            }
        }

        // Get max of array
        T max = *std::max_element(m_arr, m_arr + m_size);

        // Create a vector of empty buckets 
        std::vector<std::vector<T>> buckets(m_nbBuckets);

        // Place each element of the array in its corresponding bucket
        for (size_t i = 0; i < m_size; ++i)
        {
            size_t index = (m_arr[i] / max) * (m_nbBuckets - 1);
            buckets[index].push_back(m_arr[i]);
        }

        // Sort each bucket 
        for (size_t i = 0; i < m_nbBuckets; ++i)
            std::sort(buckets[i].begin(), buckets[i].end());

        // Remove offset from array, which was added at the beginning
        if (min < 0)
        {
            for (size_t i = 0; i < m_nbBuckets; ++i)
            {
                for(size_t j = 0; j < buckets[i].size(); ++j)
                    buckets[i][j] -= std::abs(min);
            }
        }
        else
        {
            for (size_t i = 0; i < m_nbBuckets; ++i)
            {
                for (size_t j = 0; j < buckets[i].size(); ++j)
                    buckets[i][j] += std::abs(min);
            }
        }

        // Concatenate all buckets into m_arr
        size_t id = 0;
        for (size_t i = 0; i < m_nbBuckets; ++i)
            for (size_t j = 0; j < buckets[i].size(); ++j)
                m_arr[id++] = buckets[i][j];
    }

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