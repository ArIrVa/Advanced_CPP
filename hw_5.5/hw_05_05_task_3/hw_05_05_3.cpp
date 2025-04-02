// Задача 3. Счётчик чисел

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

class MyGetSum
{
public:
    MyGetSum(const std::vector<int> &arr) : sum{0}, data{arr} {};
    int operator()()
    {
        for (auto el : data)
        {
            if (!(el % 3))
            {
                sum += el;
            }
        }
        return sum;
    }

private:
    std::vector<int> data;
    int sum;
};

class MyGetCount
{
public:
    MyGetCount(const std::vector<int> &arr) : count{0}, data{arr} {};
    int operator()()
    {
        for (auto el : data)
        {
            if (!(el % 3))
            {
                count += 1;
            }
        }
        return count;
    }

private:
    std::vector<int> data;
    int count;
};

int main()
{
    std::vector<int> arr{4, 1, 3, 6, 25, 54};
    MyGetSum get_sum(arr);
    MyGetCount get_count(arr);

    cout << "[IN]: ";
    for (auto el : arr)
    {
        cout << el << " ";
    }
    cout << endl;
    cout << "[OUT]: ";
    cout << "get_sum() = " << get_sum() << endl;

    cout << "[OUT]: ";
    cout << "get_count() = " << get_count() << endl;
    cout << endl;

    return 0;
}