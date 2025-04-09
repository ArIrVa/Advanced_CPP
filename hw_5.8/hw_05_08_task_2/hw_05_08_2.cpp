// Задача 2. Устранение пересечения

#include <iostream>
#include <vector>
#include <memory>

class Node
{
public:
    int m_value;
    // std::shared_ptr<Node> parent;    // заменим на weak_ptr, который не является владельцем ресурса
    std::weak_ptr<Node> parent;
    Node(int value) : m_value{value} {};
    ~Node() { std::cout << "destructor called\n"; }
};

int main()
{
    {
        auto node1 = std::make_shared<Node>(1);
        auto node2 = std::make_shared<Node>(2);
        node1->parent = node2;
        node2->parent = node1;
    }

    return 0;
}
