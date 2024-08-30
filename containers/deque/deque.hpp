#include "deque.h"

namespace my_deque
{
    template <typename T, class Allocator>
    deque<T,Allocator>::deque() : m_left(nullptr), m_right(nullptr), m_l_size(0), m_r_size(0), m_l_capacity(0), m_r_capacity(0), m_alloc(){}

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(const Allocator& alloc) : m_left(nullptr), m_right(nullptr), m_l_size(0), m_r_size(0), m_l_capacity(0), m_r_capacity(0), m_alloc(alloc)  {}

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(size_type count, const Allocator& alloc) : m_left(nullptr), m_right(nullptr), m_l_size(0), m_r_size(count), m_l_capacity(0), m_r_capacity(count), m_alloc(alloc) 
    {
        m_right = m_alloc.allocate(m_r_capacity);
        for (size_t i = 0; i < m_r_size; ++i) 
        {
            m_alloc.construct(m_right + i, T());
        }
        rebalance();
    }

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(size_type count, const value_type& value, const Allocator& alloc) : m_left(nullptr), m_right(nullptr), m_l_size(0), m_r_size(count), m_l_capacity(0), m_r_capacity(count), m_alloc(alloc) 
    {
        m_right = m_alloc.allocate(m_r_capacity);
        for (size_t i = 0; i < m_r_size; ++i) 
        {
            m_alloc.construct(m_right + i, value);
        }
        rebalance();
    }

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(const deque& other) : deque(other, Allocator()){}

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(const deque& other, const Allocator& alloc) : m_left(nullptr), m_right(nullptr), m_l_size(other.m_l_size), m_r_size(other.m_r_size), m_l_capacity(other.m_l_capacity), m_r_capacity(other.m_r_capacity), m_alloc(alloc) 
    {
        m_left = m_alloc.allocate(m_l_capacity);
        for (size_t i = 0; i < m_l_size; ++i) 
        {
            m_alloc.construct(m_left + i, other.m_left[i]);
        }

        m_right = m_alloc.allocate(m_r_capacity);
        for (size_t i = 0; i < m_r_size; ++i) 
        {
            m_alloc.construct(m_right + i, other.m_right[i]);
        }
    }

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(deque&& other) noexcept: deque(other, Allocator()){}

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(deque&& other, const Allocator& alloc) noexcept: m_left(nullptr), m_right(nullptr), m_l_size(std::move(other.m_l_size)), m_r_size(std::move(other.m_r_size)), m_l_capacity(std::move(other.m_l_capacity)), m_r_capacity(std::move(other.m_r_capacity)), m_alloc(alloc)
    {
        m_left = m_alloc.allocate(m_l_capacity);
        for(size_t i = 0; i < m_l_size; ++i) 
        {
            m_alloc.construct(m_left + i, std::move(other.m_left[i]));
        }

        m_right = m_alloc.allocate(m_r_capacity);
        for(size_t i = 0; i < m_r_size; ++i) 
        {
            m_alloc.construct(m_right + i, std::move(other.m_right[i]));
        }
        other.m_left = nullptr;
        other.m_right = nullptr;
    }

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(std::initializer_list<T> init, const Allocator& alloc) : m_left(nullptr), m_right(nullptr), m_l_size(0), m_r_size(init.size()), m_l_capacity(0), m_r_capacity(init.size()), m_alloc(alloc)
    {
        size_type i = 0;
        m_right = m_alloc.allocate(m_r_capacity);
        for (const auto& elem : init) 
        {
            m_alloc.construct(m_right + i, elem);
            ++i;
        }
        rebalance();
    }

    template <typename T, class Allocator>
    template<typename InputIt>
    deque<T,Allocator>::deque(InputIt first, InputIt last) : m_left(nullptr), m_right(nullptr), m_l_size(0), m_r_size(0), m_l_capacity(0), m_r_capacity(0), m_alloc()
    {
        while(first != last)
        {
            std::cout << *first;
            push_back(*first);
            ++first;
        }
        std::cout << "asdasd";
    }

