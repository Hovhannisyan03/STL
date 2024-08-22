#include <iostream>

template <size_t N>
struct fibonacci
{
    static const size_t result = fibonacci<N - 1>::result + fibonacci<N - 2>::result;
};

template<>
struct fibonacci<0>
{
    static const size_t result = 0;
};

template<>
struct fibonacci<1>
{
    static const size_t result = 1;
};

