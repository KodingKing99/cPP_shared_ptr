#include <iostream>
#include <utility>
#pragma once
namespace usu
{
    template <typename T>
    class shared_ptr
    {
      public:
        shared_ptr(T* t)
        {
            m_ref_count = new unsigned int;
            std::cout << "In overloaded const. Ref count: before " << *m_ref_count;
            *m_ref_count = 1;
            std::cout << " ref count after: " << *m_ref_count << std::endl;
            m_raw_ptr = new T;
            m_raw_ptr = t;
        };
        unsigned int use_count() const { return *m_ref_count; };
        T* get() { return m_raw_ptr; };
        shared_ptr(shared_ptr& ptr)
        // initialize m_count to be 1
        {
            // allocate memory
            m_raw_ptr = new T;
            // copy values
            *m_raw_ptr = *ptr.m_raw_ptr;
            // increment ptr ref at memory location
            // std::cout << "Copy constructor. rhs ref count before: " << *ptr.m_ref_count;
            *ptr.m_ref_count += 1;
            // std::cout << "rhs ref count after: " << *ptr.m_ref_count;
            // make the memory locations the same
            m_ref_count = ptr.m_ref_count;
            // std::cout << "lhs ref count after: " << *m_ref_count << std::endl;
        }
        ~shared_ptr()
        {
            std::cout << "Destructor. ref count: " << *m_ref_count << std::endl;
            *m_ref_count -= 1;
            std::cout << "ref count after: " << *m_ref_count << std::endl;
            if (*m_ref_count == 0)
            {
                std::cout << "deleting pointer" << std::endl;
                delete m_raw_ptr;
                m_raw_ptr = nullptr;
            }
        }

      private:
        unsigned int* m_ref_count;
        T* m_raw_ptr;
    };
    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }
} // namespace usu
