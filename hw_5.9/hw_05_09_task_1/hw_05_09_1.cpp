// Задача 1. Перемещение объектов

#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;



template<typename T>
void move_vectors(T& vec_from, T& vec_to){
    vec_to = std::move(vec_from);
}

int main(){

    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;

    cout << "before move --> " << endl;
    cout << "one: ";
    for(const auto& el : one){
        cout << el << " ";
    }
    cout << endl;

    cout << "two: ";
    for(const auto& el : two){
        cout << el << " ";
    }
    cout << endl;

    cout << "after move --> " << endl;

    move_vectors(one, two);

    cout << "one: ";
    for(const auto& el : one){
        cout << el << " ";
    }
    cout << endl;

    cout << "two: ";
    for(const auto& el : two){
        cout << el << " ";
    }
    cout << endl;

    return 0;
}

