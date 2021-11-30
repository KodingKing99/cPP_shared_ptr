#include <utility>
namespace usu
{
    template <typename T>
    class shared_ptr
    {
      public:
        shared_ptr(T* t) :
            m_ref_count(1)
        {
            m_raw_ptr = t;
        };
        unsigned int use_count() { return m_ref_count; };

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
