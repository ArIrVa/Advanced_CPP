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
    BigInteger(BigInteger &&other) noexcept : bnum{std::move(other.bnum)}, size{std::move(other.size)} {}

    // перемещающий оператор присваивания
    BigInteger &operator=(BigInteger &&other) noexcept
    {
        bnum = std::move(other.bnum);
        size = std::move(other.size);
        return *this;
    }

    // оператор сложения с большим числом
    BigInteger operator+(BigInteger &other) noexcept
    {
        return add_bignum(*this, other);
    }

    // оператор сложения с целым числом
    BigInteger operator+(const int &other) noexcept
    {
        std::vector<int> other_num;
        int m = other;
        while(m){
            other_num.push_back(m % 10);
            m /= 10;
        }
        auto other_bigint = BigInteger(other_num);
        return add_bignum(*this, other_bigint);
    }

    // оператор умножения на большое число
    BigInteger operator*(BigInteger &other)
    {
        return mult_bignum(*this, other);
    }

    // оператор умножения на целое число
    BigInteger operator*(const int &other)
    {
        std::vector<int> other_num;
        int m = other;
        while(m){
            other_num.push_back(m % 10);
            m /= 10;
        }
        auto other_bigint = BigInteger(other_num); 
        return mult_bignum(*this, other_bigint);
    }

    std::string get_number()
    {
        return bnum;
    }

    // умножение двух больших чисел
    BigInteger mult_bignum(BigInteger& num1, BigInteger& num2) 
    {
        BigInteger bin(std::move(num2));
        int ms{0}, md{0}, me{0}, d1{0}, d2{0}, k{0};
        std::vector<int> digits;
        for (int i = bin.size-1; i>=0 ; --i)
        {
            for (int j = num1.size-1; j>=0; --j)
            {
                k = (bin.size-i-1)+(num1.size-j-1);
                d1 = bin.bnum[i] - '0';
                d2 = num1.bnum[j] - '0';
                ms = d1 * d2 + me;
                
                if(digits.size()>k){
                    ms += digits[k];
                }
                
                md = ms/10;
                me = ms%10;
                
                if(digits.size()<=k){
                    digits.push_back(me);
                } else {
                    digits[k]=me;
                }
                me = md;

            }
            if(me){
                digits.push_back(me);
                me = 0;
            }
        }
        std::reverse(digits.begin(), digits.end());
        bin = BigInteger(digits);
        num1.bnum = bin.bnum;
        num1.size = bin.size;

        return std::move(num1);
    }

    // сложение двух больших чисел
    BigInteger add_bignum(BigInteger& num1, BigInteger& num2) 
    {
        int dd{0}, dig1{0}, dig2{0}, sumd{0}, se{0}, sd{0};
        std::vector<int> digits;
        BigInteger bin(std::move(num2));
        for (int i = (num1.size - 1), j = (bin.size - 1); i >= 0 || j >= 0; --i, --j)
        {
            dig1 = i < 0 ? 0 : (num1.bnum[i] - '0');
            dig2 = j < 0 ? 0 : (bin.bnum[j] - '0');
            sumd = dig1 + dig2 + se;
            sd = sumd / 10;
            se = sumd % 10;
            digits.push_back(se);
            se = sd;
        }
        if (se)
        {
            digits.push_back(se);
        }

        std::reverse(digits.begin(), digits.end());
        bin = BigInteger(digits);
        num1.bnum = bin.bnum;
        num1.size = bin.size;

        return std::move(num1);
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
    // auto number1 = big_integer("999999");
    // auto number2 = big_integer("1");
    // auto number2 = 1;
    // auto result = number1 + number2;

    // умножение чисел
    auto number1 = big_integer("999999");
    // auto number2 = big_integer("2");
    // auto number2 = 2;
    // auto result = number1 * number2;
    auto result = number1 * 2;

    std::cout << result << endl; 

    return 0;
}