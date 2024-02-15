#include <iostream>
#include "binary_tree.h" // Include the BinaryTree header file

// Function to print the key or data of a node
template <class Key, class Data>
void print_node(const std::shared_ptr<Node<Key, Data>>& node) {
    std::cout << node->get_key() << " "; // Assuming you have a get_key() function
    // std::cout << node->get_data() << " "; // Use this if you want to print data instead
}

int main() {
    // Create an instance of the BinaryTree
    BinaryTree<int, int> binary_tree;

    // Insert nodes into the binary tre

    // Insert nodes into the binary tree
    binary_tree.insert_key(5);
    binary_tree.insert_key(2);
    binary_tree.insert_key(8);
    binary_tree.insert_key(1);
    binary_tree.insert_key(4);
    binary_tree.insert_key(6);
    binary_tree.insert_key(10);
    binary_tree.insert_key(3);
    binary_tree.insert_key(7);
    binary_tree.insert_key(9);
    binary_tree.insert_key(12);
    binary_tree.insert_key(11);
    binary_tree.insert_key(13);
    binary_tree.insert_key(14);


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
    binary_tree.delete_key(1);
    binary_tree.delete_key(200);

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

    return 0;
}