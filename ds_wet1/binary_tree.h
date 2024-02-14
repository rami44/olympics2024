#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "Node.h"
#include <iostream>
#include <memory>  // Include necessary header for std::shared_ptr

template<class Key, class Data>

class BinaryTree {

private:
    std::shared_ptr<Node<Key, Data>> root;
    int numOfNodes;
    std::shared_ptr<Node<Key, Data>> maxNode;

public:
    // Constructor
    BinaryTree() : root(nullptr), numOfNodes(0), maxNode(nullptr) {}

    // Destructor
    virtual ~BinaryTree() = default;

    // Copy and assignment operators are deleted
    BinaryTree(const BinaryTree<Key, Data> &other) = delete;

    BinaryTree &operator=(const BinaryTree<Key, Data> &other) = delete;

    // Getter methods
    std::shared_ptr<Node<Key, Data>> get_root() const {
        return root;
    }


    std::shared_ptr<Node<Key, Data>> minNode(std::shared_ptr<Node<Key, Data>> node) {
        std::shared_ptr<Node<Key, Data>> current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != nullptr)
            current = current->left;

        return current;
    }


    void update_height_and_bf_after_rolling(const std::shared_ptr<Node<Key, Data>> &node) {
        node->get_right()->set_Height();
        node->get_right()->set_BF();
        node->get_left()->set_Height();
        node->get_left()->set_BF();
        node->set_Height();
        node->set_BF();
    }

    // switch nodes
    void swap_keys_data(std::shared_ptr<Node<Key, Data>> node1, std::shared_ptr<Node<Key, Data>> node2) {
        Key temp_key = node1->get_key();
        std::shared_ptr<Data> temp_data = node1->get_data();
        node1->set_key(node2->get_key());
        node1->set_data(node2->get_data());
        node2->set_key(temp_key);
        node2->set_data(temp_data);
    }

    void switch_nodes(std::shared_ptr<Node<Key, Data>> node1, std::shared_ptr<Node<Key, Data>> node2) {
        swap_keys_data(node1, node2);
    }

    int get_numOfNodes() const {
        return numOfNodes;
    }

    std::shared_ptr<Node<Key, Data>> get_maxNode() const {
        return maxNode;
    }

    void update_maxNode(const std::shared_ptr<Node<Key, Data>> &curr) {
        if (curr == nullptr) return;
        maxNode = curr;
        update_maxNode(curr->get_right());
    }

    // Other methods...

    bool node_exists(const std::shared_ptr<Node<Key, Data>> &node,
                     std::shared_ptr<Node<Key, Data>> curr) {
        if (curr == nullptr)
            return false;
        Key k = node->get_key();
        if (k == curr->get_key())
            return true;
        if (k < curr->get_key())
            return node_exists(node, curr->get_left());

        return node_exists(node, curr->get_right());
    }

    // In-order traversal
    template<class Func>
    void in_order(Func functionPointer, std::shared_ptr<Node<Key, Data>> curr) {
        if (curr == nullptr) return;
        in_order(functionPointer, curr->get_left());
        functionPointer(curr);  // Do something with the node
        in_order(functionPointer, curr->get_right());
    }

    // Pre-order traversal
    template<class Func>
    void pre_order(Func functionPointer, std::shared_ptr<Node<Key, Data>> curr) {
        if (curr == nullptr) return;
        functionPointer(curr);  // Do something with the node
        pre_order(functionPointer, curr->get_left());
        pre_order(functionPointer, curr->get_right());
    }

    // Post-order traversal
    template<class Func>
    void post_order(Func functionPointer, std::shared_ptr<Node<Key, Data>> curr) {
        if (curr == nullptr) return;
        post_order(functionPointer, curr->get_left());
        post_order(functionPointer, curr->get_right());
        functionPointer(curr);  // Do something with the node
    }

    // Rolling methods...
    // LR rotation
    void LR_rolling( std::shared_ptr<Node<Key, Data>> &rolling_node) {
        std::shared_ptr<Node<Key, Data>> root_father = rolling_node->get_father();
        std::shared_ptr<Node<Key, Data>> left_son_of_new_root = rolling_node->get_left();
        std::shared_ptr<Node<Key, Data>> new_root = left_son_of_new_root->get_right();

        if (root_father != nullptr) {
            if ((root_father->get_left() != nullptr) &&
                (*(root_father->get_left())) == *rolling_node) {
                root_father->set_left(new_root);
            } else {
                root_father->set_right(new_root);
            }

            new_root->set_father(root_father);
        } else {
            new_root->set_father(nullptr);
            root = new_root;
        }

        rolling_node->set_left(new_root->get_right());
        if (rolling_node->get_left() != nullptr) rolling_node->get_left()->set_father(rolling_node);

        left_son_of_new_root->set_right(new_root->get_left());
        if (left_son_of_new_root->get_right() != nullptr)
            left_son_of_new_root->get_right()->set_father(left_son_of_new_root);

        new_root->set_right(rolling_node);
        new_root->set_left(left_son_of_new_root);
        new_root->get_left()->set_father(new_root);
        new_root->get_right()->set_father(new_root);

        update_height_and_bf_after_rolling(new_root);
    }

    // LL rotation
    void LL_rolling( std::shared_ptr<Node<Key, Data>> &rolling_node) {
        std::shared_ptr<Node<Key, Data>> root_father = rolling_node->get_father();
        std::shared_ptr<Node<Key, Data>> new_root = rolling_node->get_left();
        if (root_father != nullptr) { // rolling_node is not the root
            if ((root_father->get_left() != nullptr) && (*(root_father->get_left()) == *rolling_node)) {
                root_father->set_left(new_root);
            } else {
                root_father->set_right(new_root);
            }

            new_root->set_father(root_father);
        } else {
            new_root->set_father(nullptr);
            root = new_root;
        }

        rolling_node->set_father(new_root);
        rolling_node->set_left(new_root->get_right());
        if (rolling_node->get_left() != nullptr) rolling_node->get_left()->set_father(rolling_node);
        new_root->set_right(rolling_node);

        update_height_and_bf_after_rolling(new_root);
    }

    // RL rotation
    void RL_rolling( std::shared_ptr<Node<Key, Data>> &rolling_node) {
        std::shared_ptr<Node<Key, Data>> root_father = rolling_node->get_father();
        std::shared_ptr<Node<Key, Data>> right_son_of_new_root = rolling_node->get_right();
        std::shared_ptr<Node<Key, Data>> new_root = right_son_of_new_root->get_left();

        if (root_father != nullptr) {
            if ((root_father->get_left() != nullptr) && (*(root_father->get_left()) == *rolling_node)) {
                root_father->set_left(new_root);
            } else {
                root_father->set_right(new_root);
            }
            new_root->set_father(root_father);
        } else {
            new_root->set_father(nullptr);
            root = new_root;
        }

        rolling_node->set_right(new_root->get_left());
        if (rolling_node->get_right() != nullptr) rolling_node->get_right()->set_father(rolling_node);

        right_son_of_new_root->set_left(new_root->get_right());
        if (right_son_of_new_root->get_left() != nullptr)
            right_son_of_new_root->get_left()->set_father(right_son_of_new_root);

        new_root->set_right(right_son_of_new_root);
        new_root->set_left(rolling_node);
        new_root->get_left()->set_father(new_root);
        new_root->get_right()->set_father(new_root);

        update_height_and_bf_after_rolling(new_root);
    }

    // RR rotation
    void RR_rolling( std::shared_ptr<Node<Key, Data>> &rolling_node) {
        std::shared_ptr<Node<Key, Data>> root_father = rolling_node->get_father();
        std::shared_ptr<Node<Key, Data>> new_root = rolling_node->get_right();
        if (root_father != nullptr) { // rolling_node is not the root
            if ((root_father->get_left() != nullptr) && (*(root_father->get_left()) == *rolling_node)) {
                root_father->set_left(new_root);
            } else {
                root_father->set_right(new_root);
            }

            new_root->set_father(root_father);
        } else {
            new_root->set_father(nullptr);
            root = new_root;
        }

        rolling_node->set_father(new_root);
        rolling_node->set_right(new_root->get_left());
        if (rolling_node->get_right() != nullptr) rolling_node->get_right()->set_father(rolling_node);
        new_root->set_left(rolling_node);

        update_height_and_bf_after_rolling(new_root);
    }

    // Apply rotation
    void apply_roll(std::shared_ptr<Node<Key, Data>> &rolling_node) {
        if (rolling_node->get_BF() == 2) {
            int left_bf = (rolling_node->get_left() == nullptr) ? 0 : rolling_node->get_left()->get_BF();
            if (left_bf == -1) {
                LR_rolling(rolling_node);
            } else {
                LL_rolling(rolling_node);
            }
        } else if (rolling_node->get_BF() == -2) {
            int right_bf = (rolling_node->get_right() == nullptr) ? 0 : rolling_node->get_right()->get_BF();
            if (right_bf == 1) {
                RL_rolling(rolling_node);
            } else {
                RR_rolling(rolling_node);
            }
        }
    }

    //updating the height and balance factor of each node that took part in the inserting
    void update_tree_stats(const std::shared_ptr<Node<Key, Data>> &leaf) {
        std::shared_ptr<Node<Key, Data>> current_node = leaf;
        while (current_node != nullptr) {
            current_node->set_Height();
            current_node->set_BF();
            current_node = current_node->get_father();
        }
    }

    void update_tree_add(const std::shared_ptr<Node<Key, Data>> &leaf) {
        update_tree_stats(leaf);//making sure all heights and bf are updated
        std::shared_ptr<Node<Key, Data>> current_node = leaf;
        while (current_node != nullptr && (current_node->get_BF() != 2 &&
                                           current_node->get_BF() != -2)) {
            current_node = current_node->get_father();
        }
        if (current_node == nullptr) return;
        // surely BF is either 2/-2
        apply_roll(current_node);
        update_tree_stats(leaf);
    }

    bool insert_key(const Key& key) {
        if (get_node_from_key(key) == nullptr) {
            std::shared_ptr<Node<Key, Data>> new_node =
                    std::make_shared<Node<Key, Data>>(key, std::make_shared<int>(0));
            insert_node(new_node);
            return true;
        }
        return false;
    }

    bool insert_node(std::shared_ptr<Node<Key, Data>> &new_node) {
        if (node_exists(new_node, root))
            return false;//node already in the tree
        if (numOfNodes == 0) {
            root = new_node;
            root->set_right(nullptr);
            root->set_left(nullptr);
            numOfNodes++;
            maxNode = new_node;
            return true;
        }
        Key k = new_node->get_key();
        std::shared_ptr<Node<Key, Data>> tmp = root;
        std::shared_ptr<Node<Key, Data>> last = tmp;
        while (tmp != nullptr) {
            last = tmp;
            if (k < tmp->get_key()) {
                tmp = tmp->get_left();
            } else {
                tmp = tmp->get_right();
            }
        }
        if (last->get_key() > k) {
            last->set_left(new_node);
        } else {
            last->set_right(new_node);
        }
        new_node->set_father(last);
        numOfNodes++;

        update_maxNode(root);
        update_tree_add(new_node);

        return true;
    }

    void fix_avl_after_deletion(std::shared_ptr<Node<Key, Data>> &deletion_node) {
        numOfNodes--;
        std::shared_ptr<Node<Key, Data>> tmp = deletion_node->get_father();
        while (tmp != nullptr) { // go up the tree and fix the BF and height until the root

            tmp->set_Height();
            tmp->set_BF();
            if (tmp->get_BF() == 2 || tmp->get_BF() == -2) { // need to apply roll
                apply_roll(tmp);
            } //      return;
            tmp = tmp->get_father(); // go up the tree
        }
    }

    std::shared_ptr<Node<Key, Data>> get_node_from_key(const Key &key) {
        std::shared_ptr<Node<Key, Data>> tmp = root;
        while (tmp != nullptr) {
            if (tmp->get_key() == key) {
                return tmp;
            }
            if (key < tmp->get_key()) {
                tmp = tmp->get_left();
            } else {
                tmp = tmp->get_right();
            }
        }
        return nullptr;
    }

    bool delete_key(const Key &key) {
        std::shared_ptr<Node<Key, Data>> node = get_node_from_key(key);
        if (node == nullptr) return false;
        delete_node(node);
        return true;
    }

    // delete node from the tree
    void delete_node(std::shared_ptr<Node<Key, Data>>& node) {
        // if the node has no children (leaf)
        if (node->get_Height() == 0) { // leaf
            if (node->get_father() == nullptr) { // single node in the tree
                root = nullptr;
            } else { // not the root
                if (node->get_father()->get_left() == node) { // left child
                    node->get_father()->set_left(nullptr);
                } else { // right child
                    node->get_father()->set_right(nullptr);
                    }
                }
                fix_avl_after_deletion(node);
                return;
            }
            // if the node has only one child
            if (node->get_left() == nullptr && node->get_right() != nullptr ||
                node->get_left() != nullptr && node->get_right() == nullptr) {
                std::shared_ptr<Node<Key, Data>> child = (node->get_left() == nullptr) ? node->get_right()
                                                                                       : node->get_left();
                if (node->get_father() == nullptr) { // node is the root
                    root = child;
                    child->set_father(nullptr);
                } else { // node is not the root
                    if (node->get_father()->get_left() == node) { // left child
                        node->get_father()->set_left(child);
                    } else { // right child
                        node->get_father()->set_right(child);
                    }
                    child->set_father(node->get_father());
                }
                fix_avl_after_deletion(node);
                return;
            } else {
                // if the node has two children
                std::shared_ptr<Node<Key, Data>> successor = node->get_right();
                while (successor->get_left() != nullptr) { // find the successor
                    successor = successor->get_left();
                }
                switch_nodes(node, successor);
                delete_node(successor); // delete the successor as it is now leaf
                return;
            }
        }
};

#endif
