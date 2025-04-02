// Задача 1. Возведение в квадрат

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
T sqrt(T val)
{
    return val *= val;
};

template <typename T>
std::vector<T> sqrt(std::vector<T> &vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        vec[i] *= vec[i];
    }
    return vec;
};

int main()
{
    int int_num{};
    std::vector<int> vector_num{};

    int_num = 4;
    cout << "[IN]: " << int_num << endl;
    cout << "[OUT]: " << sqrt(int_num) << endl;
    vector_num = {-1, 4, 8};
    cout << "[IN]: ";
    for (auto el : vector_num)
    {
        cout << el << ", ";
    }
    cout << endl;
    cout << "[OUT]: ";
    for (auto el : sqrt(vector_num))
    {
        cout << el << ", ";
    }
    cout << endl;

    return 0;
}