#include <iostream>
#include <utility>
#pragma once
namespace usu
{
    template <typename T>
    class shared_ptr
    {
      public:
        shared_ptr(T* t) :
            m_ref_count(new unsigned int(1)),
            m_raw_ptr(t){};
        unsigned int use_count() const { return *m_ref_count; };
        T* get() { return m_raw_ptr; };
        shared_ptr(shared_ptr& ptr)
        {
            m_raw_ptr = new T;
            // copy values
            *m_raw_ptr = *ptr.m_raw_ptr;
            // increment ptr ref at memory location
            *ptr.m_ref_count += 1;
            // make the memory locations the same
            m_ref_count = ptr.m_ref_count;
        }
        ~shared_ptr()
        {
            // std::cout << "Destructor. ref count: " << *m_ref_count << std::endl;
            if (*m_ref_count > 0)
            {
                *m_ref_count -= 1;
            }
            // std::cout << "ref count after: " << *m_ref_count << std::endl;
            if (*m_ref_count == 0)
            {
                // std::cout << "deleting pointer" << std::endl;
                delete m_raw_ptr;
                m_raw_ptr = nullptr;
            }
        }
        // shared_ptr(shared_ptr&& ptr)
        // {
        //     m_raw_ptr = ptr.m_raw_ptr;
        //     m_ref_count = ptr.m_ref_count;
        //     ptr.m_raw_ptr = nullptr;
        //     // *ptr.m_ref_count -= 1;
        //     // std::swap(m_raw_ptr, ptr.m_raw_ptr);
        //     // std::swap(m_ref_count, ptr.m_ref_count);
        //     // ptr.m_raw_ptr = nullptr;
        //     // *ptr.m_ref_count -= 1;

        //     // ptr.m_raw_ptr=
        // }
        T operator*() { return *m_raw_ptr; }
        T* operator->() { return m_raw_ptr; }
        shared_ptr<T>& operator=(shared_ptr&& rhs)
        {
            // std::cout << "move assignment op ref count before: " << *m_ref_count << " rhs ref count: " << *rhs.m_ref_count;
            std::swap(m_raw_ptr, rhs.m_raw_ptr);
            std::swap(m_ref_count, rhs.m_ref_count);
            // std::cout << " move assignment op ref count after: " << *m_ref_count <<  " rhs ref count: " << *rhs.m_ref_count << std::endl;
            return *this;
        }
        shared_ptr<T> operator=(shared_ptr& rhs)
        {
            *m_ref_count -= 1;
            m_raw_ptr = rhs.m_raw_ptr;
            m_ref_count = rhs.m_ref_count;
            *m_ref_count += 1;
            return *this;
        }

      private:
        unsigned int* m_ref_count;
        T* m_raw_ptr;
    };
    template <typename T>
    class shared_ptr<T[]>
    {
      public:
        shared_ptr(T* t, std::size_t number) :
            pointer(t), count(new unsigned int(1)), thisSize(number) {}
        ~shared_ptr()
        {
            *count -= 1;

            if (count == 0)
            {
                delete[] pointer;
                delete count;
            }
        }

        T& operator[](int index)
        {
            if (static_cast<std::size_t>(index) >= thisSize)
            {
                std::cout << "Index " << index << " out of bounds" << std::endl;
                exit(1);
            }

            return pointer[index];
        }

        std::size_t size()
        {
            return thisSize;
        }

      private:
        T* pointer;
        unsigned int* count;
        std::size_t thisSize;
    };
    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }
    template <typename T, unsigned int N>
    shared_ptr<T[]> make_shared_array()
    {
        return shared_ptr<T[]>(new T[N], N);
    }
} // namespace usu
