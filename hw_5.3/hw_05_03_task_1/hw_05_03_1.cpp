// Задача 1. Умный массив

#include <iostream>
#include <exception>

class Smart_array
{
public:
    Smart_array(unsigned size) : data{new int[size]}, data_size{size}, count{0} {} // создаем динамический массив в конструкторе
    ~Smart_array()
    {
        std::cout << "Free memory ..." << std::endl;
        delete[] data; // освобождаем память в деструкторе
    }

    int &operator[](unsigned index) { return data[index]; } // определим оператор индекса для доступа к элементам массива

    void add_element(int value)
    {
        // Функция добавления нового элемента в массив
        if (count < data_size)
        {
            data[count] = value;
            count++;
        }
        else
        {
            throw std::overflow_error("Ошибка! Массив переполнен.");
        }
    }

    int get_element(unsigned index)
    {
        // Функция получения элемента по индексу
        if (index >= 0 && index < data_size)
        {
            return data[index];
        }
        else
        {
            throw std::overflow_error("Ошибка! Индекс находится вне границ массива.");
        }
    }

private:
    int *data;
    unsigned data_size;
    int count;
};

int main()
{
    try
    {
        Smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);
        std::cout << arr.get_element(1) << std::endl;

        // arr.add_element(1000);   // проверка на добавление элемента в переполненный массив
        // std::cout << arr.get_element(5) << std::endl;    // проверка на обращение по индексу вне диапазона
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}