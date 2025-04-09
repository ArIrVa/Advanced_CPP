// Задача 2. Печать контейнера

#include <iostream>
#include <vector>
#include <set>
#include <list>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
void print_container(const T &cont)
{
    for (auto el : cont)
    {
        cout << el << " ";
    }
    cout << endl;
}

int main()
{
    std::set<std::string> test_set = {"one", "two", "three", "four"};
    print_container(test_set); // four one three two.

    std::list<std::string> test_list = {"one", "two", "three", "four"};
    print_container(test_list); // one, two, three, four

    std::vector<std::string> test_vector = {"one", "two", "three", "four"};
    print_container(test_vector); // one, two, three, four

    return 0;
}