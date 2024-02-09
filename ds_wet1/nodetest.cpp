#include "Node.h"
#include <iostream>
#include <memory>
int main() {
    // Creating nodes with integer key and value
    std::shared_ptr<Node<int, int>> node1 = std::make_shared<Node<int, int>>(1, std::make_shared<int>(20));
    std::shared_ptr<Node<int, int>> node2 = std::make_shared<Node<int, int>>(2, std::make_shared<int>(10));
    std::shared_ptr<Node<int, int>> node3 = std::make_shared<Node<int, int>>(3, std::make_shared<int>(30));
    std::shared_ptr<Node<int, int>> node4 = std::make_shared<Node<int, int>>(4, std::make_shared<int>(40));
    std::shared_ptr<Node<int, int>> node5 = std::make_shared<Node<int, int>>(5, std::make_shared<int>(50));


    // Set height and balance factor
    node1->set_left(node2);
    node2->set_left(node3);
    node3->set_left(node4);
    node4->set_left(node5);



    node5->set_Height(); // Height of node1 is 4
    node5->set_BF();

    node4->set_Height(); // Height of node1 is 4
    node4->set_BF();

    node3->set_Height(); // Height of node1 is 4
    node3->set_BF();

    node2->set_Height(); // Height of node1 is 4
    node2->set_BF();

    node1->set_Height(); // Height of node1 is 4
    node1->set_BF(); // Balance Factor of node1 is 4


    std::cout << "Height of node3: " << node1->get_Height() << std::endl;
    std::cout << "Balance Factor of node3: " << node1->get_BF() << std::endl;

    return 0;
}

