#include "Node.h"
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
    BinaryTree(const BinaryTree<Key, Data>& other) = delete;
    BinaryTree& operator=(const BinaryTree<Key, Data>& other) = delete;

    // Getter methods
    std::shared_ptr<Node<Key, Data>> get_root() const {
        return root;
    }

    int get_numOfNodes() const {
        return numOfNodes;
    }

    std::shared_ptr<Node<Key, Data>> get_maxNode() const {
        return maxNode;
    }

    void update_maxNode(const std::shared_ptr<Node<Key, Data>>& curr) {
        if (curr == nullptr) return;
        maxNode = curr;
        update_maxNode(curr->get_right());
    }

    // Other methods...

    // Inconsistent comment in node_exists, assuming it should be key comparison
    bool node_exists(const std::shared_ptr<Node<Key, Data>>& node,
                     const std::shared_ptr<Node<Key, Data>>& curr) {
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
    void LR_rolling(const std::shared_ptr<Node<Key, Data>>& rolling_node) {
        // Implementation...
    }

    // LL rotation
    void LL_rolling(const std::shared_ptr<Node<Key, Data>>& rolling_node) {
        // Implementation...
    }

    // RL rotation
    void RL_rolling(const std::shared_ptr<Node<Key, Data>>& rolling_node) {
        // Implementation...
    }

    // RR rotation
    void RR_rolling(const std::shared_ptr<Node<Key, Data>>& rolling_node) {
        // Implementation...
    }

    // Apply rotation
    void apply_roll(const std::shared_ptr<Node<Key, Data>>& rolling_node) {
        if (rolling_node->get_balance_factor() == 2) {
            int left_bf = (rolling_node->get_left() == nullptr) ? 0 : rolling_node->get_left()->get_balance_factor();
            if (left_bf == -1) {
                LR_rolling(rolling_node);
            } else {
                LL_rolling(rolling_node);
            }
        } else if (rolling_node->get_balance_factor() == -2) {
            int right_bf = (rolling_node->get_right() == nullptr) ? 0 : rolling_node->get_right()->get_balance_factor();
            if (right_bf == 1) {
                RL_rolling(rolling_node);
            } else {
                RR_rolling(rolling_node);
            }
        }
    }


};
