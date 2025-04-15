// Задача 3*. std::unique_ptr своими руками

#include <iostream>
#include <vector>
#include <memory>
#include <exception>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
class MyUniquePtr
{
public:
    MyUniquePtr(T *ptr) : u_ptr{ptr} {}
    ~MyUniquePtr()
    {
        if (u_ptr)
        {
            std::cout << "Free memory...";
            delete u_ptr;
        }
    }

    MyUniquePtr(const MyUniquePtr &) = delete; // удаляем конструктор копирования из класса

    MyUniquePtr &operator=(const MyUniquePtr &) = delete; // удаляем оператор присваивания

    T &operator*()
    {
        if (u_ptr == nullptr)
        {
            throw std::invalid_argument("Ошибка! nullptr ");
        }
        else
        {
            return *u_ptr;
        }
    }

    T *operator->()
    {
        return get_val();
    }

    T *release()
    {
        T *new_ptr = u_ptr;
        u_ptr = nullptr;
        return new_ptr;
    }

    T *get_val()
    {
        if (!u_ptr)
        {
            throw std::invalid_argument("Ошибка! nullptr ");
        }
        else
        {
            return u_ptr;
        }
    }

private:
    T *u_ptr;
};

int main()
{
    return 0;
}