// Задача 2. Большие числа

#include <iostream>
#include <vector>
#include <memory>
#include <cstring>
#include <algorithm>
#include <utility>

using std::cin;
using std::cout;
using std::endl;

class BigInteger
{
public:
    BigInteger(const char *cn)
    {
        if (cn)
        {
            size = std::strlen(cn);
            for (size_t i = 0; i < size; ++i)
            {
                bnum += cn[i];
            }
        }
    }
    BigInteger(const std::vector<int> &sn)
    {
        if (sn.size())
        {
            size = sn.size();
            for (auto el : sn)
            {
                bnum += std::to_string(el);
            }
        }
    }
    ~BigInteger() {}

    BigInteger &operator=(const BigInteger &&other) = delete;

    // конструктор перемещения
    BigInteger(BigInteger &&other) noexcept : bnum{std::exchange(other.bnum, "")}, size{std::exchange(other.size, 0)} {}

    // перемещающий оператор присваивания
    BigInteger &operator=(BigInteger &&other) noexcept
    {
        bnum = std::move(other.bnum);
        size = std::move(other.size);
        return *this;
    }

    // оператор сложения двух больших чисел
    BigInteger &&operator+(BigInteger &other) noexcept
    {
        int dd{0}, dig1{0}, dig2{0}, sumd{0};
        std::vector<int> digits;
        BigInteger bin(std::move(other));
        for (int i = (size - 1), j = (bin.size - 1); i >= 0 || j >= 0; --i, --j)
        {
            dig1 = i < 0 ? 0 : (bnum[i] - '0');
            dig2 = j < 0 ? 0 : (bin.bnum[j] - '0');
            sumd = dig1 + dig2;
            digits.push_back(((sumd % 10) + dd));
            dd = (sumd / 10) >= 1 ? 1 : 0;
            sumd = 0;
        }
        if (dd)
        {
            digits.push_back(dd);
        }

        std::reverse(digits.begin(), digits.end());
        bin = BigInteger(digits);
        bnum = bin.bnum;
        size = bin.size;

        return std::move(*this);
    }

    // оператор умножения на число
    BigInteger operator*(BigInteger &other)
    {
        BigInteger bin(std::move(other));
        int mult{0}, pd{0}, dd{0}, sd{0}, dig{0}, sumd{0};
        int len = size + bin.size;
        std::vector<int> digits;
        for (int j = 0; j < bin.size; ++j)
        {
            for (int i = 0; i < size; ++i)
            {
                pd = i + j;
                mult = (bnum[size - i - 1] - '0') * (bin.bnum[bin.size - j - 1] - '0');
                dig = ((mult + dd) % 10);
                dd = (mult + dd) / 10;
                if (pd > (static_cast<int>(digits.size()) - 1))
                {
                    sumd = dig + sd;
                    digits.push_back(sumd % 10);
                    sd = sumd / 10;
                }
                else
                {
                    sumd = (digits[pd] + dig + sd);
                    digits[pd] = sumd % 10;
                    sd = sumd / 10;
                }
                sumd = 0;
            }
            if (dd || sd)
            {
                pd++;
                if (pd > (static_cast<int>(digits.size()) - 1))
                {
                    digits.push_back(dd + sd);
                }
                else
                {
                    digits[pd] += dd + sd;
                }
                dd = 0;
                sd = 0;
            }
        }
        std::reverse(digits.begin(), digits.end());
        bin = BigInteger(digits);
        bnum = bin.bnum;
        size = bin.size;

        return std::move(*this);
    }

    std::string get_number()
    {
        return bnum;
    }

private:
    int size;
    std::string bnum;
};
std::ostream &operator<<(std::ostream &out, BigInteger &other)
{
    out << other.get_number();
    return out;
}

int main()
{
    using big_integer = BigInteger;

    // сложение чисел
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << endl; // 193099

    return 0;
}