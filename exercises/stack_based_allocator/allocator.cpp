#include <iostream>
#include <memory>

constexpr size_t memory_size = 5000;
char memory[memory_size];

template <typename T>
class Allocator
{
    public:
        using value_type = T;
        using size_type = size_t;
        using pointer = T*;
        using const_pointer = const T*;
    public:
        Allocator() : offset(0){}
        pointer allocate(size_type count)
        {   
            if(offset + count * sizeof(T) > memory_size)
            {
                throw std::bad_alloc();
            }
            pointer res = static_cast<pointer>(static_cast<void*>(memory + offset));
            offset += count * sizeof(T);
            return res;

        }
        void deallocate(void* ptr, size_type size){}  
        template <typename ...Args>
        void construct(pointer ptr, Args ... args)
        {
            std::construct_at(ptr, std::forward<Args>(args)...);
        }
        void destroy(void* ptr)
        {
            std::destroy_at(static_cast<pointer>(ptr));
        }
    private:
        size_type offset;
};

int main()
{
    Allocator<int> alloc;
    int val = 0;
    int* ptr = alloc.allocate(10);

    std::cout << "Enter elements of the first arrray: ";
    for(size_t i = 0; i < 10; ++i)
    {
        std::cin >> val;
        alloc.construct(ptr + i, val);
    }
    std::cout << std::endl;

    
    int* ptr2 = alloc.allocate(5);
    std::cout << "Enter elements of the second arrray: ";
    for(size_t i = 0; i < 5; ++i)
    {
        std::cin >> val;
        alloc.construct(ptr2 + i, val);
    }
    std::cout << std::endl;

    std::cout << "Arr1 = [";
    for(size_t i = 0; i < 10; ++i)
    {
        std::cout <<" " << ptr[i];
    }
    std::cout << " ] " << std::endl;

    std::cout << "Arr2 = [";
    for(size_t i = 0; i < 5; ++i)
    {
        std::cout <<" " << ptr2[i];
    }
    std::cout << " ] " << std::endl;

    for (int i = 0; i < 10; ++i) 
    {
        alloc.destroy(ptr + i);
    }
    for (int i = 0; i < 5; ++i) 
    {
        alloc.destroy(ptr2 + i);
    }
    alloc.deallocate(ptr, 10);
    alloc.deallocate(ptr2, 5);

}