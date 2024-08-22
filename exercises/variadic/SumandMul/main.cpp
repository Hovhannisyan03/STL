#include <iostream>

template <typename T>
T sum(T val) 
{
    return val;
}

template <typename T, typename ...Ts>
T sum(T val, Ts... args) 
{
    return val + sum(args...);
}

template <typename T>
T mul(T val) 
{
    return val;
}

template <typename T, typename ...Ts>
T mul(T val, Ts... args) 
{
    return val * mul(args...);
}


int main() 
{
    std::cout << sum(4.4, 2, 4, 6, 3.2) << std::endl;   
    std::cout << sum(1.8, 2.5 ,25.2, 9) << std::endl; 
    std::cout << sum(19, 21, 0.5) << std::endl;  

    std::cout << mul(4, 5, 2.1, 7.5) << std::endl;   
    std::cout << mul(5.5, 20, 30.0) << std::endl; 
    std::cout << mul(7.9, 55) << std::endl;               
    return 0;
}
