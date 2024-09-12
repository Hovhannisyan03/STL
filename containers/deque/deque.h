#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <initializer_list>
#include <memory>
#include <new>
#include <utility>
#include <compare>

namespace my_deque
{

    template <typename T>
    class DequeAllocator 
    {
    public:
        using value_type = T;

        DequeAllocator() noexcept = default;

        template <typename U>
        DequeAllocator(const DequeAllocator<U>&) noexcept {}

        T* allocate(std::size_t n) 
        {
            if (n == 0) return nullptr;
            void* ptr = std::malloc(n * sizeof(T));
            if (!ptr) throw std::bad_alloc();
            return static_cast<T*>(ptr);
        }

        void deallocate(T* p, std::size_t n) noexcept 
        {
            std::free(p);
        }

        template <typename U, typename... Args>
        void construct(U* p, Args&&... args) 
        {
            new (p) U(std::forward<Args>(args)...);
        }

        template <typename U>
        void destroy(U* p) noexcept 
        {
            p->~U();
        }

        template <typename U>
        struct rebind {
            using other = DequeAllocator<U>;
        };
    };

    template <typename T, typename U>
    bool operator==(const DequeAllocator<T>&, const DequeAllocator<U>&) noexcept {
        return true;
    }

    template <typename T, typename U>
    bool operator!=(const DequeAllocator<T>& lhs, const DequeAllocator<U>& rhs) noexcept {
        return !(lhs == rhs);
    }

    template <class T,  class Allocator = DequeAllocator<T>>
    class deque
    {
        public:
            using value_type = T;
            using size_type = size_t;
            using allocator_type = Allocator;
            using reference = T&;
            using const_reference = const T&;
            using pointer = T*;
            using const_pointer = const T*;
            using bf_type = double;

        public:
            class iterator;
            class const_iterator;
            class reverse_iterator;
            class const_reverse_iterator;
            
        public:
            deque();
            explicit deque(const Allocator& aloc);
            explicit deque(size_type count, const Allocator& alloc = Allocator());
            deque (size_type count, const value_type& val, const Allocator& alloc = Allocator());
            deque(const deque& other);
            deque(const deque& other, const Allocator& alloc);
            deque(deque&& other) noexcept;
            deque(deque&& other, const Allocator& alloc) noexcept;
            deque(std::initializer_list<T> init, const Allocator& alloc = Allocator());
            template<typename InputIt>
            deque(InputIt first, InputIt last);
            ~deque();
            allocator_type get_allocator() const;

        public:
            deque& operator=(const deque& other);
            deque& operator=(deque&& other) noexcept;
            deque& operator=(std::initializer_list<value_type> init);
            
            void assign(size_type count, const value_type& val);
            template<class InputIt>
            void assign(InputIt first, InputIt last);
            void assign(std::initializer_list<value_type> init); 

        public:
            reference at(size_type pos);
            const_reference at(size_type pos) const;

            reference operator[](size_type pos);
            const_reference operator[](size_type pos) const;

            reference front();
            const_reference front() const;
            reference back();
            const_reference back() const;

        public:
            iterator begin();
            const_iterator begin() const;
            const_iterator cbegin() const noexcept;

            iterator end();
            const_iterator end() const;
            const_iterator cend() const noexcept;

            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;
            const_reverse_iterator crbegin() const noexcept;

            reverse_iterator rend();
            const_reverse_iterator rend() const;
            const_reverse_iterator crend() const noexcept;

        public:
            bool empty() const;
            size_type size() const;
            void shrink_to_fit();

        public:
            void clear();

            iterator insert(const_iterator pos, const value_type& value);
            iterator insert(const_iterator pos,size_type count, const value_type& value);
            iterator insert(const_iterator pos, const_iterator first, const_iterator last);
            iterator insert(const_iterator pos, std::initializer_list<T> init);

            iterator erase(const_iterator pos);
            iterator erase(const_iterator first, const_iterator last);

            void push_back(const value_type& value);
            void push_back(value_type&& value);
            void push_front(const value_type& value);
            void push_front(value_type&& value);
            void pop_back();
            void pop_front();
            void resize(size_type count);
            void resize(size_type count, const value_type& value);
            void swap(deque& other) noexcept;

        private:
            void reserve(size_type newCapacity, bool left = true);
            bool balance_factor() const;
            void rebalance();
           
            value_type *m_left;
            value_type *m_right;
            size_type m_l_size;
            size_type m_r_size;
            size_type m_l_capacity;
            size_type m_r_capacity;
            Allocator m_alloc;
    };
}

