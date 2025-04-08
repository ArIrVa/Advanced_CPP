// Задача 3. Счётчик чисел

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

class MyFunctor
{
public:
    MyFunctor(const std::vector<int> &arr) : sum{0}, count{0}, data{arr} {}
    int operator()()
    {
        for (auto el : data)
        {
            if (!(el % 3))
            {
                sum += el;
                count += 1;
            }
        }
        return sum;
    }

    int get_sum()
    {
        return sum;
    }

    int get_count()
    {
        return count;
    }

private:
    std::vector<int> data;
    int sum;
    int count;
};

int main()
{
    std::vector<int> arr{4, 1, 3, 6, 25, 54};
    MyFunctor func_arr(arr);
    
    func_arr(); // вызываем функтор для подсчета суммы и количества элементов
    cout << "[IN]: ";
    for (auto el : arr)
    {
        cout << el << " ";
    }
    cout << endl;
    cout << "[OUT]: ";
    cout << "get_sum() = " << func_arr.get_sum() << endl;

    cout << "[OUT]: ";
    cout << "get_count() = " << func_arr.get_count() << endl;
    cout << endl;

    return 0;
}