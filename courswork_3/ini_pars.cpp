// Курсовой проект: "Парсер INI-файлов"

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <exception>
#include <map>
#include <algorithm>
#include <math.h>

using std::cin;
using std::cout;
using std::endl;

class ParsExcept : public std::exception
{
public:
    ParsExcept() {}

    ParsExcept(const std::string &message) : message{message} {}
    const char *what() const noexcept override
    {
        return message.c_str();
    }

    std::string err() const
    {
        return "Ошибка парсинга! Причина: ";
    }   

private:
    std::string message;
};

class ParsINI
{

public:
    ParsINI(const std::string &f) : file{f}
    {
        init();
    }
    ~ParsINI() {}

    std::string pars_sec(const std::string &str)
    {
        std::string section = str.substr(0, str.find("."));
        str_trim(section);
        return section;
    }

    std::string pars_param(const std::string &str)
    {
        std::string param = str.substr(str.find(".") + 1, str.size());
        str_trim(param);
        return param;
    }

    const std::string get_secvalue(const std::string &sec, const std::string &par)
    {
        return secval[sec][par];
    }

    void check_parvalue(const std::string &sec, const std::string &par)
    {
        std::map<std::string, std::string> m = secval[sec];
        if (!m.count(par))
        {
            std::string param_list;
            for (const auto &p : m)
            {
                param_list += p.first + "=" + p.second + ", ";
            }
            throw ParsExcept("Переменная не найдена. \nСписок доступных переменных: " + param_list);
        }
        else
        {
            std::string val = secval[sec][par];
            if (val == "")
            {
                throw ParsExcept("Значение переменной отсутствует.");
            }
        }
    }

    template <typename T>
    T get_value(const std::string &sec_value)
    {
        std::string section = pars_sec(sec_value);
        std::string param = pars_param(sec_value);
        check_parvalue(section, param);
        std::string val = get_secvalue(section, param);
        return convert<T>(val);
    }

    std::string get_value(const std::string &sec_value)
    {
        std::string section = pars_sec(sec_value);
        std::string param = pars_param(sec_value);
        check_parvalue(section, param);
        return get_secvalue(section, param);
    }

private:
    std::string file;
    std::vector<std::string> data;
    std::map<std::string, std::map<std::string, std::string>> secval;

    void init()
    {
        std::ifstream inf(file);
        std::string line;
        if (inf.is_open())
        {
            while (!inf.eof())
            {
                getline(inf, line);
                data.push_back(line);
            }
            inf.close();
        }
        else
        {
            std::cout << "Не удалось открыть файл!" << std::endl;
            return;
        }
        get_data();
    };

    void get_data()
    {
        std::string sec, param_name, param_value;
        size_t isc{0};
        int line_num{0};
        for (auto &line : data)
        {
            line_num++;
            if (line.find('[') != std::string::npos && line.find(']') != std::string::npos)
            {
                str_trim(line);
                sec = line.substr(1, line.length() - 2);
                if (secval.count(sec) == 0)
                {
                    secval[sec] = {};
                }
            }
            else if (line.find('=') != std::string::npos)
            {
                isc = line.find(';');
                if (isc != std::string::npos)
                {
                    line.resize(isc);
                }
                param_name = line.substr(0, line.find("="));
                param_value = line.substr(line.find("=") + 1, line.length());
                if (param_name != "")
                {
                    str_trim(param_name);
                    if (param_value != "")
                    {
                        str_trim(param_value);
                        secval[sec][param_name] = param_value;
                    }
                    else
                    {
                        secval[sec][param_name] = "";
                    }
                }
            }
            else if (line.find(';') != std::string::npos || line == "")
            {
                continue;
            }
            else
            {
                std::string err_line = "Некорректные данные. Строка (" + std::to_string(line_num) + "): " + line;
                throw ParsExcept(err_line);
            }
        }
        data = {};
    }

    void str_trim(std::string &str)
    {
        // очистка строки от пробелов
        if (str == "")
        {
            return;
        }
        int i{0}, j{0};
        size_t len = str.length();

        // удалить пробелы в начале строки
        while (str[i] == ' ' || str[i] == '\t')
        {
            i++;
        }
        if (i)
        {
            while ((j + i) < len)
            {
                str[j] = str[j + i];
                j++;
            }
            str.resize(j);
            len = str.length();
        }

        // удалить пробелы в конце строки
        j = len - 1;
        while (str[j] == ' ' || str[j] == '\t')
        {
            j--;
        }
        if (j == (len - 1))
        {
            return;
        }
        j++;
        str.resize(j);
    }

    template <typename T>
    T convert(std::string &s)
    {
        T result{0};
        int lnum{0}, rnum{0};
        auto point = s.find('.');
        if (point != std::string::npos)
        {
            lnum = get_numbers(s.substr(0, point));
            rnum = get_numbers(s.substr(point + 1, s.length()));
            result = lnum + rnum / pow(10, s.length() - point - 1);
        }
        else
        {
            result = get_numbers(s);
        }
        return result;
    };

    std::string convert(std::string &s)
    {
        return s;
    }

    int get_numbers(const std::string &s)
    {
        int result{0};
        std::vector<int> dig;
        bool sign{false};
        int i{0};

        if (s[0] == '-')
        {
            sign = true;
            ++i;
        }
        for (size_t j = i; j < s.length(); j++)
        {
            if (!isdigit(s[j]))
            {
                throw ParsExcept("Значение не может быть преобразовано в число.");
            }
            dig.push_back(static_cast<int>(s[j]) & 0x0F);
        }
        if (dig.size() > 0)
        {
            result = dig[0];
            for (size_t i = 1; i < dig.size(); i++)
            {
                result = result * 10 + dig[i];
            }
        }
        if (sign)
        {
            result *= -1;
        }
        return result;
    }
};

int main()
{
    using ini_parser = ParsINI;

    try
    {
        ini_parser parser("params.ini");

        auto value = parser.get_value<int>("Section2.var1");
        cout << "value: " << value << endl;
    }
    catch (const ParsExcept &pex)
    {
        cout << pex.err() << pex.what() << endl;
    }

    return 0;
}