    template <typename T, class Allocator>
    deque<T,Allocator>::~deque()
    {
        clear();
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::allocator_type  deque<T,Allocator>::get_allocator() const
    {
        return m_alloc;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::deque& deque<T,Allocator>::operator=(const deque& other)
    {
        if(this != &other)
        {
            deque temp(other);

            clear();

            m_left = temp.m_left;
            m_right = temp.m_right;
            m_l_size = temp.m_l_size;
            m_r_size = temp.m_r_size;
            m_l_capacity = temp.m_l_capacity;
            m_r_capacity = temp.m_r_capacity;
            m_alloc = temp.m_alloc;
        }
        return *this;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::deque& deque<T,Allocator>::operator=(deque&& other) noexcept
    {
        if(this != &other)
        {
            clear();

            m_left = std::move(other.m_left);
            m_right = std::move(other.m_right);
            m_l_size = std::move(other.m_l_size);
            m_r_size = std::move(other.m_r_size);
            m_l_capacity = std::move(other.m_l_capacity);
            m_alloc = std::move(other.m_alloc);
        }
        return *this;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::deque& deque<T,Allocator>::operator=(std::initializer_list<value_type> init)
    {
        clear();

        m_r_capacity = init.size();
        m_r_size = 0;
        m_right = m_alloc.allocate(m_r_capacity);
        for(const auto& elem : init)
        {
            push_back(elem);
        }
        return *this;
        
    }

    template<typename T, class Allocator>
    void deque<T,Allocator>::assign(size_type count, const value_type& val)
    {
        clear();

        m_r_capacity = count;
        m_r_size = 0;
        m_right = m_alloc.allocate(m_r_capacity);

        for(size_type i = 0; i < count; ++i)
        {
            push_back(val);
        }
    }

    template<typename T, class Allocator>
    void deque<T,Allocator>::assign(std::initializer_list<value_type> init)
    {
        clear();

        m_r_capacity = init.size();
        m_right = m_alloc.allocate(m_r_capacity);
        m_r_size = 0;
     
        for(const auto& elem : init)
        {   
            push_back(elem);
        }
    }

    template<typename T, class Allocator>
    template<typename InputIt>
    void deque<T,Allocator>::assign(InputIt first, InputIt last)
    {
        clear();

        while(first != last)
        {
            push_back(*first);
            ++first;
        }
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::reference deque<T,Allocator>::operator[](size_type pos)
    {
        return m_l_size > pos ? m_left[m_l_size - pos - 1] : m_right[pos - m_l_size]; 
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::const_reference deque<T,Allocator>::operator[](size_type pos) const
    {
        return m_l_size > pos ? m_left[m_l_size - pos - 1] : m_right[pos - m_l_size]; 
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::reference deque<T,Allocator>::at(size_type pos)
    {
        return const_cast<reference>(static_cast<const deque&>(*this)[pos]);
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::const_reference deque<T,Allocator>::at(size_type pos) const
    {
        if(pos >= m_l_size + m_r_size)
        {
            throw std::out_of_range("Out of range");
        }
        return m_l_size > pos ? m_left[m_l_size - pos - 1] : m_right[pos - m_l_size]; 
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::reference deque<T,Allocator>::front()
    {
        return const_cast<reference>(static_cast<const deque&>(*this).front());
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::reference deque<T,Allocator>::back()
    {
        return const_cast<reference>(static_cast<const deque&>(*this).back());
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::const_reference deque<T,Allocator>::front() const
    {
        if (m_l_size > 0) 
        {
            return m_left[m_l_size - 1];
        } 
        
        if (m_r_size > 0) 
        {
            return m_right[0];
        }
        throw std::out_of_range("Deque is empty");
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::const_reference deque<T,Allocator>::back() const
    {
        if (m_r_size > 0) 
        {
            return m_right[m_r_size - 1];
        } 
        
        if (m_l_size > 0) 
        {
            return m_left[0];
        }
        throw std::out_of_range("Deque is empty");
    }


    template <typename T, class Allocator>
    typename deque<T,Allocator>::size_type deque<T,Allocator>::size() const
    {
        return m_l_size + m_r_size;
    }

    template <typename T, class Allocator>
    bool deque<T,Allocator>::empty() const
    {
        return m_l_size == 0 && m_r_size == 0 ? true : false;
    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::clear()
    {
        if(m_left)
        {
            for(size_t i = 0; i < m_l_size; ++i)
            {
                m_alloc.destroy(&m_left[i]);
            }
        }

        if(m_r_size)
        {
            for(size_t i = 0; i < m_r_size; ++i)
            {
                m_alloc.destroy(&m_right[i]);
            }
        }
        m_alloc.deallocate(m_left, m_l_capacity);
        m_alloc.deallocate(m_right, m_r_capacity);

        m_left = nullptr;
        m_right = nullptr;
        m_l_size = 0;
        m_r_size = 0;
        m_l_capacity = 0;
        m_r_capacity = 0;

    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::iterator deque<T,Allocator>::erase(const_iterator pos)
    {
        if (pos.m_ptr >= m_left && pos.m_ptr < m_left + m_l_size) 
        {
            size_type offset = pos.m_ptr - m_left;

            if (m_l_size == 1) 
            {
                m_alloc.destroy(&m_left[0]);
                --m_l_size;
            } 
            else 
            {
                for (size_type i = offset; i < m_l_size - 1; ++i) 
                {
                    m_left[i] = m_left[i + 1]; 
                }
                m_alloc.destroy(&m_left[m_l_size - 1]);
                --m_l_size;
            }

            if(pos.m_ptr == m_left)
            {
                return iterator(m_right);
            }
            return iterator(m_left + offset - 1 ); 
        } 
        else if (pos.m_ptr >= m_right && pos.m_ptr < m_right + m_r_size) 
        {
            size_type offset = pos.m_ptr - m_right;

            if (m_r_size == 1) 
            {
                m_alloc.destroy(&m_right[0]);
                --m_r_size;
            } 
            else 
            {
                for (size_type i = offset; i < m_r_size - 1; ++i) 
                {
                    m_right[i] = m_right[i + 1]; 
                }
                m_alloc.destroy(&m_right[m_r_size - 1]);
                --m_r_size; 
            }
            return iterator(m_right + offset + 1); 
        }

        throw std::out_of_range("Invalid iterator"); 
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::iterator deque<T,Allocator>::erase(const_iterator first, const_iterator last)
    {
        while (first != last) 
        {
            std::cout << *first << " ";
            first = erase(first);

        }

        rebalance(); // Ensure the deque is balanced after removals

        return iterator(first.m_ptr); // Return the iterator to the position after the last erased element
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::iterator deque<T,Allocator>::insert(const_iterator pos, const value_type& value)
    {
        if(pos.m_ptr >= m_left && pos.m_ptr < m_left + m_l_size)
        {
            if(m_l_size == m_l_capacity)
            {
                reserve(m_l_capacity * 2);
            }
            value_type offset = pos.m_ptr - m_left;
            m_alloc.construct(m_left + m_l_size, 0);
            value_type temp = m_l_size;
            while(temp != offset)
            {
                m_left[temp] = m_left[temp - 1];
                --temp;
            }
            m_left[offset] = value;
            ++m_l_size;
            return iterator(m_left + (pos.m_ptr - m_left));
        }
        else if(pos.m_ptr >= m_right && pos.m_ptr < m_right + m_r_size)
        {
            if(m_r_size == m_r_capacity)
            {
                reserve(m_r_capacity * 2);
            }
            value_type offset = pos.m_ptr - m_right;
            m_alloc.construct(m_right + m_r_size, 0);
            value_type temp = m_r_size;
            while(temp != offset)
            {
                m_right[temp] = m_right[temp - 1];
                --temp;
            }
            m_right[offset] = value;
            ++m_r_size;
            return iterator(m_right + (pos.m_ptr - m_right));
        }
        throw std::out_of_range("Invalid iterator");
        
    }
    template <typename T, class Allocator>
    void deque<T,Allocator>::push_back(const value_type& value)
    {
        if(balance_factor())
        {
            rebalance();
        }
        if(m_r_size == m_r_capacity)
        {
            reserve(m_r_capacity == 0 ? 1 : m_r_capacity * 2, false);
        }
        m_alloc.construct(m_right + m_r_size, value);
        ++m_r_size;
    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::push_back(value_type&& value)
    {
        if(balance_factor())
        {
            rebalance();
        }
        if(m_r_size == m_r_capacity)
        {
            reserve(m_r_capacity == 0 ? 1 : m_r_capacity * 2, false);
        }
        m_alloc.construct(m_right + m_r_size, std::move(value));
        ++m_r_size;
    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::push_front(const value_type& value)
    {
        if(balance_factor())
        {
            rebalance();
        }
        if(m_l_size == m_l_capacity)
        {
            reserve(m_l_capacity == 0 ? 1 : m_l_capacity * 2, true);
        }
        m_alloc.construct(m_left + m_l_size, value);
        ++m_l_size;
    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::push_front(value_type&& value)
    {
        if(balance_factor())
        {
            rebalance();
        }
        if(m_l_size == m_l_capacity)
        {
            reserve(m_l_capacity == 0 ? 1 : m_l_capacity * 2, true);
        }
        m_alloc.construct(m_left + m_l_size, value);
        ++m_l_size;
    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::pop_front()
    {
        if(m_l_size == 0)
        {
            return;
        }
        if(m_l_size > 0)
        {
            m_left[m_l_size - 1].~value_type();
            --m_l_size;
        }
        
        if(balance_factor())
        {
            rebalance();
        }

    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::pop_back()
    {
        if(m_r_size == 0)
        {
            return;
        }
        if(m_r_size > 0)
        {
            m_right[m_r_size - 1].~value_type();
            --m_r_size;
        }
        
        if(balance_factor())
        {
            rebalance();
        }
    }


    template <typename T, class Allocator>
    void deque<T,Allocator>::reserve(size_type newCapacity, bool left)
    {
        if(left)
        {
            if(newCapacity > m_l_capacity)
            {
                pointer new_left = m_alloc.allocate(newCapacity);

                for(size_type i = 0; i < m_l_size; ++i)
                {
                    m_alloc.construct(new_left + i, std::move(m_left[i]));
                    m_alloc.destroy(&m_left[i]);

                }
                m_alloc.deallocate(m_left, m_l_capacity);

                m_left = new_left;
                m_l_capacity = newCapacity; 
            }
        }
        else
        {
           if(newCapacity > m_r_capacity)
           {
                pointer new_right = m_alloc.allocate(newCapacity);

                for(size_type i = 0; i < m_r_size; ++i)
                {
                    m_alloc.construct(new_right + i, std::move(m_right[i]));
                    m_alloc.destroy(&m_right[i]);
                } 

                m_alloc.deallocate(m_right, m_r_capacity);

                m_right = new_right;
                m_r_capacity = newCapacity;
           } 
        }
    }

    template<typename T, class Allocator>
    void deque<T,Allocator>::resize(size_type count)
    {
        if(count == 0)
        {
            return;
        }
        else if(count > size())
        {
            resize(count,0);
        }
        else
        {
            for(size_type i = size(); i > count; --i)
            {
                pop_back();
            }
        }
    }

    
    template<typename T, class Allocator>
    void deque<T,Allocator>::resize(size_type count,const value_type& val)
    {
        if(count <= size())
        {
            return;
        }
        for(size_type i = size(); i < count; ++i)
        {
            push_back(val);
        }
    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::shrink_to_fit() 
    {
       
        if (m_l_size == m_l_capacity && m_r_size == m_r_capacity)
        {
            return;
        }
        size_t left_size = m_l_size;
        size_t right_size = m_r_size;
        
        
        size_t new_l_capacity = left_size;
        size_t new_r_capacity = right_size;
        
        pointer new_left = m_alloc.allocate(new_l_capacity);
        pointer new_right = m_alloc.allocate(new_r_capacity);
        
        for(size_t i = 0; i < left_size; ++i) 
        {
            m_alloc.construct(new_left + i, std::move(m_left[i]));
            m_left[i].~T(); 
        }
        
        for(size_t i = 0; i < right_size; ++i) 
        {
            m_alloc.construct(new_right + i, std::move(m_right[i]));
            m_right[i].~T(); 
        }
        
        if(m_left) 
        {
            m_alloc.deallocate(m_left, m_l_capacity);
        }
        if(m_right)
        {
            m_alloc.deallocate(m_right, m_r_capacity);
        } 
        
        m_left = new_left;
        m_right = new_right;
        m_l_capacity = new_l_capacity;
        m_r_capacity = new_r_capacity;
        
        m_l_size = left_size;
        m_r_size = right_size;
    }

    template <typename T, class Allocator>
    template<class ...Args>
    void deque<T,Allocator>::emplace_back(Args&&... args)
    {
        if(m_r_size == m_r_capacity) 
        {   
            reserve(m_r_capacity == 0 ? 1 : m_r_capacity * 2, false);
        }

        m_alloc.construct(m_right + m_r_size, std::forward<Args>(args)...);
        ++m_r_size;

        if(balance_factor())
        {
            rebalance();
        }
    }


    template<typename T, class Allocator>
    void deque<T,Allocator>::swap(deque& other) noexcept
    {
        std::swap(m_left, other.m_left);
        std::swap(m_right, other.m_right);
        std::swap(m_l_size, other.m_l_size);
        std::swap(m_r_size, other.m_r_size);
        std::swap(m_l_capacity, other.m_l_capacity);
        std::swap(m_r_capacity, other.m_r_capacity);
        std::swap(m_alloc, other.m_alloc);
    }

// ======================================================== const_terator ===================================================
    template<typename T, class Allocator>
    deque<T,Allocator>::const_iterator::const_iterator(pointer ptr, pointer left, pointer right) : m_ptr{ptr}, m_left{left}, m_right{right}{}

    // template<typename T, class Allocator>
    // typename deque<T, Allocator>::const_iterator deque<T, Allocator>::const_iterator::operator+(size_type n) const
    // {
    //     if(m_ptr - n >= m_left)
    //     {
    //         return const_iterator(m_ptr - n, m_left, m_right);
    //     }
    //     else
    //     {
    //         size_type offset = m_left - m_ptr - n;
    //         return const_iterator(m_right + offset, m_left, m_right);
    //     }
    // }

    
    // template<typename T, class Allocator>
    // typename deque<T,Allocator>::const_iterator deque<T,Allocator>::const_iterator::operator-(size_type n) const
    // {
    //     const pointer new_ptr = m_ptr - n;

    //     if(new_ptr >= m_left)
    //     {
    //         return const_iterator(new_ptr, m_left, m_right);
    //     }
    //     else
    //     {
    //         size_type offset = m_left + m_l_size - new_ptr;
    //         return const_iterator(m_right - (n - offset), m_left, m_right);
    //     }
    // }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::const_iterator& deque<T,Allocator>::const_iterator::operator++()
    {    
        if(m_ptr >= m_left)
        {
            if(m_ptr == m_left)
            {
                m_ptr = m_right;
                return *this;
            }
            --m_ptr;
        }
        else
        {
            ++m_ptr;
        }
        return *this;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::const_iterator deque<T,Allocator>::const_iterator::operator++(int)
    {
        const_iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::const_iterator& deque<T,Allocator>::const_iterator::operator--()
    {
        if(m_ptr >= m_right && !(m_ptr >= m_left))
        {
            if(m_ptr == m_right)
            {
                m_ptr = m_left;
                return *this;
            }
            --m_ptr;
        }
        else
        {
            ++m_ptr;
        }
        return *this;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::const_iterator deque<T,Allocator>::const_iterator::operator--(int)
    {
        const_iterator tmp = *this;
        --(*this);
        return tmp;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::const_reference deque<T,Allocator>::const_iterator::operator*() const
    {
        return *m_ptr;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::const_pointer deque<T,Allocator>::const_iterator::operator->() const
    {
        return m_ptr;
    }

    // template<typename T, class Allocator>
    // typename deque<T,Allocator>::const_reference deque<T,Allocator>::const_iterator::operator[](size_type pos) const
    // {   
    //     return m_l_size > pos ? m_left[m_l_size - pos - 1] : m_right[pos - m_l_size]; 
    // }


    template<typename T, class Allocator>
    typename deque<T,Allocator>::const_iterator deque<T,Allocator>::begin() const 
    {   
        return const_iterator(m_left + m_l_size - 1, m_left, m_right);
    }


    template<typename T, class Allocator>
    typename deque<T, Allocator>::const_iterator deque<T, Allocator>::end() const 
    {
        return const_iterator(m_right + m_r_size, m_left, m_right);
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::const_iterator deque<T,Allocator>::cbegin() const noexcept
    {
        return const_iterator(m_left + m_l_size - 1, m_left, m_right);
    }

    template<typename T, class Allocator>
    typename deque<T, Allocator>::const_iterator deque<T, Allocator>::cend() const noexcept
    {
        return const_iterator(m_right + m_r_size, m_left, m_right);
    }

    template<typename T, class Allocator>
    bool deque<T, Allocator>::const_iterator::operator==(const const_iterator& other) const 
    {
        return m_ptr == other.m_ptr;
    }

    template<typename T, class Allocator>
    bool deque<T, Allocator>::const_iterator::operator!=(const const_iterator& other) const 
    {
        return m_ptr != other.m_ptr;
    }

    template<typename T, class Allocator>
    bool deque<T, Allocator>::const_iterator::operator>(const const_iterator& other) const 
    {
        return m_ptr > other.m_ptr;
    }

    template<typename T, class Allocator>
    bool deque<T, Allocator>::const_iterator::operator<(const const_iterator& other) const 
    {
        return m_ptr < other.m_ptr;
    }

    template<typename T, class Allocator>
    bool deque<T, Allocator>::const_iterator::operator>=(const const_iterator& other) const 
    {
        return m_ptr >= other.m_ptr;
    }

    template<typename T, class Allocator>
    bool deque<T, Allocator>::const_iterator::operator<=(const const_iterator& other) const 
    {
        return m_ptr <= other.m_ptr;
    }


// // ======================================================== iterator ========================================================
    template<typename T, class Allocator>
    deque<T,Allocator>::iterator::iterator(pointer ptr, pointer left, pointer right) : const_iterator(ptr,left,right){}

    // template<typename T, class Allocator>
    // typename deque<T, Allocator>::iterator deque<T, Allocator>::iterator::operator+(size_type n) const
    // {
    //     if(m_ptr - n >= m_left)
    //     {
    //         return iterator(m_ptr - n, m_left, m_right);
    //     }
    //     else
    //     {
    //         size_type offset = m_left - m_ptr - n;
    //         return iterator(m_right + offset, m_left, m_right);
    //     }
    // }

    
    // template<typename T, class Allocator>
    // typename deque<T,Allocator>::iterator deque<T,Allocator>::iterator::operator-(size_type n) const
    // {
    //     pointer new_ptr = m_ptr - n;

    //     if(new_ptr >= m_left)
    //     {
    //         return iterator(new_ptr, m_left, m_right);
    //     }
    //     else
    //     {
    //         size_type offset = m_left + m_l_size - new_ptr;
    //         return iterator(m_right - (n - offset), m_left, m_right);
    //     }
    // }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::iterator& deque<T,Allocator>::iterator::operator++()
    {      
        if(this->m_ptr >= this->m_left)
        {
            if(this->m_ptr == this->m_left)
            {
                this->m_ptr = this->m_right;
                return *this;
            }
            --this->m_ptr;
        }
        else
        {
            ++this->m_ptr;
        }
        return *this;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::iterator deque<T,Allocator>::iterator::operator++(int)
    {
        iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::iterator& deque<T,Allocator>::iterator::operator--()
    {
        if(this->m_ptr >= this->m_right && !(this->m_ptr >= this->m_left))
        {
            if(this->m_ptr == this->m_right)
            {
                this->m_ptr = this->m_left;
                return *this;
            }
            --this->m_ptr;
        }
        else
        {
            ++this->m_ptr;
        }
        return *this;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::iterator deque<T,Allocator>::iterator::operator--(int)
    {
        iterator tmp = *this;
        --(*this);
        return tmp;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::reference deque<T,Allocator>::iterator::operator*() 
    {
        return *this->m_ptr;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::pointer deque<T,Allocator>::iterator::operator->() 
    {
        return this->m_ptr;
    }

    // template<typename T, class Allocator>
    // typename deque<T,Allocator>::const_reference deque<T,Allocator>::const_iterator::operator[](size_type pos) const
    // {   
    //     return m_l_size > pos ? m_left[m_l_size - pos - 1] : m_right[pos - m_l_size]; 
    // }


    template<typename T, class Allocator>
    typename deque<T,Allocator>::iterator deque<T,Allocator>::begin()  
    {   
        return iterator(m_left + m_l_size - 1, m_left, m_right);
    }


    template<typename T, class Allocator>
    typename deque<T, Allocator>::iterator deque<T, Allocator>::end()  
    {
        return iterator(m_right + m_r_size, m_left, m_right);
    }
// ======================================================== reverse_iterator ================================================
// ======================================================== const_reverse_iterator ==========================================

    template<typename T, class Allocator>
    bool deque<T,Allocator>::balance_factor() const
    {
        if (m_l_size == 0 || m_r_size == 0) 
        {
            return !(m_l_size == m_r_size); 
        }
        bf_type left = m_l_size == 0 ? 1 : static_cast<bf_type>(m_l_size);
        bf_type right = m_r_size == 0 ? 1 : static_cast<bf_type>(m_r_size);
        return left / right >= 1.3 || right / left >= 1.3 ? true : false;
    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::rebalance()
    {   
        const size_type size = m_l_size + m_r_size;
        size_type reb_index = 0;
        value_type reb_arr[size];
        if(m_left)
        {
            for(size_type i = m_l_size - 1; i != -1; --i)
            {
                reb_arr[reb_index++] = std::move(m_left[i]);
                m_alloc.destroy(&m_left[i]);
            }
        }
        if(m_right)
        {
            for(size_type i = 0; i < m_r_size; ++i)
            {
                reb_arr[reb_index++] = std::move(m_right[i]);
                m_alloc.destroy(&m_right[i]);            
            }
        }

        m_l_size = 0;
        m_r_size = 0;
        if(m_l_capacity < size / 2)
        {    
            reserve(size);
        }
        if(m_r_capacity < size / 2)
        {    
            reserve(size, false);
        }

        for(size_type i = (size / 2) - 1; i != -1 ; --i)
        {
           m_alloc.construct(m_left + m_l_size, reb_arr[i]);
           ++m_l_size;     
        }

        for(size_type i = (size / 2); i < size; ++i)
        {
           m_alloc.construct(m_right + m_r_size, reb_arr[i]);
           ++m_r_size;     
        }
    }
}
