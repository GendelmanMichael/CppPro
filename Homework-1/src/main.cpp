#include <vector>
#include <iostream>

std::vector<int> v = {1, 2, 3, 4, 5};

/*
void int_func(int &i)
{
    i *= i;
}

bool predicate(int &i)
{
    return i > 10;
}
*/

template <typename F>
void for_each(std::vector<int> &v, F f) // void (*f)(int &))
{
    for (int i = 0; i < v.size(); i++)
    {
        f(v[i]);
    }
}

template <typename F>
bool all(std::vector<int> &v, F f) // bool (*f)(int &))
{
    for (int i = 0; i < v.size(); i++)
    {
        if (!f(v[i]))
        {
            return false;
        }
    }
    return true;
}

template <typename F>
int count_if(std::vector<int> &v, F f) // bool (*f)(int &))
{
    int res = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (f(v[i]))
        {
            res++;
        }
    }
    return res;
}

void print_vector(std::vector<int> &v)
{
    std::cout << "{ ";
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << (i == v.size() - 1 ? " }" : ", ");
    }
    std::cout << std::endl;
}

int main()
{
    print_vector(v);
    for_each(v, [](int &i)
             { i = i * i; }); // int_func);
    print_vector(v);
    std::cout << all(v, [](int &i)
                     { return i > 0; })
              << std::endl;
    std::cout << count_if(v, [](int &i)
                          { return i > 10; })
              << std::endl;
    return 0;
}