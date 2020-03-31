#include "Array.h"

// Ctor
template <typename T>
Array<T>::Array(T arr[], size_t size) : m_size(size)
{
    m_arr = new T[m_size];
    for (auto i : m_arr)
        m_arr[i] = arr[i];
}

// Dtor
template <typename T>
Array<T>::~Array()
{
    delete[] m_arr;
}

template <typename T>
T & Array<T>::operator[](size_t index)
{
    return m_arr[index];
}

template <typename T>
void Array<T>::print()
{
    std::for_each(std::begin(m_arr), std::end(m_arr), std::cout);
}

template <typename T>
void Array<T>::swap(T arr[], size_t a, size_t b)
{
    T tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}