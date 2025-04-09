// Задача 1. Уникальный вектор

#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::vector<int> vec = {1, 1, 2, 5, 6, 1, 2, 4};
    auto begin = vec.begin();
    auto end = vec.end();

    cout << "[IN]: ";
    for (auto i : vec)
    {
        cout << i << " ";
    }
    cout << endl;

    std::sort(begin, end,                          // отсортируем вектор
              [](const int &el1, const int &el2) { // зададим условие сортировки
                  return el1 < el2;
              });

    auto it_start = std::unique(begin, end); // определим итератор начала, с которого надо удалить все дубли
    vec.erase(it_start, end);                // удаляем дубли
    cout << "[OUT]: ";
    for (auto i : vec)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}