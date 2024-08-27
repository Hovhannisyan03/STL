#include "deque.h"

namespace my_deque
{
    template <typename T, class Allocator>
    deque<T,Allocator>::deque() : m_left(nullptr), m_right(nullptr), m_l_size(0), m_r_size(0), m_l_capacity(0), m_r_capacity(0), m_l_free(0), m_r_free(0), m_alloc(){}

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(const Allocator& alloc) : m_left(nullptr), m_right(nullptr), m_l_size(0), m_r_size(0), m_l_capacity(0), m_r_capacity(0), m_l_free(0), m_r_free(0), m_alloc(alloc)  {}


    template <typename T, class Allocator>
    deque<T,Allocator>::deque(size_type count, const Allocator& alloc) : m_left(nullptr), m_right(nullptr), m_l_size(0), m_r_size(count), m_l_capacity(0), m_r_capacity(count), m_l_free(0), m_r_free(0), m_alloc(alloc) 
    {
        m_right = m_alloc.allocate(m_r_capacity);
        for (size_t i = 0; i < m_r_size; ++i) 
        {
            m_alloc.construct(m_right + i, T());
        }
    }

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(size_type count, const value_type& value, const Allocator& alloc) : m_left(nullptr), m_right(nullptr), m_l_size(0), m_r_size(count), m_l_capacity(0), m_r_capacity(count), m_l_free(0), m_r_free(0), m_alloc(alloc) 
    {
        m_right = m_alloc.allocate(m_r_capacity);
        for (size_t i = m_r_free; i < m_r_size; ++i) 
        {
            m_alloc.construct(m_right + (i - m_r_free), value);
        }
    }

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(const deque& other) : deque(other, Allocator()){}

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(const deque& other, const Allocator& alloc) : m_left(nullptr), m_right(nullptr), m_l_size(other.m_l_size), m_r_size(other.m_r_size), m_l_capacity(other.m_l_capacity), m_r_capacity(other.m_r_capacity), m_l_free(0), m_r_free(0), m_alloc(alloc) 
    {
        m_left = m_alloc.allocate(m_l_capacity);
        for (size_t i = m_l_free; i < m_l_size; ++i) 
        {
            m_alloc.construct(m_left + (i - m_l_free), other.m_left[i]);
        }

        m_right = m_alloc.allocate(m_r_capacity);
        for (size_t i = m_r_free; i < m_r_size; ++i) 
        {
            m_alloc.construct(m_right + (i - m_r_free), other.m_right[i]);
        }
    }

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(deque&& other) noexcept: deque(other, Allocator()){}

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(deque&& other, const Allocator& alloc) noexcept: m_left(nullptr), m_right(nullptr), m_l_size(std::move(other.m_l_size)), m_r_size(std::move(other.m_r_size)), m_l_capacity(std::move(other.m_l_capacity)), m_r_capacity(std::move(other.m_r_capacity)), m_l_free(0), m_r_free(0), m_alloc(alloc)
    {
        m_left = m_alloc.allocate(m_l_capacity);
        for(size_t i = m_l_free; i < m_l_size; ++i) 
        {
            m_alloc.construct(m_left + (i - m_l_free), std::move(other.m_left[i]));
        }

        m_right = m_alloc.allocate(m_r_capacity);
        for(size_t i = m_r_free; i < m_r_size; ++i) 
        {
            m_alloc.construct(m_right + (i - m_r_free), std::move(other.m_right[i]));
        }
        other.m_left = nullptr;
        other.m_right = nullptr;
        other.m_l_free = 0;
        other.m_r_free = 0;
    }

    template <typename T, class Allocator>
    deque<T,Allocator>::deque(std::initializer_list<T> init, const Allocator& alloc) : m_left(nullptr), m_right(nullptr), m_l_size(0), m_r_size(init.size()), m_l_capacity(0), m_r_capacity(init.size()), m_l_free(0), m_r_free(0), m_alloc(alloc)
    {
        size_type i = 0;
        m_right = m_alloc.allocate(m_r_capacity);
        for (auto elem : init) 
        {
            m_alloc.construct(m_right + i, elem);
            ++i;
        }
    }
    
