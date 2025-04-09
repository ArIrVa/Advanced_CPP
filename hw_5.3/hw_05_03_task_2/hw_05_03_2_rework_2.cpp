// Задача 2. Копирование умных массивов

#include <iostream>
#include <exception>

class Smart_array
{
public:
    Smart_array(unsigned size) : data{new int[size]}, data_size{size}, count{0} {} // создаем динамический массив в конструкторе
    ~Smart_array()
    {
        if (data)
        {
            delete[] data; // освобождаем память в деструкторе
            std::cout << "Free memory ..." << std::endl;
        }
    }

    Smart_array(const Smart_array &) = delete; // удаляем конструктор копирования из класса

    int &operator[](unsigned index) { return data[index]; } // определим оператор индекса для доступа к элементам массива    

    Smart_array &operator=(Smart_array &other)
    {
        delete[] data;  // освободим память под старый массив в левом массиве

        // скопируем соответствующие значения полей
        data_size = other.data_size;
        count = other.count;

        data = new int[data_size];  // выделим память под новый массив в левом массиве

        for(unsigned i = 0; i < data_size; ++i){    // скопируем данные из правого массива
            data[i] = other.data[i];
        }        
        
        return *this;
    }
    // Функция добавления нового элемента в массив
    void add_element(int value)
    {
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
    // Функция получения элемента по индексу
    int get_element(unsigned index)
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
        Smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;
        //  std::cout << arr[0] << "test " << arr[1] << std::endl;       // проверка
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
