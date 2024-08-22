#include "array.h"

template <class T, size_t N>
my_std::array<T,N>::array() : m_arr{0}, m_size{0} {}

template <class T, size_t N>
my_std::array<T,N>::array(std::initializer_list<value_type> init) : m_arr{0}, m_size{0}
{   
    for(const auto& elem : init)
    {
        m_arr[m_size++] = elem;
    }
}

template <class T, size_t N>
my_std::array<T,N>::array(const array& other) : m_arr{0}, m_size{other.m_size}
{
    for(size_type i = 0; i < N; ++i)
    {
        m_arr[i] = other.m_arr[i];
    }
}

template <class T, size_t N>
my_std::array<T,N>::array(array&& other) noexcept : m_arr{0}, m_size{other.m_size}
{
    for(size_type i = 0; i < N; ++i)
    {
        m_arr[i] = other.m_arr[i];
    }
    other.m_size = 0;    
}

template <class T, size_t N>
const my_std::array<T,N>& my_std::array<T,N>::operator=(std::initializer_list<value_type> init)
{
    m_size = 0;
    for(const auto& elem : init)
    {
        m_arr[m_size++] = elem;
    }
    if(m_size < N)
    {
        for(size_type i = m_size; i < N; ++i)
        {
            m_arr[i] = 0;
        }
    }
    return *this;
}

template <class T, size_t N>
const my_std::array<T,N>& my_std::array<T,N>::operator=(const array& other) 
{
    m_size = other.m_size;
    for(size_type i = 0; i < N; ++i)
    {
        m_arr[i] = other.m_arr[i];
    }
    return *this;
}

template <class T, size_t N>
const my_std::array<T,N>& my_std::array<T,N>::operator=(array&& other) noexcept 
{
    m_size = other.m_size;
    other.m_size = 0;    
    for(size_type i = 0; i < N; ++i)
    {
        m_arr[i] = other.m_arr[i];
    }
    return *this;
}

