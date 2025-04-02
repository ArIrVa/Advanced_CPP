// Задача 2. Таблица

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
class table
{
public:
    table(size_t sz_row, size_t sz_col) : size_row{sz_row}, size_col{sz_col}
    {
        // создаем динамический двумерный массив
        data = new T *[size_row];
        for (size_t i = 0; i < size_row; ++i)
        {
            data[i] = new T[size_col]{};
        }
    }

    ~table()
    {
        // очищаем двумерный массив и память
        // cout << "Free memory..." << endl;
        for (size_t i = 0; i < size_row; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    }

    const size_t Size_row() { return size_row; }
    const size_t Size_col() { return size_col; }

    T *operator[](const int &index) { return data[index]; }
    const T *operator[](const int &index) const { return data[index]; }

private:
    T **data;
    size_t size_row;
    size_t size_col;
};

int main()
{
    // test
    auto test = table<int>(2, 3);
    test[0][0] = 4;
    std::cout << test[0][0] << endl; // выводит 4

    return 0;
}