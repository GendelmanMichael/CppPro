
#include <iostream>
#include <string>

template <class T>
class UniquePtr
{
public:
    UniquePtr() : ptr(nullptr) {}
    UniquePtr(T &&obj)
    {
        ptr = new T(obj);
    }
    UniquePtr(UniquePtr &&uptr)
    {
        ptr = nullptr;
        if (uptr.ptr != nullptr)
        {
            ptr = new T(*uptr.ptr);
            delete uptr.ptr;
            uptr.ptr = nullptr;
        }
    }
    UniquePtr(const T &) = delete;
    ~UniquePtr()
    {
        if (ptr != nullptr)
        {
            delete ptr;
        }
    }
    T &operator*() // розмінування додав амперсенд
    {
        return ptr == nullptr ? T() : *ptr;
    }
    T *operator->()
    {
        return ptr;
    }
    UniquePtr<T> &operator=(UniquePtr<T> &&other)
    {
        if (this != &other)
        {
            ptr = nullptr;
            if (other.ptr != nullptr)
            {
                ptr = new T(*other.ptr);
                delete other.ptr;
                other.ptr = nullptr;
            }
        }
        return *this;
    }
    UniquePtr<T> &operator=(T &&obj)
    {
        ptr = new T(obj);
        return *this;
    }
    UniquePtr<T> &operator=(UniquePtr<T> &) = delete;

    bool operator bool() const
    {
        return ptr != nullptr;
    }

private:
    T *ptr;
};

int main()
{
    UniquePtr<std::string> ptr("Hello world!!!");
    std::cout << "Value by audsterix: " << *ptr << std::endl;
    std::cout << "Length by ref: " << ptr->length() << std::endl;

    UniquePtr<std::string> ptr2(std::move(ptr));
    std::cout << "Value of 2 by audsterix: " << *ptr2 << std::endl;
    std::cout << "Length of 2 by ref: " << ptr2->length() << std::endl;

    return 0;
}