#include <iostream>

std::string sep() 
{
    return "->";
}
std::string end()
{
    return "\n";
}
template<std::string (*sep)() = sep, std::string(*end)() = end, typename ...Ts>
void print(Ts... args)
{
    ((std::cout << args << sep()), ...) << end();
}