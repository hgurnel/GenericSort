#include "ArrayHG.h"

// Ctor
template <typename T, int size>
ArrayHG<T, size>::ArrayHG(){}

// Dtor
template <typename T, int size>
ArrayHG<T, size>::~ArrayHG()
{
    delete[] m_arr;
}

template <typename T, int size>
T& ArrayHG<T, size>::operator[](int i)
{
    return m_arr[i];
}

template <typename T, int size>
void ArrayHG<T, size>::print()
{
    std::for_each(std::begin(m_arr), std::end(m_arr), print);
}

template <typename T, int size>
void ArrayHG<T, size>::swap(T a, T b)
{

}