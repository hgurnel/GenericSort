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

    /*Browse array and everytime a greater element is found at j+1, swap it with
    the current one at j*/
    void bubbleSort()
    {
        int i, j;
        for (i = 0; i < m_size - 1; ++i) 
            for (j = 0; j < m_size - i - 1; ++j)
                if (m_arr[j] > m_arr[j + 1])
                    swap(j, j + 1);
    }

    ///// SELECTION SORT, O(n^2) /////

    /*The array is divided in two parts: the sorted part, on the left, and the 
    unsorted part, on the right. At first, the sorted part does not exist, so
    an index "i=0" is defined to browse the array element by element. At each
    iteration, the algorithm looks for the index of the lowest element of the 
    array, located right to i. This index is denoted by minId. Its corresponding
    element is then swapped with array[i].*/
    void selectionSort()
    {
        int i, j, minId;

        // Move within unsorted part of the array
        for (i = 0; i < m_size - 1; ++i)
        {
            // Find index of minimal element 
            minId = i;
            for (j = i + 1; j < m_size; ++j)
                if (m_arr[j] < m_arr[minId])
                    minId = j;

            // Swap minimum element with first element of unsorted part of the array  
            swap(minId, i);
        }
    }

    ///// BUCKET SORT, O(n) /////

    /*This sorting algorithm is adapted to arrays whose elements belong to a 
    range of values (positive or negative, decimal or integer values). The
    idea is to create "buckets", each covering a fraction of this range. 
    The elements of the array are then placed in their corresponding bucket.
    Each bucket is sorted and finally all the buckets are merged, to produce
    the final sorted array. Here, to deal with negative and positive numbers,
    the algorithm starts by applying an offset to the array, in order to bring
    its minimum to zero. A vector of empty buckets is then created, to host the
    elements of the array. The buckets are sorted, the offset is removed, to 
    get back in the original range of values, and the buckets are merged, to 
    produce the final array.*/
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

    /*This algorithm works by defining a partition, ie finding the sorted 
    position of a pivot element. A sorted position for the pivot corresponds
    to the index for which all the elements of the array located left to the
    pivot are lower than the pivot, while all those located right to it are greater. 
    A partition corresponds to the sorted position of the pivot and the two parts of 
    the array: left to the pivot and right of the pivot. Once a partition has been 
    obtained, the left and right part are sorted individually, using quick sort, 
    iteratively*/
    void quickSort(size_t first, size_t last)
    {
        // Recursion stopping condition: when paritition has only one element
        if (first < last)
        {
            // Get pivot index, ie its sorted location 
            size_t j = partition(first, last);
            // Sort array part located left to pivot
            quickSort(first, j);
            // Sort array part located right to pivot
            quickSort(j+1, last);
        }
    }

    /* The functions takes a partition as an input. It is either the full array
    or a fraction of it, defined by the "first" and "last" indexes. The function
    builds a new partition by placing the elements smaller than the pivot on its
    left and those that are greater on its right. It returns the sorted position
    of the pivot, whose initial position is arbitrarily chosen as first element 
    of the input partition. 
    To find this sorted position, two cursors i and j are defined. i is used to 
    browse the input partition from the start, while j is used to browse it from 
    its end. Everytime an element partition[i] is found greater than pivot, and an 
    element partition[j] is found smaller than pivot, those two are swapped, to end 
    up in the right part of the partition. When i and j are about to intersect, j 
    corresponds to the sorted position of the pivot. Thus, the pivot is placed there,
    by swapping the first element of the partition with partition[j].*/
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

        // Place the pivot at its sorted position, ie j
        swap(first, j);

        // Return the sorted position of the pivot
        return j;
    }

    ///// MERGE SORT, O(n log(n)) expected and worst case /////

    /*This algorithms splits the array into two, by defining a middle element.
    The algorithm is then applied recursively to the left and right parts 
    separately, in order to further split the array into smaller ones. Once 
    splitting is done, the partitions are merged (and so sorted) to produce the
    final array.*/
    void mergeSort(size_t first, size_t last)
    {
        // Condition used to check is the array has at least two elements
        if (first < last)
        {
            size_t middle = (first + last) / 2;
            mergeSort(first, middle);
            mergeSort(middle + 1, last);
            merge(first, middle, last);
        }
    }

    /* This function considers two subarrays within the input array,
    the left part and the right part. It also creates a third array, "tmp", which
    will host the result of the merging operation. 
    At each iteration, one element from the left part and one from the right part 
    are compared. The lowest one is added to tmp. 
    At the end, the content of tmp is copied into m_arr.*/
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