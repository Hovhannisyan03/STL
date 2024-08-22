#include "array.h"

int main()
{
    const my_std::array<int, 8> arr1 = {1,2,3,4,5,6,7,8};
    my_std::array<int, 8> arr2 = {8,7,6,5,4,3,2,1};

    // if(arr1 != arr2)
    // {
    //     std::cout << "asd" << std::endl;
    // }
    // for(auto elem : arr1)
    // {
    //     std::cout << elem << " ";
    // }
    // std::cout << std::endl;

    for(my_std::array<int,8>::iterator it = arr2.begin(); it != arr2.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for(my_std::array<int,8>::const_iterator it = arr2.begin(); it != arr2.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for(my_std::array<int,8>::const_iterator it = arr2.cbegin(); it != arr2.cend(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    for(my_std::array<int,8>::reverse_iterator it = arr2.rbegin(); it != arr2.rend(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for(my_std::array<int,8>::const_reverse_iterator it = arr2.rbegin(); it != arr2.rend(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for(my_std::array<int,8>::const_reverse_iterator it = arr2.crbegin(); it != arr2.crend(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // for(my_std::array<int,8>::iterator it = arr2.begin(); it != arr2.end(); it++)
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;

// std::cout << "asdsadsa";

//   for(my_std::array<int,8>::const_iterator it = arr2.begin(); it != arr2.end(); it++)
//     {
//         std::cout << *it << " ";
//     }
//     std::cout << std::endl;

    // for(my_std::array<int,8>::const_reverse_iterator it = arr2.rbegin(); it != arr2.rend(); it++)
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;

    // for(my_std::array<int,8>::const_iterator it = arr1.cbegin(); it != arr1.cend(); it++)
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;

    // for(my_std::array<int,8>::const_reverse_iterator it = arr1.crbegin(); it != arr1.crend(); it = it + 2)
    // {
    //     std::cout << *it << " ";
    // }
    // for(int i = 0; i < 8; ++i)
    // {
    //     std::cout << arr2[i] << " ";
    // }
    // arr1.swap(arr2);
    //     std::cout << std::endl;

    // for(int i = 0; i < 8; ++i)
    // {
    //     std::cout << arr1[i] << " ";
    // }
    // std::cout << std::endl;

    // for(int i = 0; i < 8; ++i)
    // {
    //     std::cout << arr2[i] << " ";
    // }
    // std::cout << arr.empty() << " " << arr.size() << " " << arr.max_size() << std::endl;

    // std::cout << arr.empty() << " " << arr.size() << " " << arr.max_size() << std::endl;
    // // *(arr.data()) = 13;

    // for(int i = 0; i < 8; ++i)
    // {
    //     std::cout << arr[i] << " ";
    // }

    // std::cout << std::endl;

    // my_std::array<int,4> arr2 = std::move(arr);

    // arr = {4,2};
    // my_std::array<int, 4> arr4;
    // arr4 = arr;
    // for(int i = 0; i < 4; ++i)
    // {
    //     std::cout << arr[i] << " ";
    // }

    // std::cout << std::endl;

    // for(int i = 0; i < 4; ++i)
    // {
    //     std::cout << arr2[i] << " ";
    // }
}