    template <typename T, class Allocator>
    deque<T,Allocator>::~deque()
    {
        clear();
        if(m_left) 
        {
            m_alloc.deallocate(m_left, m_l_capacity);
        }
        if (m_right) 
        {
            m_alloc.deallocate(m_right, m_r_capacity);
        }

        m_left = nullptr;
        m_right = nullptr;
        m_l_capacity = 0;
        m_r_capacity = 0;
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

            for(size_t i = m_l_free; i < m_l_size; ++i) 
            {
                m_left[i].~T();
            }
            for(size_t i = m_r_free; i < m_r_size; ++i) 
            {
                m_right[i].~T();
            }

            m_alloc.deallocate(m_left, m_l_capacity);
            m_alloc.deallocate(m_right, m_r_capacity);

            std::swap(m_left, temp.m_left);
            std::swap(m_right, temp.m_right);
            std::swap(m_l_size, temp.m_l_size);
            std::swap(m_r_size, temp.m_r_size);
            std::swap(m_l_capacity, temp.m_l_capacity);
            std::swap(m_r_capacity, temp.m_r_capacity);
            std::swap(m_l_free, temp.m_l_free);
            std::swap(m_r_free, temp.m_r_free);
            std::swap(m_alloc, temp.m_alloc);
        }
        return *this;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::deque& deque<T,Allocator>::operator=(deque&& other) noexcept
    {
        if(this != &other)
        {
            for (size_t i = m_l_free; i < m_l_size; ++i) 
            {
                m_left[i].~T();
            }
            for (size_t i = m_r_free; i < m_r_size; ++i) 
            {
                m_right[i].~T();
            }

            m_alloc.deallocate(m_left, m_l_capacity);
            m_alloc.deallocate(m_right, m_r_capacity);

            m_left = std::move(other.m_left);
            m_right = std::move(other.m_right);
            m_l_size = std::move(other.m_l_size);
            m_r_size = std::move(other.m_r_size);
            m_l_capacity = std::move(other.m_l_capacity);
            m_l_free = std::move(other.m_l_free);
            m_r_free = std::move(other.m_r_free);
            m_alloc = std::move(other.m_alloc);

            other.m_left = nullptr;
            other.m_right = nullptr;
            other.m_l_size = 0;
            other.m_r_size = 0;
            other.m_l_capacity = 0;
            other.m_l_free = 0;
            other.m_r_free = 0;
            other.m_r_capacity = 0;
        }
        return *this;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::deque& deque<T,Allocator>::operator=(std::initializer_list<value_type> init)
    {
        for (size_t i = m_l_free; i < m_l_size; ++i) 
        {
            m_left[i].~T();
        }
        for (size_t i = m_l_free; i < m_r_size; ++i) 
        {
            m_right[i].~T();
        }

        m_alloc.deallocate(m_left, m_l_capacity);
        m_alloc.deallocate(m_right, m_r_capacity);


        m_l_capacity = 0;
        m_r_capacity = init.size();
        m_left = nullptr;
        m_right = m_alloc.allocate(m_r_capacity);
        m_l_size = 0;
        m_r_size = 0;
        m_l_free = 0;
        m_r_free = 0;
        for(const auto& elem : init)
        {
            push_back(elem);
        }
        return *this;
        
    }

    template<typename T, class Allocator>
    void deque<T,Allocator>::assign(size_type count, const value_type& val)
    {
        for(size_t i = m_l_free; i < m_l_size; ++i) 
        {
            m_left[i].~T();
        }
        for(size_t i = m_l_free; i < m_r_size; ++i) 
        {
            m_right[i].~T();
        }

        m_alloc.deallocate(m_left, m_l_capacity);
        m_alloc.deallocate(m_right, m_r_capacity);

        m_l_capacity = 0;
        m_r_capacity = count;
        m_left = nullptr;
        m_right = m_alloc.allocate(m_r_capacity);
        m_l_size = 0;
        m_r_size = 0;
        m_l_free = 0;
        m_r_free = 0;
        for(size_type i = 0; i < count; ++i)
        {
            push_back(val);
        }
    }

    template<typename T, class Allocator>
    void deque<T,Allocator>::assign(std::initializer_list<value_type> init)
    {
        for(size_t i = m_l_free; i < m_l_size; ++i) 
        {
            m_left[i].~T();
        }
        for(size_t i = m_l_free; i < m_r_size; ++i) 
        {
            m_right[i].~T();
        }

        m_alloc.deallocate(m_left, m_l_capacity);
        m_alloc.deallocate(m_right, m_r_capacity);

        m_l_capacity = 0;
        m_r_capacity = init.size();
        m_left = nullptr;
        m_right = m_alloc.allocate(m_r_capacity);
        m_l_size = 0;
        m_r_size = 0;
        m_l_free = 0;
        m_r_free = 0;
        for(const auto& elem : init)
        {
            push_back(elem);
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
        if(pos >= (m_l_size - m_l_free) + (m_r_size - m_r_free))
        {
            throw std::out_of_range("Out of range");
        }
        return m_l_size > pos ? m_left[m_l_size - pos - 1] : m_right[pos - m_l_size]; 
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::reference deque<T,Allocator>::front()
    {
        if (m_l_size - m_l_free > 0) 
        {
            return m_left[m_l_size - 1 - m_l_free];
        } 
        else if (m_r_size - m_r_free > 0) 
        {
            return m_right[m_r_free];
        }
        throw std::out_of_range("Deque is empty");
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::reference deque<T,Allocator>::back()
    {
        if(m_r_size - m_r_free > 0) 
        {
            return m_right[m_r_size - 1 - m_r_free];
        } 
        else if(m_l_size - m_l_free > 0) 
        {
            return m_left[m_l_free];
        }
        throw std::out_of_range("Deque is empty");
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::const_reference deque<T,Allocator>::front() const
    {
        if (m_l_size - m_l_free > 0) 
        {
            return m_left[m_l_size - 1 - m_l_free];
        } 
        else if (m_r_size - m_r_free > 0) 
        {
            return m_right[m_r_free];
        }
        throw std::out_of_range("Deque is empty");
    }

    template <typename T, class Allocator>
    typename deque<T,Allocator>::const_reference deque<T,Allocator>::back() const
    {
        if (m_r_size - m_r_free > 0) 
        {
            return m_right[m_r_size - 1 - m_r_free];
        } 
        else if (m_l_size - m_l_free > 0) 
        {
            return m_left[m_l_free];
        }
        throw std::out_of_range("Deque is empty");
    }


    template <typename T, class Allocator>
    typename deque<T,Allocator>::size_type deque<T,Allocator>::size() const
    {
        return (m_l_size - m_l_free) + (m_r_size - m_r_free);
    }

    template <typename T, class Allocator>
    bool deque<T,Allocator>::empty() const
    {
        return (m_l_size - m_l_free) == 0 && (m_r_size - m_r_free) == 0 ? true : false;
    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::clear()
    {
        if(m_left)
        {
            for(size_t i = m_l_free; i < m_l_size; ++i)
            {
                m_left[i].~value_type();
            }
        }

        if(m_r_size)
        {
            for(size_t i = m_r_free; i < m_r_size; ++i)
            {
                m_right[i].~value_type();
            }
        }
        m_l_size = 0;
        m_r_size = 0;
        m_l_free = 0;
        m_r_free = 0;
    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::push_back(const value_type& value)
    {
        if(m_l_free > 0)
        {
            m_alloc.construct(m_left + (m_l_free - 1), value);
            --m_l_free;
            ++m_l_size;
            return;
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
        if(m_l_free > 0)
        {
            m_alloc.construct(m_left + (m_l_free - 1), std::move(value));
            --m_l_free;
            ++m_l_size;
            return;
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
        if(m_r_free > 0)
        {
            m_alloc.construct(m_right + (m_r_free - 1), value);
            --m_r_free;
            ++m_r_size;
            return;
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
        if(m_r_free > 0)
        {
            m_alloc.construct(m_right + (m_r_free - 1), std::move(value));
            --m_r_free;
            ++m_r_size;
            return;
        }
        if(m_l_size == m_l_capacity)
        {
            reserve(m_l_capacity == 0 ? 1 : m_l_capacity * 2, true);
        }
        m_alloc.construct(m_left + m_l_size, std::move(value));
        ++m_l_size;
    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::pop_front()
    {
        if(m_l_size > 0)
        {
            m_left[m_l_size - 1].~value_type();
            --m_l_size;
        }
        else if(m_r_size - m_r_free > 0)
        {
            m_right[m_r_free].~value_type();
            ++m_r_free;
        }
    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::pop_back()
    {
        if(m_r_size > 0)
        {
            m_right[m_r_size - 1].~value_type();
            --m_r_size;
        }
        else if(m_l_size - m_l_free > 0)
        {
            m_left[m_l_free].~value_type();
            ++m_l_free;
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

                for(size_type i = m_l_free; i < m_l_size; ++i)
                {
                    m_alloc.construct(new_left + i, std::move(m_left[i]));
                }
                
                for(size_type i = m_l_free; i < m_l_size; ++i) 
                {
                    m_left[i].~value_type();
                }

                m_alloc.deallocate(m_left, m_l_capacity);

                m_left = new_left;
                m_l_capacity = newCapacity; 
                m_l_free = 0;                   
            }
        }
        else
        {
           if(newCapacity > m_r_capacity)
           {
                pointer new_right = m_alloc.allocate(newCapacity);

                for(size_type i = m_r_free; i < m_r_size; ++i)
                {
                    m_alloc.construct(new_right + i, std::move(m_right[i]));
                } 

                for(size_type i = m_r_free; i < m_r_size; ++i)
                {
                    m_right[i].~value_type();
                }

                m_alloc.deallocate(m_right, m_l_capacity);

                m_right = new_right;
                m_r_capacity = newCapacity;
                m_l_free = 0;
           } 
        }
    }

    template<typename T, class Allocator>
    void deque<T,Allocator>::resize(size_type count)
    {
        if(count > size())
        {
            resize(count,0);
        }
        else if(count < size())
        {
            for(size_type i = size(); i > count; --i)
            {
                pop_back();
            }
        }
        else
        {
            return;
        }
    }

    template <typename T, class Allocator>
    void deque<T,Allocator>::shrink_to_fit() 
    {
       
        if (m_l_size - m_l_free == m_l_capacity && m_r_size - m_r_free == m_r_capacity)
        {
            return;
        }
        size_t left_size = m_l_size - m_l_free;
        size_t right_size = m_r_size - m_r_free;
        
        
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
        
        m_l_free = 0;
        m_r_free = 0;
    }

    template <typename T, class Allocator>
    template<class ...Args>
    void deque<T,Allocator>::emplace_back(Args&&... args)
    {
        if (m_r_free > 0) 
        {
        m_alloc.construct(m_right + m_r_size, std::forward<Args>(args)...);//?
        ++m_r_size;
        --m_r_free;
        } 
        else 
        {
            if (m_r_size == m_r_capacity) 
            {
                reserve(m_r_capacity == 0 ? 1 : m_r_capacity * 2, false);
            }
            m_alloc.construct(m_right + m_r_size, std::forward<Args>(args)...);//?
            ++m_r_size;
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

    template<typename T, class Allocator>
    void deque<T,Allocator>::swap(deque& other) noexcept
    {
        std::swap(m_left, other.m_left);
        std::swap(m_right, other.m_right);
        std::swap(m_l_size, other.m_l_size);
        std::swap(m_r_size, other.m_r_size);
        std::swap(m_l_capacity, other.m_l_capacity);
        std::swap(m_r_capacity, other.m_r_capacity);
        std::swap(m_l_free, other.m_l_free);
        std::swap(m_r_free, other.m_r_free);
        std::swap(m_alloc, other.m_alloc);
    }

// ======================================================== const_terator ===================================================
    template<typename T, class Allocator>
    deque<T,Allocator>::const_iterator::const_iterator(pointer ptr, pointer left, pointer right, size_type l_size, size_type r_size) : m_ptr{ptr}, m_left{left}, m_right{right}, m_l_size{l_size}, m_r_size{r_size} {}

    template<typename T, class Allocator>
    typename deque<T, Allocator>::const_iterator deque<T, Allocator>::const_iterator::operator+(size_type n) const
    {
        return m_l_size > n ? const_iterator(m_left + m_l_size - n - 1, m_left, m_right, m_l_size, m_r_size) : const_iterator(m_right + n - m_l_size, m_left, m_right, m_l_size, m_r_size); 
    }


    // template<typename T, class Allocator>
    // typename deque<T,Allocator>::const_iterator deque<T,Allocator>::const_iterator::operator-(size_type n) const
    // {
    //     return m_l_size > n ? const_iterator(m_left - (m_l_size - n - 1), m_left, m_right, m_l_size, m_r_size) : const_iterator(m_right - n - m_l_size, m_left, m_right, m_l_size, m_r_size); 
    // }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::const_iterator& deque<T,Allocator>::const_iterator::operator++()
    {   
        if(m_ptr == m_left)
        {   
            if(m_right)
            {
                m_ptr = m_right;
            }
            else
            {
                --m_ptr;
            }
        }
        else if(m_l_size > 1)
        {
            --m_ptr;
            --m_l_size;
        }
        else if(m_ptr && m_r_size > 0)
        {
            ++m_ptr;
            --m_r_size;
        }
        else
        {   
            if(m_right)
            {
               ++m_ptr; 
            }
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
        if(m_ptr == m_right)
        {   
            if(m_left)
            {
                m_ptr = m_left;
            }
            else
            {
                --m_ptr;
            }
        }
        else if(m_ptr - m_right > 0)
        {
            --m_ptr;
            ++m_r_size;
        }
        else if(m_ptr && m_l_size > 0)
        {
            ++m_ptr;
            ++m_l_size;
        }
        else
        {   
            if(m_left)
            {
               ++m_ptr; 
            }
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

    template<typename T, class Allocator>
    typename deque<T,Allocator>::const_reference deque<T,Allocator>::const_iterator::operator[](size_type pos) const
    {   
        return m_l_size > pos ? m_left[m_l_size - pos - 1] : m_right[pos - m_l_size]; 
    }


    template<typename T, class Allocator>
    typename deque<T,Allocator>::const_iterator deque<T,Allocator>::begin() const 
    {   
        if(m_l_size > 0 && m_r_size > 0)
        {
            return const_iterator(m_left + m_l_size - 1, m_left + m_l_free, m_right + m_r_free, m_l_size - m_l_free, m_r_size - m_r_free);
        }
        if(m_l_size > 0 && m_r_size == 0)
        {
            return const_iterator(m_left + m_l_size - 1, m_left + m_l_free, nullptr, m_l_size - m_l_free, 0);
        }
        if(m_l_size == 0 && m_r_size > 0)
        {
            return const_iterator(m_right + m_r_free, nullptr, m_right + m_r_free, 0, m_r_size - m_r_free);
        }
        return const_iterator(m_left, m_left, m_right,0,0);
    }


    template<typename T, class Allocator>
    typename deque<T, Allocator>::const_iterator deque<T, Allocator>::end() const 
    {
        if(m_l_size > 0 && m_r_size > 0)
        {
            return const_iterator(m_right + m_r_size, m_left + m_l_free, m_right + m_r_free, 0, 1);
        }
        if(m_l_size > 0 && m_r_size == 0)
        {
            return const_iterator(m_left - 1, m_left + m_l_free, nullptr, m_l_size - m_l_free, 0);
        }
        if(m_l_size == 0 && m_r_size > 0)
        {
            return const_iterator(m_right + m_r_size, nullptr, m_right + m_r_free, 0, 1);
        }
        return const_iterator(m_left, m_left, m_right,0,0);
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::const_iterator deque<T,Allocator>::cbegin() const noexcept
    {
        return const_iterator(m_left + m_l_free, m_left + m_l_free, m_right + m_r_free, m_l_size - m_l_free, m_r_size - m_r_free);
    }

    template<typename T, class Allocator>
    typename deque<T, Allocator>::const_iterator deque<T, Allocator>::cend() const noexcept
    {
        return const_iterator(m_l_free + m_l_free, m_left + m_l_size, m_right + m_r_size, 0, 0);
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


// ======================================================== iterator ========================================================
    template<typename T, class Allocator>
    deque<T,Allocator>::iterator::iterator(pointer ptr, pointer left, pointer right, size_type l_size, size_type r_size) : const_iterator(ptr, left, right, l_size, r_size) {}

    template<typename T, class Allocator>
    typename deque<T, Allocator>::iterator deque<T, Allocator>::iterator::operator+(size_type n) const
    {
        return this->m_l_size > n ? iterator(this->m_left + this->m_l_size - n - 1, this->m_left, this->m_right, this->m_l_size, this->m_r_size) : iterator(this->m_right + n - this->m_l_size, this->m_left, this->m_right, this->m_l_size, this->m_r_size); 
    }


    // template<typename T, class Allocator>
    // typename deque<T,Allocator>::const_iterator deque<T,Allocator>::const_iterator::operator-(size_type n) const
    // {
    //     return m_l_size > n ? const_iterator(m_left - (m_l_size - n - 1), m_left, m_right, m_l_size, m_r_size) : const_iterator(m_right - n - m_l_size, m_left, m_right, m_l_size, m_r_size); 
    // }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::iterator& deque<T,Allocator>::iterator::operator++()
    {   
        if(this->m_ptr == this->m_left)
        {   
            if(this->m_right)
            {
                this->m_ptr = this->m_right;
            }
            else
            {
                --this->m_ptr;
            }
        }
        else if(this->m_l_size > 1)
        {
            --this->m_ptr;
            --this->m_l_size;
        }
        else if(this->m_ptr && this->m_r_size > 0)
        {
            ++this->m_ptr;
            --this->m_r_size;
        }
        else
        {   
            if(this->m_right)
            {
               ++this->m_ptr; 
            }
        }

        return *this;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::iterator deque<T,Allocator>::iterator::operator++(int)
    {
        const_iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::iterator& deque<T,Allocator>::iterator::operator--()
    {
        if(this->m_ptr == this->m_right)
        {   
            if(this->m_left)
            {
                this->m_ptr = this->m_left;
            }
            else
            {
                --this->m_ptr;
            }
        }
        else if(this->m_ptr - this->m_right > 0)
        {
            --this->m_ptr;
            ++this->m_r_size;
        }
        else if(this->m_ptr && this->m_l_size > 0)
        {
            ++this->m_ptr;
            ++this->m_l_size;
        }
        else
        {   
            if(this->m_left)
            {
               ++this->m_ptr; 
            }
        }

        return *this;
    }

    template<typename T, class Allocator>
    typename deque<T,Allocator>::iterator deque<T,Allocator>::iterator::operator--(int)
    {
        const_iterator tmp = *this;
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

    template<typename T, class Allocator>
    typename deque<T,Allocator>::reference deque<T,Allocator>::iterator::operator[](size_type pos) const
    {   
        return this->m_l_size > pos ?this->m_left[this->m_l_size - pos - 1] : this->m_right[pos - this->m_l_size]; 
    }


    template<typename T, class Allocator>
    typename deque<T,Allocator>::iterator deque<T,Allocator>::begin()  
    {   
        if(this->m_l_size > 0 && this->m_r_size > 0)
        {
            return iterator(this->m_left + this->m_l_size - 1, this->m_left + this->m_l_free, this->m_right + this->m_r_free, this->m_l_size - this->m_l_free, this->m_r_size - this->m_r_free);
        }
        if(this->m_l_size > 0 && this->m_r_size == 0)
        {
            return iterator(this->m_left + this->m_l_size - 1, this->m_left + this->m_l_free, nullptr, this->m_l_size - this->m_l_free, 0);
        }
        if(this->m_l_size == 0 && this->m_r_size > 0)
        {
            return iterator(this->m_right + this->m_r_free, nullptr, this->m_right + this->m_r_free, 0, this->m_r_size - this->m_r_free);
        }
        return iterator(this->m_left, this->m_left, this->m_right,0,0);
    }


    template<typename T, class Allocator>
    typename deque<T, Allocator>::iterator deque<T, Allocator>::end()  
    {
        if(this->m_l_size > 0 && this->m_r_size > 0)
        {
            return iterator(this->m_right + this->m_r_size, this->m_left + this->m_l_free, this->m_right + this->m_r_free, 0, 1);
        }
        if(this->m_l_size > 0 && this->m_r_size == 0)
        {
            return iterator(this->m_left - 1, this->m_left + this->m_l_free, nullptr, this->m_l_size - this->m_l_free, 0);
        }
        if(this->m_l_size == 0 && this->m_r_size > 0)
        {
            return iterator(this->m_right + this->m_r_size, nullptr, this->m_right + this->m_r_free, 0, 1);
        }
        return iterator(this->m_left, this->m_left, this->m_right,0,0);
    }
// ======================================================== reverse_iterator ================================================
// ======================================================== const_reverse_iterator ==========================================
}
