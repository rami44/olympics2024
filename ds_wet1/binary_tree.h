#include "Node.h"

template<class Key, class Data>
class BinaryTree {
private:
 main
    std::shared_ptr<Node<Key, Data>> root;
    int numOfNodes;
    std::shared_ptr<Node<Key, Data>> maxNode;

    std::shared_ptr <Node<Key, Data>> root;
    int numOfNodes;
    std::shared_ptr <Node<Key, Data>> maxNode;
 
public:
    //ctor
    BinaryTree() : root(nullptr), numOfNodes(0), maxNode(nullptr) {}

    virtual ~BinaryTree() = default;

    //copy and assignment operators are not valid
    BinaryTree(const BinaryTree<Key, Data> &other) = delete;

    BinaryTree &operator=(const BinaryTree<Key, Data> &other) = delete;


    std::shared_ptr<Node<Key, Data>> get_root() const {

    std::shared_ptr <Node<Key, Data>> get_root() const {

        return root;
    }

    int get_numOfNodes() const {
        return numOfNodes;
    }


    std::shared_ptr<Node<Key, Data>> get_maxNode() const {
        return maxNode;
    }

    void update_maxNode(const std::shared_ptr<Node<Key, Data>> &curr) {

    std::shared_ptr <Node<Key, Data>> get_maxNode() const {
        return maxNode;
    }

    void update_maxNode(const std::shared_ptr <Node<Key, Data>> &curr) {

        if (curr == nullptr) return;
        maxNode = curr;
        update_maxNode(curr->get_right());
    }


    bool node_exists(const std::shared_ptr<Node<Key, Data>> &node, const std::shared_ptr<Node<Key, Data>> &curr) {
=======
    bool node_exists(const std::shared_ptr <Node<Key, Data>> &node, const std::shared_ptr <Node<Key, Data>> &curr) {

        Key k = node->get_key();
        if (curr == nullptr)
            return false;

        if (k == curr->get_key())
            return true;
        if (k < curr->get_key())
            return node_exists(node, curr->get_left());

        return node_exists(node, curr->get_right());

    }

    // in order
    template<class Func>

    void in_order(Func functionPointer, std::shared_ptr<Node<Key, Data>> curr) {

    void in_order(Func functionPointer, std::shared_ptr <Node<Key, Data>> curr) {

        {
            if (curr == nullptr) return;
            in_order(functionPointer, curr->get_left());
            functionPointer(curr); // do something with the node
            in_order(functionPointer, curr->get_right());
        }
    }

    // pre order
    template<class Func>

    void pre_order(Func functionPointer, std::shared_ptr<Node<Key, Data>> curr) {

    void pre_order(Func functionPointer, std::shared_ptr <Node<Key, Data>> curr) {

        if (curr == nullptr) return;
        functionPointer(curr); // do something with the node
        pre_order(functionPointer, curr->get_left());
        pre_order(functionPointer, curr->get_right());
    }

    // post order
    template<class Func>

    void post_order(Func functionPointer, std::shared_ptr<Node<Key, Data>> curr) {

    void post_order(Func functionPointer, std::shared_ptr <Node<Key, Data>> curr) {

        if (curr == nullptr) return;
        post_order(functionPointer, curr->get_left());
        post_order(functionPointer, curr->get_right());
        functionPointer(curr); // do something with the node
    }


    // Rolling

    // LR rotation
    void LR_rolling(const std::shared_ptr<Node<Key, Data>> &rolling_node) {
        std::shared_ptr<Node<Key, Data>> left = rolling_node->get_left();
        std::shared_ptr<Node<Key, Data>> left_right = left->get_right();
        std::shared_ptr<Node<Key, Data>> father = rolling_node->get_father();

        if (father == nullptr) { // rolling_node is the root
            root = left;
            left->set_father(nullptr);
        } else { // rolling_node is not the root (
            if (father->get_left() == rolling_node) {
                father->set_left(left);
            } else {
                father->set_right(left);
            }
        }

        left->set_father(father);
        rolling_node->set_left(left_right);
        if (left_right != nullptr) {
            left_right->set_father(rolling_node);
        }
        left->set_right(rolling_node);
        rolling_node->set_father(left);
        rolling_node->set_Height();
        left->set_Height();
        if (rolling_node == maxNode) {
            update_maxNode(rolling_node);
        }
    }


    // Rolling

    // LR rotation
    void LR_rolling(const std::shared_ptr <Node<Key, Data>> &rolling_node) {
        std::shared_ptr <Node<Key, Data>> left = rolling_node->get_left();
        std::shared_ptr <Node<Key, Data>> left_right = left->get_right();
        std::shared_ptr <Node<Key, Data>> father = rolling_node->get_father();

        if (father == nullptr) { // rolling_node is the root
            root = left;
            left->set_father(nullptr);
        } else { // rolling_node is not the root (
            if (father->get_left() == rolling_node) {
                father->set_left(left);
            } else {
                father->set_right(left);
            }
        }


    void LL_rolling(const std::shared_ptr<Node<Key, Data>> &rolling_node) {
    
        left->set_father(father);
        rolling_node->set_left(left_right);
        if (left_right != nullptr) {
            left_right->set_father(rolling_node);
        }
        left->set_right(rolling_node);
        rolling_node->set_father(left);
        rolling_node->set_Height();
        left->set_Height();
        if (rolling_node == maxNode) {
            update_maxNode(rolling_node);
        }
    }


    void LL_rolling(const std::shared_ptr <Node<Key, Data>> &rolling_node){

        std::shared_ptr <Node<Key, Data>> left = rolling_node->get_left();
        std::shared_ptr <Node<Key, Data>> left_right = left->get_right();
        std::shared_ptr <Node<Key, Data>> father = rolling_node->get_father();


        std::shared_ptr<Node<Key, Data>> left = rolling_node->get_left();
        std::shared_ptr<Node<Key, Data>> left_right = left->get_right();
        std::shared_ptr<Node<Key, Data>> father = rolling_node->get_father();

    }

    }


    void apply_roll(const std::shared_ptr<Node<Key,Data>>& rolling_node){
        if(rolling_node->get_balance_factor() == 2){
            int left_bf = (rolling_node->get_left() == nullptr)? 0 : rolling_node->get_left()->get_balance_factor();
            if (left_bf == -1){
                LR_rolling(rolling_node);
            }
            else {
                LL_rolling(rolling_node);
            }
        }
        else if (rolling_node->get_balance_factor() == -2){
            int right_bf = (rolling_node->get_right() == nullptr)? 0 : rolling_node->get_right()->get_balance_factor();
            if (right_bf == 1){
                RL_rolling(rolling_node);

            }
            else {
                RR_rolling(rolling_node);
            }
        }

    }



    void apply_roll(const std::shared_ptr<Node<Key, Data>> &rolling_node) {
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