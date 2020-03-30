#include "ArrayHG.h"

// Ctor
template <typename T, size_t size>
ArrayHG<T, size>::ArrayHG(){}

// Dtor
template <typename T, size_t size>
ArrayHG<T, size>::~ArrayHG()
{
    delete[] m_arr;
}

template <typename T, size_t size>
T& ArrayHG<T, size>::operator[](int i)
{
    return m_arr[i];
}

void ArrayHG<T, size>::print()
{
    std::for_each(std::begin(m_arr), std::end(m_arr), print);
}

template <typename T, size_t size>
void ArrayHG<T, size>::swap(T a, T b)
{

}