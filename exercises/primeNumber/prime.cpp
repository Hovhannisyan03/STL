#include <iostream>

template <int NUM, int DIV>
struct check 
{
    static const bool result = (NUM % DIV) && check<NUM, DIV - 1>::result;
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

int main()
{
    std::cout << is_prime<11>::result;
}