#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <initializer_list>
#include <memory>

namespace my_deque
{
    template <class T,  class Allocator = std::allocator<T>>
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

        public:
            class iterator;
            class const_iterator;
            // class reverse_iterator;
            // class const_reverse_iterator;

        public:
            deque();
            explicit deque(const Allocator& aloc);
            explicit deque(size_type count, const Allocator& alloc = Allocator());
            deque (size_type count, const value_type& val, const Allocator& alloc = Allocator());
            deque(const deque& other);
            deque(const deque& other, const Allocator& alloc);
            deque(deque&& other) noexcept;
            deque(deque&& other, const Allocator& alloc) noexcept;
            deque (std::initializer_list<T> init, const Allocator& alloc = Allocator());
            // template<typename InputIt>
            // deque(InputIt first, InputIt last);
            ~deque();
            allocator_type get_allocator() const;

        public:
            deque& operator=(const deque& other);
            deque& operator=(deque&& other) noexcept;
            deque& operator=(std::initializer_list<value_type> init);
            
            void assign(size_type count, const value_type& val);
            // template<class InputIt>
            // void assign(InputIt first, InputIt last);
            void assign(std::initializer_list<value_type> init); 

            // Allocator ----------------------

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

            // reverse_iterator rbegin();
            // const_reverse_iterator rbegin() const;
            // const_reverse_iterator crbegin() const noexcept;

            // reverse_iterator rend();
            // const_reverse_iterator rend() const;
            // const_reverse_iterator crend() const noexcept;

        public:
            bool empty() const;
            size_type size() const;
            void shrink_to_fit();

        public:
            void clear();

            // iterator insert(const_iterator pos, const value_type& value);
            // iterator insert(const_iterator pos, value_type&& value);
            // iterator insert(const_iterator pos,size_type count, const value_type& value);
            // template<class InputIt>
            // iterator insert(const_iterator pos, InputIt first, InputIt last);
            // iterator insert(const_iterator pos, std::initializer_list<T> ilist);

            // template< class... Args >
            // iterator emplace(const_iterator pos, Args&&... args);

            // iterator erase(iterator pos);
            // iterator erase(const_iterator pos);
            // iterator erase(iterator first, iterator last);
            // iterator erase(const_iterator first, const_iterator last);

            void push_back(const value_type& value);
            void push_back(value_type&& value);
            void push_front(const value_type& value);
            void push_front(value_type&& value);
            void pop_back();
            void pop_front();

            template<class... Args>
            void emplace_back(Args&&... args);
            // template<class... Args>
            // reference emplace_back(Args&&... args);
            // template<class... Args>
            // void emplace_front(Args&&... args);
            // template<class... Args>
            // reference emplace_front(Args&&... args);

            void resize(size_type count);
            void resize(size_type count, const value_type& value);

            void swap(deque& other) noexcept;

        private:
            void reserve(size_type newCapacity, bool left = true);
            value_type *m_left;
            value_type *m_right;
            size_type m_l_size;
            size_type m_r_size;
            size_type m_l_capacity;
            size_type m_r_capacity;
            size_type m_l_free;
            size_type m_r_free;
            Allocator m_alloc;
    };
}
//template<class T, class Alloc>
//synth-three-way-result<T> operator<=>(const std::deque<T, Alloc>& lhs, const std::deque<T, Alloc>& rhs);


template <typename T, class Allocator>
class my_deque::deque<T,Allocator>::const_iterator
{
        friend class deque<T,Allocator>;
    protected:
        pointer m_ptr;        
        pointer m_left;       
        pointer m_right;      
        size_type m_l_size; 
        size_type m_r_size; 
    private:
        const_iterator(pointer ptr = nullptr, pointer left = nullptr, pointer right = nullptr, size_type l_size = 0, size_type r_size = 0);
    public:
        const_iterator() = default;
        const_iterator(const const_iterator&) = default;      
        const_iterator(const_iterator&&) = default;

        const_iterator& operator=(const const_iterator&) = default;      
        const_iterator& operator=(const_iterator&&) = default;

        const_iterator operator+(size_type n) const;      
        // const_iterator operator-(size_type n) const;

        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);

        const_reference operator*() const;
        const_pointer operator->() const;

        const_reference operator[](size_type pos) const;

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
        iterator(pointer ptr = nullptr, pointer left = nullptr, pointer right = nullptr, size_type l_size = 0, size_type r_size = 0);
    public:
        iterator() = default;
        iterator(const iterator&) = default;      
        iterator(iterator&&) = default;

        iterator& operator=(const iterator&) = default;      
        iterator& operator=(iterator&&) = default;

        iterator operator+(size_type n) const;      
        // iterator operator-(size_type n) const;

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);

        reference operator*();
        pointer operator->();

        reference operator[](size_type pos) const;
};


// template <typename T, class Allocator>
// class my_deque::deque<T,Allocator>::const_reverse_iterator
// {
//         friend class deque<T,Allocator>;
//     protected:
//         pointer m_ptr;
//     private:
//         const_reverse_iterator(pointer ptr);
//     public:
//         const_reverse_iterator() = default;
//         const_reverse_iterator(const const_reverse_iterator&) = default;      
//         const_reverse_iterator(const_reverse_iterator&&) = default;

//         const_reverse_iterator& operator=(const const_reverse_iterator&) = default;      
//         const_reverse_iterator& operator=(const_reverse_iterator&&) = default;

//         const_reverse_iterator operator+(size_type n) const;      
//         const_reverse_iterator operator-(size_type n) const;

//         const_reverse_iterator& operator++();
//         const_reverse_iterator operator++(int);
//         const_reverse_iterator& operator--();
//         const_reverse_iterator operator--(int);

//         const_reference operator*() const;
//         const_pointer operator->() const;

//         const_reference operator[](size_type pos) const;

//         bool operator==(const const_reverse_iterator& other) const;      
//         bool operator!=(const const_reverse_iterator& other) const;      
//         bool operator<(const const_reverse_iterator& other) const;      
//         bool operator<=(const const_reverse_iterator& other) const;      
//         bool operator>(const const_reverse_iterator& other) const;      
//         bool operator>=(const const_reverse_iterator& other) const;      
// };

// template <typename T, class Allocator>
// class my_deque::deque<T,Allocator>::reverse_iterator : public my_deque::deque<T,Allocator>::const_reverse_iterator
// {
//         friend class deque<T,Allocator>;
//     private:
//         reverse_iterator(pointer ptr);
//     public:
//         reverse_iterator() = default;
//         reverse_iterator(const reverse_iterator&) = default;      
//         reverse_iterator(reverse_iterator&&) = default;

//         const reverse_iterator& operator=(const reverse_iterator& rhv);      
//         const reverse_iterator& operator=(reverse_iterator&& rhv);

//         reverse_iterator operator+(size_type n) const;      
//         reverse_iterator operator-(size_type n) const;

//         reverse_iterator& operator++();
//         reverse_iterator operator++(int);
//         reverse_iterator& operator--();
//         reverse_iterator operator--(int);

//         reference operator*();
//         pointer operator->();

//         reference operator[](size_type pos) const;
// };

#include "deque.hpp"
#endif