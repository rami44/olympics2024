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

    // Insert nodes into the binary tree
    // Assuming you have Node<Key, Data> constructor, create nodes with appropriate key and data values
    std::shared_ptr<Node<int, int>> node1 = std::make_shared<Node<int, int>>(1, std::make_shared<int>(1));
    std::shared_ptr<Node<int, int>> node2 = std::make_shared<Node<int, int>>(2, std::make_shared<int>(2));
    std::shared_ptr<Node<int, int>> node3 = std::make_shared<Node<int, int>>(3, std::make_shared<int>(3));
    std::shared_ptr<Node<int, int>> node4 = std::make_shared<Node<int, int>>(15, std::make_shared<int>(15));
    std::shared_ptr<Node<int, int>> node5 = std::make_shared<Node<int, int>>(80, std::make_shared<int>(80));
    std::shared_ptr<Node<int, int>> node6 = std::make_shared<Node<int, int>>(7, std::make_shared<int>(7));
    std::shared_ptr<Node<int, int>> node7 = std::make_shared<Node<int, int>>(90, std::make_shared<int>(90));
    std::shared_ptr<Node<int, int>> node8 = std::make_shared<Node<int, int>>(13, std::make_shared<int>(13));
    std::shared_ptr<Node<int, int>> node9 = std::make_shared<Node<int, int>>(12, std::make_shared<int>(12));
    std::shared_ptr<Node<int, int>> node10 = std::make_shared<Node<int, int>>(91, std::make_shared<int>(91));

    // Insert nodes into the binary tree
    binary_tree.insert_node(node1);
    binary_tree.insert_node(node2);
    binary_tree.insert_node(node3);
    binary_tree.insert_node(node4);
    binary_tree.insert_node(node5);
    binary_tree.insert_node(node6);
    binary_tree.insert_node(node7);
    binary_tree.insert_node(node8);
    binary_tree.insert_node(node9);
    binary_tree.insert_node(node10);
    binary_tree.insert_node(node5);
    binary_tree.insert_node(node6);


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
    binary_tree.delete_node(node4); // delete node with key 3

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
