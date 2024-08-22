#include <iostream>
#include <map>

int factorial(int n, std::map<int,int>& map)
{
    if(n < 1)
    {
        return 1;
    }
    if(map.count(n) == 0)
    {
        map.insert({n, n * factorial(n - 1, map)});
    }
    return map[n];
}

int main()
{   
    std::map<int,int> map;
    std::cout << "Result: " << factorial(13, map) << std::endl;
    std::cout << "Result: " << factorial(2, map) << std::endl;
    std::cout << "Result: " << factorial(21, map) << std::endl;
    std::cout << "Result: " << factorial(4, map) << std::endl;
    std::cout << "Result: " << factorial(8, map) << std::endl;
    std::cout << "Result: " << factorial(6, map) << std::endl;
}