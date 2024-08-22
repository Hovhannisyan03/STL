#include <iostream>
#include <fstream>
#include <string>
// 1
template <typename T, typename ...Ts>
void print_1(T val, Ts... args)
{
    std::cout << val << " "; 
    if constexpr (sizeof...(args) > 0) 
    {
        print_1(args...); 
    } 
    else 
    {
        std::cout << std::endl; 
    }
}

// 2
template <typename ...Ts>
void print_2(Ts... args)
{
    ((std::cout << args << " "),...) << std::endl;
}

// 3
std::string sep() {
    return "->";
}

std::string end() {
    return "\n";
}

template<std::string (*sep)() = sep, std::string(*end)() = end, typename ...Ts>
void print_3(Ts... args) 
{
    int flag = 0;
    ((std::cout << (flag++ ? sep() : "") << args), ...) << end();
}

int main() 
{   
    print_3("Hello", "world", 42); 
    return 0;
}
