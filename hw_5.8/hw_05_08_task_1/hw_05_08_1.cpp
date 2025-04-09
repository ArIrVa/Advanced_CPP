// Задача 1. Клонирование объекта класса

#include <iostream>
#include <vector>
#include <memory>

using std::cin;
using std::cout;
using std::endl;

class Tridiagonal_matrix
{
public:
    std::vector<double> m_down;
    std::vector<double> m_upper;
    std::vector<double> m_middle;
    Tridiagonal_matrix(
        const std::vector<double> &down,
        const std::vector<double> &upper,
        const std::vector<double> &middle) : m_down{down}, m_upper{upper}, m_middle{middle} {};
    ~Tridiagonal_matrix() { std::cout << "destructor called\n"; }

    std::unique_ptr<Tridiagonal_matrix> clone()
    {
        std::unique_ptr<Tridiagonal_matrix> new_matrix = (std::make_unique<Tridiagonal_matrix>(m_down, m_upper, m_middle));
        return new_matrix;
    }
};
int main()
{
    auto down = std::vector<double>{-4.0, 5.0};
    auto upper = std::vector<double>{14.0, 8.0};
    auto middle = std::vector<double>{3.0, 1.0, 7.0};
    auto matrix = std::make_unique<Tridiagonal_matrix>(
        down,
        upper,
        middle);

    auto matrix_clone = matrix->clone();

    // получим адреса
    // cout << matrix.get() << endl;
    // cout << matrix_clone.get() << endl;

    return 0;
}
