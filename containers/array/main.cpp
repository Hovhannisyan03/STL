#include "array.h"
#include <cassert>

void test_default_construction_and_initialization() {
    my_std::array<int, 5> arr = {1, 2, 3, 4, 5};

    assert(arr.size() == 5);
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);
    assert(arr[3] == 4);
    assert(arr[4] == 5);
}

void test_accessors() {
    my_std::array<int, 5> arr = {1, 2, 3, 4, 5};

    assert(arr.front() == 1);
    assert(arr.back() == 5);

    arr[2] = 10;
    assert(arr[2] == 10);

    try {
        arr.at(10);
        assert(false); 
    } catch (const std::out_of_range&) {
    }

    assert(arr.data() == &arr[0]);
}

void test_iterators() {
    my_std::array<int, 5> arr = {1, 2, 3, 4, 5};

    auto it = arr.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);

    auto cit = arr.cbegin();
    assert(*cit == 1);
    ++cit;
    assert(*cit == 2);

    auto rit = arr.rbegin();
    assert(*rit == 5);
    ++rit;
    assert(*rit == 4);

    auto crit = arr.crbegin();
    assert(*crit == 5);
    ++crit;
    assert(*crit == 4);
}

void test_fill_and_swap() {
    my_std::array<int, 5> arr1 = {1, 2, 3, 4, 5};
    my_std::array<int, 5> arr2 = {6, 7, 8, 9, 10};

    arr1.fill(42);
    assert(arr1[0] == 42);
    assert(arr1[1] == 42);
    assert(arr1[2] == 42);
    assert(arr1[3] == 42);
    assert(arr1[4] == 42);

    arr1.swap(arr2);
    assert(arr1[0] == 6);
    assert(arr2[0] == 42);
}

void test_empty_and_size() {
    my_std::array<int, 5> arr = {1, 2, 3, 4, 5};

    assert(!arr.empty());
    assert(arr.size() == 5);
    assert(arr.max_size() == 5);
}

void test_const_and_reverse_iterators() {
    const my_std::array<int, 5> arr = {1, 2, 3, 4, 5};

    auto cit = arr.cbegin();
    assert(*cit == 1);
    ++cit;
    assert(*cit == 2);

    auto crit = arr.crbegin();
    assert(*crit == 5);
    ++crit;
    assert(*crit == 4);
}

void test_comparison_operators() {
    my_std::array<int, 5> arr1 = {1, 2, 3, 4, 5};
    my_std::array<int, 5> arr2 = {1, 2, 3, 4, 5};
    my_std::array<int, 5> arr3 = {5, 4, 3, 2, 1};

    assert(arr1 == arr2);
    assert(!(arr1 != arr2));
    assert(arr1 != arr3);
    assert(arr1 < arr3);
    assert(arr3 > arr1);
}

int main() {
    try {
        test_default_construction_and_initialization();
        test_accessors();
        test_iterators();
        test_fill_and_swap();
        test_empty_and_size();
        test_const_and_reverse_iterators();
        test_comparison_operators();
        
        std::cout << "All tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}