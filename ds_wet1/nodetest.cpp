#include <iostream>
#include "binary_tree.h" // Include the BinaryTree header file

// Function to print the key or data of a node
template <class Key, class Data>
void print_node(const Node<Key, Data> *node) {
    std::cout << node->get_key() << " "; // Assuming you have a get_key() function
    // std::cout << node->get_data() << " "; // Use this if you want to print data instead
}

int main() {
    // Create an instance of the BinaryTree
    BinaryTree<int, int> binary_tree;

    // Insert nodes into the binary tre
    std::shared_ptr<int> data = std::make_shared<int>(1);

    // Insert nodes into the binary tree
    binary_tree.insert_key_and_data(7,data);
    binary_tree.insert_key_and_data(13,data);

    binary_tree.insert_key_and_data(12,data);
    binary_tree.insert_key_and_data(20,data);
    binary_tree.insert_key_and_data(25,data);
    binary_tree.insert_key_and_data(0,data);
    binary_tree.insert_key_and_data(4,data);
    binary_tree.insert_key_and_data(100,data);



    // Perform in-order traversal and print the keys or data of each visited node
    std::cout << "In-order traversal (before deletion): ";
    binary_tree.in_order(print_node<int, int>, binary_tree.get_root());
    std::cout << std::endl;


    // preorder traversal
    std::cout << "Pre-order traversal: ";
    binary_tree.pre_order(print_node<int, int>, binary_tree.get_root());
    std::cout << std::endl;

    // postorder traversal
    std::cout << "Post-order traversal: ";
    binary_tree.post_order(print_node<int, int>, binary_tree.get_root());
    std::cout << std::endl;

    // Delete a node from the binary tree
    binary_tree.delete_key(20);
    binary_tree.delete_key(32626);

    // Perform in-order traversal after deletion and print the keys or data of each visited node
    std::cout << "In-order traversal (after deletion): ";
    binary_tree.in_order(print_node<int, int>, binary_tree.get_root());
    std::cout << std::endl;

    // preorder traversal
    std::cout << "Pre-order traversal: ";
    binary_tree.pre_order(print_node<int, int>, binary_tree.get_root());
    std::cout << std::endl;

    // postorder traversal
    std::cout << "Post-order traversal: ";
    binary_tree.post_order(print_node<int, int>, binary_tree.get_root());
    std::cout << std::endl;



    binary_tree.delete_tree();

    std::cout << "In-order traversal (after delete_tree): ";
    binary_tree.in_order(print_node<int, int>, binary_tree.get_root());
    std::cout << std::endl;

    // preorder traversal
    std::cout << "Pre-order traversal: ";
    binary_tree.pre_order(print_node<int, int>, binary_tree.get_root());
    std::cout << std::endl;

    // postorder traversal
    std::cout << "Post-order traversal: ";
    binary_tree.post_order(print_node<int, int>, binary_tree.get_root());
    std::cout << std::endl;



    return 0;
}