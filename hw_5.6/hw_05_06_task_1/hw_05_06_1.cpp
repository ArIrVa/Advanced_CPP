// Задача 1. Частота символов

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;

int main()
{

    std::string str = "Hello world!!";                 // заданный текст
    std::map<std::string, int> chars_count;            // для хранения символов и количества повторов
    std::vector<std::pair<std::string, int>> pair_vec; // для хранения пары ключ-значение для применения сортировки

    for (const char &el : str)
    {
        chars_count[std::string{el}] += 1; // map принимает ключь в виде строки, поэтому преобразуем char в string
                                           // чудесным образом не надо инициализировать значение нулем при создании, сразу увеличиваем на один
    }

    std::map<std::string, int>::iterator itmap; // создаем итератор

    for (itmap = chars_count.begin(); itmap != chars_count.end(); itmap++)
    {
        pair_vec.push_back(std::make_pair(itmap->first, itmap->second)); // добавляем в вектор пары
    }

    std::sort(pair_vec.begin(), pair_vec.end(), [](const auto &p1, const auto &p2) { // сортируем по значению
        return p1.second > p2.second;
    });

        // Вывод
    cout << "[IN]: " << str << endl;
    cout << "[OUT]: " << endl;

    for (auto el : pair_vec)
    {
        cout << el.first << " : " << el.second << endl;
    }

    return 0;
}