template <class T, size_t N>
typename my_std::array<T,N>::reference my_std::array<T,N>::at(size_type pos)
{
    if(pos >= N)
    {
        throw std::out_of_range("Out of range");
    }
    return m_arr[pos];
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reference my_std::array<T,N>::at(size_type pos)const
{
    if(pos >= N)
    {
        throw std::out_of_range("Out of range");
    }
    return m_arr[pos];
}


template <class T, size_t N>
typename my_std::array<T,N>::reference my_std::array<T,N>::operator[](size_type pos)
{
    return m_arr[pos];
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reference my_std::array<T,N>::operator[](size_type pos)const
{
    return m_arr[pos];
}

template <class T, size_t N>
typename my_std::array<T,N>::reference my_std::array<T,N>::front()
{
    if(N == 0)
    {
        throw std::logic_error("Array is empty");
    }
    return m_arr[0];
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reference my_std::array<T,N>::front() const
{
    if(N == 0)
    {
        throw std::logic_error("Array is empty");
    }
    return m_arr[0];
}

template <class T, size_t N>
typename my_std::array<T,N>::reference my_std::array<T,N>::back()
{
    if(N == 0)
    {
        throw std::logic_error("Array is empty");
    }
    return m_arr[N - 1];
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reference my_std::array<T,N>::back() const
{
    if(N == 0)
    {
        throw std::logic_error("Array is empty");
    }
    return m_arr[N - 1];
}

template <class T, size_t N>
typename my_std::array<T,N>::pointer my_std::array<T,N>::data() 
{
    if(N == 0)
    {
        throw std::logic_error("Array is empty");
    }
    return m_arr;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_pointer my_std::array<T,N>::data() const
{
    if(N == 0)
    {
        throw std::logic_error("Array is empty");
    }
    return m_arr;
}

template <class T, size_t N>
constexpr bool my_std::array<T,N>::empty() const noexcept
{
    return N == 0;
}

template <class T, size_t N>
constexpr typename my_std::array<T,N>::size_type my_std::array<T,N>::size() const noexcept
{
    return m_size;
}

template <class T, size_t N>
constexpr typename my_std::array<T,N>::size_type my_std::array<T,N>::max_size() const noexcept
{
    return N;
}

template <class T, size_t N>
void my_std::array<T,N>::fill(const_reference val)
{
    for(size_type i = 0; i < N; ++i)
    {
        m_arr[i] = val;
    }
}

template <class T, size_t N>
void my_std::array<T,N>::swap(array& other) noexcept
{
    for(size_type i = 0; i < N; ++i)
    {
        value_type temp = m_arr[i];
        m_arr[i] = other.m_arr[i];
        other.m_arr[i] = temp;
    }
}

template <class T, size_t N>
std::strong_ordering my_std::array<T, N>::operator<=>(const array& other) const 
{
    return std::lexicographical_compare_three_way
    (
        this->m_arr, this->m_arr + N,
        other.m_arr, other.m_arr + N
    );
}

template <class T, size_t N>
bool my_std::array<T, N>::operator==(const array& other) const 
{
    return (*this <=> other) == std::strong_ordering::equal;
}

template <class T, size_t N>
bool my_std::array<T, N>::operator!=(const array& other) const 
{
    return !(*this == other);
}

template <class T, size_t N>
bool my_std::array<T, N>::operator<(const array& other) const 
{
    return (*this <=> other) == std::strong_ordering::less;
}

template <class T, size_t N>
bool my_std::array<T, N>::operator<=(const array& other) const 
{
    auto cmp = *this <=> other;
    return cmp == std::strong_ordering::less || cmp == std::strong_ordering::equal;
}

template <class T, size_t N>
bool my_std::array<T, N>::operator>(const array& other) const 
{
    return (*this <=> other) == std::strong_ordering::greater;
}

template <class T, size_t N>
bool my_std::array<T, N>::operator>=(const array& other) const 
{
    auto cmp = *this <=> other;
    return cmp == std::strong_ordering::greater || cmp == std::strong_ordering::equal;
}
// ======================================================== Const Iterator ========================================================
template <class T, size_t N>
my_std::array<T,N>::const_iterator::const_iterator(const_pointer ptr) : m_ptr(ptr) {}

template <class T, size_t N>
typename my_std::array<T,N>::const_iterator my_std::array<T,N>::const_iterator::operator+(size_type n) const
{
    return const_iterator(m_ptr + n);
}

template <class T, size_t N>
typename my_std::array<T,N>::const_iterator my_std::array<T,N>::const_iterator::operator-(size_type n) const
{
    return const_iterator(m_ptr - n);
}

template <class T, size_t N>
typename my_std::array<T,N>::const_iterator& my_std::array<T,N>::const_iterator::operator++()
{
    ++m_ptr;
    return *this;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_iterator my_std::array<T,N>::const_iterator::operator++(int)
{
    const_iterator temp = *this;
    ++m_ptr;
    return temp;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_iterator& my_std::array<T,N>::const_iterator::operator--()
{
    --m_ptr;
    return *this;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_iterator my_std::array<T,N>::const_iterator::operator--(int)
{
    const_iterator temp = *this;
    --m_ptr;
    return temp;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reference my_std::array<T,N>::const_iterator::operator*() const
{
    return *m_ptr;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_pointer my_std::array<T,N>::const_iterator::operator->() const
{
    return m_ptr;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reference my_std::array<T,N>::const_iterator::operator[](size_type pos) const
{
    return m_ptr[pos];
}

template <class T, size_t N>
bool my_std::array<T,N>::const_iterator::operator==(const const_iterator& other) const
{
    return m_ptr == other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::const_iterator::operator!=(const const_iterator& other) const
{
    return m_ptr != other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::const_iterator::operator<(const const_iterator& other) const
{
    return m_ptr < other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::const_iterator::operator<=(const const_iterator& other) const
{
    return m_ptr <= other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::const_iterator::operator>(const const_iterator& other) const
{
    return m_ptr > other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::const_iterator::operator>=(const const_iterator& other) const
{
    return m_ptr >= other.m_ptr;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_iterator my_std::array<T,N>::cbegin() const noexcept 
{
    return const_iterator(m_arr);
}

template <class T, size_t N>
typename my_std::array<T,N>::const_iterator my_std::array<T,N>::cend() const noexcept 
{
    return const_iterator(m_arr + N);
}

template <class T, size_t N>
typename my_std::array<T,N>::const_iterator my_std::array<T,N>::begin() const noexcept 
{
    return const_iterator(m_arr);
}

template <class T, size_t N>
typename my_std::array<T,N>::const_iterator my_std::array<T,N>::end() const noexcept 
{
    return const_iterator(m_arr + N);
}
// ======================================================== Iterator ========================================================
template <class T, size_t N>
my_std::array<T,N>::iterator::iterator(pointer ptr) : const_iterator(ptr), m_ptr{ptr} {}

template <class T, size_t N>
typename my_std::array<T,N>::iterator my_std::array<T,N>::iterator::operator+(size_type n) const
{
    return iterator(this->m_ptr + n);
}

template <class T, size_t N>
typename my_std::array<T,N>::iterator my_std::array<T,N>::iterator::operator-(size_type n) const
{
    return iterator(this->m_ptr - n);
}

template <class T, size_t N>
typename my_std::array<T,N>::iterator& my_std::array<T,N>::iterator::operator++()
{
    ++(this->m_ptr);
    return *this;
}

template <class T, size_t N>
typename my_std::array<T,N>::iterator my_std::array<T,N>::iterator::operator++(int)
{
    iterator temp = *this;
    ++(this->m_ptr);
    return temp;
}

template <class T, size_t N>
typename my_std::array<T,N>::iterator& my_std::array<T,N>::iterator::operator--()
{
    --(this->m_ptr);
    return *this;
}

template <class T, size_t N>
typename my_std::array<T,N>::iterator my_std::array<T,N>::iterator::operator--(int)
{
    iterator temp = *this;
    --(this->m_ptr);
    return temp;
}

template <class T, size_t N>
typename my_std::array<T,N>::reference my_std::array<T,N>::iterator::operator*()
{
    return *(this->m_ptr);
}

template <class T, size_t N>
typename my_std::array<T,N>::pointer my_std::array<T,N>::iterator::operator->()
{
    return this->m_ptr;
}

template <class T, size_t N>
typename my_std::array<T,N>::reference my_std::array<T,N>::iterator::operator[](size_type pos) const
{
    return this->m_ptr[pos];
}

template <class T, size_t N>
typename my_std::array<T,N>::iterator my_std::array<T,N>::begin() noexcept 
{
    return iterator(m_arr);
}

template <class T, size_t N>
typename my_std::array<T,N>::iterator my_std::array<T,N>::end() noexcept 
{
    return iterator(m_arr + N);
}

template <class T, size_t N>
bool my_std::array<T,N>::iterator::operator==(const iterator& other) const
{
    return m_ptr == other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::iterator::operator!=(const iterator& other) const
{
    return m_ptr != other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::iterator::operator<(const iterator& other) const
{
    return m_ptr < other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::iterator::operator<=(const iterator& other) const
{
    return m_ptr <= other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::iterator::operator>(const iterator& other) const
{
    return m_ptr > other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::iterator::operator>=(const iterator& other) const
{
    return m_ptr >= other.m_ptr;
}

// ======================================================== Const Reverse Iterator ========================================================
template <class T, size_t N>
my_std::array<T,N>::const_reverse_iterator::const_reverse_iterator(const_pointer ptr) : m_ptr(ptr) {}

template <class T, size_t N>
typename my_std::array<T,N>::const_reverse_iterator my_std::array<T,N>::const_reverse_iterator::operator+(size_type n) const 
{
    return const_reverse_iterator(m_ptr - n);
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reverse_iterator my_std::array<T,N>::const_reverse_iterator::operator-(size_type n) const 
{
    return const_reverse_iterator(m_ptr + n);
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reverse_iterator& my_std::array<T,N>::const_reverse_iterator::operator++() 
{
    --m_ptr;
    return *this;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reverse_iterator my_std::array<T,N>::const_reverse_iterator::operator++(int) 
{
    const_reverse_iterator temp = *this;
    --m_ptr;
    return temp;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reverse_iterator& my_std::array<T,N>::const_reverse_iterator::operator--() 
{
    ++m_ptr;
    return *this;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reverse_iterator my_std::array<T,N>::const_reverse_iterator::operator--(int) 
{
    const_reverse_iterator temp = *this;
    ++m_ptr;
    return temp;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reference my_std::array<T,N>::const_reverse_iterator::operator*() const 
{
    return *m_ptr;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_pointer my_std::array<T,N>::const_reverse_iterator::operator->() const 
{
    return m_ptr;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reference my_std::array<T,N>::const_reverse_iterator::operator[](size_type pos) const 
{
    return m_ptr[pos];
}

template <class T, size_t N>
bool my_std::array<T,N>::const_reverse_iterator::operator==(const const_reverse_iterator& other) const
{
    return m_ptr == other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::const_reverse_iterator::operator!=(const const_reverse_iterator& other) const
{
    return m_ptr != other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::const_reverse_iterator::operator<(const const_reverse_iterator& other) const
{
    return m_ptr > other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::const_reverse_iterator::operator<=(const const_reverse_iterator& other) const
{
    return m_ptr >= other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::const_reverse_iterator::operator>(const const_reverse_iterator& other) const
{
    return m_ptr < other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::const_reverse_iterator::operator>=(const const_reverse_iterator& other) const
{
    return m_ptr <= other.m_ptr;
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reverse_iterator my_std::array<T,N>::crbegin() const noexcept
{
    return const_reverse_iterator(m_arr + N - 1);
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reverse_iterator my_std::array<T,N>::crend() const noexcept
{
    return const_reverse_iterator(m_arr - 1);
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reverse_iterator my_std::array<T,N>::rbegin() const noexcept
{
    return const_reverse_iterator(m_arr + N - 1);
}

template <class T, size_t N>
typename my_std::array<T,N>::const_reverse_iterator my_std::array<T,N>::rend() const noexcept
{
    return const_reverse_iterator(m_arr - 1);
}

// ======================================================== Reverse Iterator ========================================================

template <class T, size_t N>
my_std::array<T,N>::reverse_iterator::reverse_iterator(pointer ptr) : const_reverse_iterator(ptr), m_ptr(ptr) {}

template <class T, size_t N>
typename my_std::array<T,N>::reverse_iterator my_std::array<T,N>::reverse_iterator::operator+(size_type n) const 
{
    return reverse_iterator(this->m_ptr - n);
}

template <class T, size_t N>
typename my_std::array<T,N>::reverse_iterator my_std::array<T,N>::reverse_iterator::operator-(size_type n) const 
{
    return reverse_iterator(this->m_ptr + n);
}

template <class T, size_t N>
typename my_std::array<T,N>::reverse_iterator& my_std::array<T,N>::reverse_iterator::operator++() 
{
    --(this->m_ptr);
    return *this;
}

template <class T, size_t N>
typename my_std::array<T,N>::reverse_iterator my_std::array<T,N>::reverse_iterator::operator++(int) 
{
    reverse_iterator temp = *this;
    --(this->m_ptr);
    return temp;
}

template <class T, size_t N>
typename my_std::array<T,N>::reverse_iterator& my_std::array<T,N>::reverse_iterator::operator--() 
{
    ++(this->m_ptr);
    return *this;
}

template <class T, size_t N>
typename my_std::array<T,N>::reverse_iterator my_std::array<T,N>::reverse_iterator::operator--(int) 
{
    reverse_iterator temp = *this;
    ++(this->m_ptr);
    return temp;
}

template <class T, size_t N>
typename my_std::array<T,N>::reference my_std::array<T,N>::reverse_iterator::operator*()
{
    return *(this->m_ptr);
}

template <class T, size_t N>
typename my_std::array<T,N>::pointer my_std::array<T,N>::reverse_iterator::operator->()
{
    return this->m_ptr;
}

template <class T, size_t N>
typename my_std::array<T,N>::reference my_std::array<T,N>::reverse_iterator::operator[](size_type pos) const 
{
    return this->m_ptr[pos];
}

template <class T, size_t N>
typename my_std::array<T,N>::reverse_iterator my_std::array<T,N>::rbegin() noexcept
{
    return reverse_iterator(m_arr + N - 1);
}

template <class T, size_t N>
typename my_std::array<T,N>::reverse_iterator my_std::array<T,N>::rend() noexcept
{
    return reverse_iterator(m_arr - 1);
}

template <class T, size_t N>
bool my_std::array<T,N>::reverse_iterator::operator==(const reverse_iterator& other) const
{
    return m_ptr == other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::reverse_iterator::operator!=(const reverse_iterator& other) const
{
    return m_ptr != other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::reverse_iterator::operator<(const reverse_iterator& other) const
{
    return m_ptr > other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::reverse_iterator::operator<=(const reverse_iterator& other) const
{
    return m_ptr >= other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::reverse_iterator::operator>(const reverse_iterator& other) const
{
    return m_ptr < other.m_ptr;
}

template <class T, size_t N>
bool my_std::array<T,N>::reverse_iterator::operator>=(const reverse_iterator& other) const
{
    return m_ptr <= other.m_ptr;
}
