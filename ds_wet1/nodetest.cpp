#include "binary_tree.h"
#include <iostream>

int main() {
    // Create a binary tree
    BinaryTree<int, int> tree;
    std::shared_ptr<Node<int, int>> node3 = std::make_shared<Node<int, int>>(1, std::make_shared<int>(50));
    // Test get_root function
    std::shared_ptr<Node<int, int>> root = tree.get_root();
    if (root == nullptr) {
        std::cout << "Binary tree root is nullptr." << std::endl;
    } else {
        std::cout << "Binary tree root key: " << root->get_key() << std::endl;
    }
    // Add nodes to the binary tree
    std::shared_ptr<Node<int, int>> node1 = std::make_shared<Node<int, int>>(5, std::make_shared<int>(10));
    std::shared_ptr<Node<int, int>> node2 = std::make_shared<Node<int, int>>(8, std::make_shared<int>(20));
    tree.get_root()->set_left(node1);
    tree.get_root()->set_right(node2);

    // Test get_numOfNodes function
    std::cout << "Number of nodes in the binary tree: " << tree.get_numOfNodes() << std::endl;

    // Test get_maxNode and update_maxNode functions
    std::shared_ptr<Node<int, int>> maxNode = tree.get_maxNode();
    if (maxNode == nullptr) {
        std::cout << "Max node in the binary tree is nullptr." << std::endl;
    } else {
        std::cout << "Max node key: " << maxNode->get_key() << std::endl;
    }
    tree.update_maxNode(tree.get_root());
    maxNode = tree.get_maxNode();
    if (maxNode == nullptr) {
        std::cout << "Max node in the binary tree is nullptr." << std::endl;
    } else {
        std::cout << "Max node key after update: " << maxNode->get_key() << std::endl;
    }

    // Test node_exists function
    std::shared_ptr<Node<int, int>> node3 = std::make_shared<Node<int, int>>(3, std::make_shared<int>(30));
    if (tree.node_exists(node3, tree.get_root())) {
        std::cout << "Node with key 3 exists in the binary tree." << std::endl;
    } else {
        std::cout << "Node with key 3 does not exist in the binary tree." << std::endl;
    }

    return 0;
}
