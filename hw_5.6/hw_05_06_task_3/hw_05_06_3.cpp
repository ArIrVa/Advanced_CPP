// Задача 3*. Аналог std::vector

#include <iostream>
#include <exception>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
class MyVector
{
public:
    MyVector() : data_size{0}, cap{0}, data{new T[0]} {}
    ~MyVector()
    {
        if (data)
        {
            delete[] data; // освобождаем память в деструкторе
            std::cout << "Free memory ..." << std::endl;
        }
    }

    int &operator[](unsigned index) { return data[index]; } // определим оператор индекса для доступа к элементам массива

    int at(unsigned index)
    {
        if (index < data_size)
        {
            return data[index];
        }
        else
        {
            throw std::overflow_error("Ошибка! Индекс находится вне границ массива.");
        }
    }

    void push_back(T value)
    {
        data_size++;
        if (data_size == 1)
        {
            cap = 1;
            delete[] data;
            data = new T[cap];
        }
        else if ((data_size) > cap)
        {
            cap *= 2;
            T *new_data = new T[cap]; // создаем новый массив
            for (size_t i = 0; i < data_size - 1; ++i)
            {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            new_data = nullptr;
        }
        data[data_size - 1] = value;
    }

    size_t size()
    {
        return data_size;
    }

    size_t capacity()
    {
        return cap;
    }

private:
    T *data;
    size_t data_size;
    size_t cap;
};

int main()
{
    MyVector<int> vec;
    int i{};

    try
    {
        vec.push_back(1);
        vec.push_back(3);
        vec.push_back(10);
        vec.push_back(15);
        vec.push_back(8);
        vec.push_back(9);
        vec.push_back(4);
        vec.push_back(12);
        vec.push_back(17);

        for (int i = 0; i < vec.size(); ++i)
        {
            cout << vec[i] << " ";
        }
        cout << endl;
        i = 3;
        // cout << vec.at(9) << endl;   // проверка индекса вне границ
        cout << "at[" << i << "]: " << vec.at(i) << endl;
        cout << "size: " << vec.size() << endl;
        cout << "capacity: " << vec.capacity() << endl;
    }
    catch (const std::exception &ex)
    {
        cout << ex.what() << endl;
    }

    return 0;
}