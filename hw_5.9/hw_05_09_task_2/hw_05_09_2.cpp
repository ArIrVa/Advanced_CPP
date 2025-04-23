// Задача 2. Большие числа

#include <iostream>
#include <vector>
#include <memory>
#include <cstring>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;


class BigInteger {
    public:
        BigInteger(const char* cn) { 
            if(cn){
                size = std::strlen(cn); 
                bnum = new char[size];
                for(size_t i = 0; i < size; ++i){
                    bnum[i] = cn[i];
                }
            }
        }
        BigInteger(const std::vector<int>& sn) { 
            if(sn.size()){
                std::string strnum;
                size = sn.size(); 
                bnum = new char[size+1];
                for(auto el : sn){
                    strnum += std::to_string(el);
                }
                for(size_t i = 0; i < size; ++i){
                    bnum[i] = strnum[i];
                }
                bnum[size] = '\0';
            }
        }
        ~BigInteger() { 
            if(bnum){
                // cout << "Free memory..." << endl;
                delete bnum;
            }
        }

        BigInteger& operator=(const BigInteger&& other) = delete;

        // конструктор перемещения
        BigInteger(BigInteger&& other) noexcept : 
            bnum{ std::exchange(other.bnum, nullptr) }, size{ std::exchange(other.size, 0) } { }
    
        // перемещающий оператор присваивания
        BigInteger& operator=(BigInteger&& other) noexcept 
        { 
            std::swap(bnum, other.bnum);
            std::swap(size, other.size);
            return *this;
        }

        // оператор сложения двух больших чисел
        BigInteger operator+(const BigInteger& other ) 
            {
            int dd{0}, dig1{0}, dig2{0}, sumd{0};
            std::vector<int> digits;
            for(int i = (size - 1), j = (other.size - 1); i >= 0 || j >= 0; --i, --j)
            {
                dig1 = i < 0 ? 0 : (bnum[i] - '0'); 
                dig2 = j < 0 ? 0 : (other.bnum[j] - '0'); 
                sumd = dig1 + dig2;
                digits.push_back(((sumd % 10) + dd));
                dd = (sumd / 10) >= 1 ? 1 : 0; 
                sumd = 0;
            }
            if(dd){ 
                digits.push_back(dd);
            }

            std::reverse(digits.begin(), digits.end());

            return BigInteger(digits); 
        }

        // оператор умножения на число
        BigInteger operator*(const BigInteger& other ) 
        {
            int mult{0}, pd{0}, dd{0}, sd{0}, dig{0}, sumd{0};
            int len = size + other.size;
            std::vector<int> digits;
            for(int j = 0; j < other.size; ++j){
                for(int i = 0; i < size; ++i){
                    pd = i + j;
                    mult = (bnum[size - i -1] - '0') * (other.bnum[other.size - j - 1] - '0');
                    dig = ((mult + dd) % 10) ;
                    dd = (mult + dd) / 10;
                    if(pd > (static_cast<int>(digits.size()) - 1)){
                        sumd = dig + sd;
                        digits.push_back(sumd % 10);
                        sd = sumd / 10;
                    } else {
                        sumd = (digits[pd] + dig + sd);
                        digits[pd] = sumd % 10;
                        sd = sumd / 10;
                    }
                    sumd = 0;
                }
                if(dd || sd){ 
                    pd++;
                    if(pd > (static_cast<int>(digits.size()) - 1)){
                        digits.push_back(dd + sd);
                    } else {
                        digits[pd] += dd + sd; 
                    }
                    dd = 0;
                    sd = 0;
                    
                }
            }

            std::reverse(digits.begin(), digits.end());

            return BigInteger(digits);
        }

        std::string get_number(){
            std::string result;
            for(size_t i = 0; i < size; ++i){
                result += bnum[i];
            }
            return result;
        }

    private:
        char* bnum;
        int size;
        
};
std::ostream& operator<<(std::ostream& out, BigInteger& other){

    out << other.get_number(); 
    return out;
}

int main(){

    using big_integer = BigInteger;

    // сложение чисел
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << endl; // 193099


    return 0;
}