template<class T, class Alloc>
std::strong_ordering operator<=>(const my_deque::deque<T, Alloc>& lhs, const my_deque::deque<T, Alloc>& rhs) 
{
    if (auto cmp = lhs.size() <=> rhs.size(); cmp != 0) 
    {
        return cmp;
    }

    auto lhs_it = lhs.begin();
    auto rhs_it = rhs.begin();
    for (; lhs_it != lhs.end(); ++lhs_it, ++rhs_it) 
    {
        if (auto cmp = *lhs_it <=> *rhs_it; cmp != 0) 
        {
            return cmp;
        }
    }

    return std::strong_ordering::equal;
}

template <typename T, class Allocator>
class my_deque::deque<T,Allocator>::const_iterator
{
        friend class deque<T,Allocator>;
    protected:
        pointer m_ptr;        
        pointer m_left;
        pointer m_right;
    private:
        const_iterator(pointer ptr = nullptr, pointer left = nullptr, pointer right = nullptr);
    public:
        const_iterator() = default;
        const_iterator(const const_iterator&) = default;      
        const_iterator(const_iterator&&) = default;

        const_iterator& operator=(const const_iterator&) = default;      
        const_iterator& operator=(const_iterator&&) = default;

        const_iterator operator+(size_type n) const;      
        const_iterator operator-(size_type n) const;

        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);

        const_reference operator*() const;
        const_pointer operator->() const;

        // const_reference operator[](size_type pos) const;

        bool operator==(const const_iterator& other) const;      
        bool operator!=(const const_iterator& other) const;      
        bool operator<(const const_iterator& other) const;      
        bool operator<=(const const_iterator& other) const;      
        bool operator>(const const_iterator& other) const;      
        bool operator>=(const const_iterator& other) const;      
};

template <typename T, class Allocator>
class my_deque::deque<T,Allocator>::iterator : public my_deque::deque<T,Allocator>::const_iterator
{
        friend class deque<T,Allocator>;
    private:
        iterator(pointer ptr = nullptr, pointer left = nullptr, pointer right = nullptr);    
    public:
        iterator() = default;
        iterator(const iterator&) = default;      
        iterator(iterator&&) = default;

        iterator& operator=(const iterator&) = default;      
        iterator& operator=(iterator&&) = default;

        iterator operator+(size_type n) const;      
        iterator operator-(size_type n) const;

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);

        reference operator*();
        pointer operator->();

        // reference operator[](size_type pos) const;
};


template <typename T, class Allocator>
class my_deque::deque<T,Allocator>::const_reverse_iterator
{
        friend class deque<T,Allocator>;
    protected:
        pointer m_ptr;        
        pointer m_left;
        pointer m_right;
    private:
        const_reverse_iterator(pointer ptr = nullptr, pointer left = nullptr, pointer right = nullptr);
    public:
        const_reverse_iterator() = default;
        const_reverse_iterator(const const_reverse_iterator&) = default;      
        const_reverse_iterator(const_reverse_iterator&&) = default;

        const_reverse_iterator& operator=(const const_reverse_iterator&) = default;      
        const_reverse_iterator& operator=(const_reverse_iterator&&) = default;

        const_reverse_iterator operator+(size_type n) const;      
        const_reverse_iterator operator-(size_type n) const;

        const_reverse_iterator& operator++();
        const_reverse_iterator operator++(int);
        const_reverse_iterator& operator--();
        const_reverse_iterator operator--(int);

        const_reference operator*() const;
        const_pointer operator->() const;

        // const_reference operator[](size_type pos) const;

        bool operator==(const const_reverse_iterator& other) const;      
        bool operator!=(const const_reverse_iterator& other) const;      
        bool operator<(const const_reverse_iterator& other) const;      
        bool operator<=(const const_reverse_iterator& other) const;      
        bool operator>(const const_reverse_iterator& other) const;      
        bool operator>=(const const_reverse_iterator& other) const;      
};

template <typename T, class Allocator>
class my_deque::deque<T,Allocator>::reverse_iterator : public my_deque::deque<T,Allocator>::const_reverse_iterator
{
        friend class deque<T,Allocator>;
    private:
        reverse_iterator(pointer ptr = nullptr, pointer left = nullptr, pointer right = nullptr);
    public:
        reverse_iterator() = default;
        reverse_iterator(const reverse_iterator&) = default;      
        reverse_iterator(reverse_iterator&&) = default;

        const reverse_iterator& operator=(const reverse_iterator& rhv);      
        const reverse_iterator& operator=(reverse_iterator&& rhv);

        reverse_iterator operator+(size_type n) const;      
        reverse_iterator operator-(size_type n) const;

        reverse_iterator& operator++();
        reverse_iterator operator++(int);
        reverse_iterator& operator--();
        reverse_iterator operator--(int);

        reference operator*();
        pointer operator->();

        // reference operator[](size_type pos) const;
};

#include "deque.hpp"
#endif
