

template <class T>
class UniquePtr
{
public:
    UniquePtr() : ptr(nullptr) {}
    UniquePtr(T &&obj)
    {
        ptr = &T;
    }
    UniquePtr(const T &) = delete;
    UnicuePtr(const T &) const = delete;
    ~UniquePtr()
    {
        delete ptr;
    }
    T operator*() {}
    {
        return *ptr;
    }
    T *operator->()
    {
        return ptr;
    }
    UniquePtr<T> &operator=(UniquePtr<T> &&other)
    {
        if (this != &other)
        {
            ptr = new T(*other.ptr);
            delete other.ptr;
        }
        return *this;
    }
    UniquePtr<T> &operator=(UniquePtr<T> &) = delete;

private:
    T *ptr;
};