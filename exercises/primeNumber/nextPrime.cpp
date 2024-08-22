#include <iostream>

template <int NUM, int DIV>
struct check 
{
    static const bool result = (NUM % DIV) && check<NUM, DIV-1>::result;
};

template <int DIV>
struct check<0> 
{
    static const bool result = false;
};

template <int NUM>
struct check<NUM,1> 
{
    static const bool result = true;
};

template <int NUM>
struct check<NUM,1> 
{
    static const bool result = true;
};

template <int NUM>
struct check<NUM,1> 
{
    static const bool result = true;
};

template <int NUM>
struct is_prime 
{
    static const bool result = check<NUM, NUM - 1>::result;
};

template <int NUM>
struct next_prime_check
{
    static const int result = is_prime<NUM + 1>::result ? NUM + 1 : next_prime_check<NUM + 1>::result;
};

template <>
struct next_prime_check<0> 
{   
    static const int result = 2;
};

template <int NUM>
struct next_prime
{
    static const int result = next_prime_check<NUM>::result;
};

int main()
{
    std::cout << next_prime<5>::result;
}