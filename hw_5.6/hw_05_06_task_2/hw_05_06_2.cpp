// Задача 2. Удаление дубликатов

#include <iostream>
#include <set>
#include <deque>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::set<int> num_set;
    std::deque<int> dec;
    int num_count{}, numbers{};

    cout << "[IN]: " << endl;
    cin >> num_count;

    for (int i = 0; i < num_count; ++i)
    {
        cin >> numbers;
        num_set.insert(numbers);
    }

    for (auto &el : num_set)
    {
        dec.push_front(el);
    }

    cout << "[OUT]:" << endl;
    for (const auto &el : dec)
    {
        cout << el << endl;
    }

    return 0;
}