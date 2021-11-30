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
            m_ref_count(1)
        {
            m_raw_ptr = new T;
            m_raw_ptr = t;
        };
        unsigned int use_count() const { return m_ref_count; };
        T* get() { return m_raw_ptr; };
        // initialize m_count to be 1
        shared_ptr(shared_ptr& ptr) :
            m_ref_count(1)
        {
            // allocate memory
            m_raw_ptr = new T;
            // copy values
            *m_raw_ptr = *ptr.m_raw_ptr;
            // increment ptr ref count
            ptr.m_ref_count++;
        }
        ~shared_ptr()
        {
            std::cout << "Destructor. ref count: " << m_ref_count << std::endl;
            m_ref_count--;
            std::cout << "ref count after: " << m_ref_count << std::endl;
            if (m_ref_count == 0)
            {
                std::cout << "deleting pointer" << std::endl;
                delete m_raw_ptr;
                m_raw_ptr = nullptr;
            }
        }

      private:
        unsigned int m_ref_count;
        T* m_raw_ptr;
    };
    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }
} // namespace usu
