#include <iostream>

template <size_t N>
struct factorial
{
    static const size_t result = N * factorial<N-1>::result;
};

template <>
struct factorial<0>
{
    static const size_t result = 1;
};


