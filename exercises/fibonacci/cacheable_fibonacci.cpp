#include <iostream>
#include <map>

int fibonacci(int n, std::map<int,int>& map)
{
    if(n <= 2)
    {
        return 1;
    }
    if(map.count(n) == 0)
    {
        map.insert({n,fibonacci(n - 1, map) + fibonacci(n - 2, map)});
    }
    return map[n];
}

int main()
{   
    std::map<int,int> map;
    std::cout << "Result: " << fibonacci(1, map) << std::endl;
    std::cout << "Result: " << fibonacci(2, map) << std::endl;
    std::cout << "Result: " << fibonacci(3, map) << std::endl;
    std::cout << "Result: " << fibonacci(4, map) << std::endl;
    std::cout << "Result: " << fibonacci(8, map) << std::endl;
    std::cout << "Result: " << fibonacci(6, map) << std::endl;
}