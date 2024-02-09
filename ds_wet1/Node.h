#ifndef DATA_STRUCTURE_WET1_NODE
#define DATA_STRUCTURE_WET1_NODE

#include <memory>

template<class Key, class Data>
class Node {
private:
    const Key key;
    std::shared_ptr<Data> data;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> father;
    std::shared_ptr<Node> right;
    int height;
    int BF;

public:

    //ctor
    Node(Key key, const std::shared_ptr<Data> &d) : key(key), data(d), height(0), BF(0) {
        // Assigning null pointer using the reset function
        left = nullptr;
        right = nullptr;
        father = nullptr;
    }

    //return the key
    Key get_key() const {
        return key;
    }

    //return the data
    std::shared_ptr<Data> get_data() const {
        return data;
    }

    virtual ~Node() = default;

    Node(const Node &other) = default;

    Node &operator=(const Node &other) = delete;


    //return left son
    std::shared_ptr<Node> get_left() const {
        return left;
    }

    //update the left node
    void set_left(const std::shared_ptr<Node> &newL) {
        left = newL;
        set_Height();
    }

    //return right son
    std::shared_ptr<Node> get_right() const {
        return right;
    }

    // update the right node
    void set_right(const std::shared_ptr<Node> &newR) {
        right = newR;
        set_Height();
    }

    void set_father(const std::shared_ptr<Node> &new_father) {
        father = new_father;
        set_Height();
    }

    std::shared_ptr<Node> get_father() const {
        return father;
    }

    bool operator==(const Node<Key, Data> &other) const {
        return key == other.key;
    }

    int get_Height() const {
        return height;
    }

    int get_BF() const {
        return BF;
    }

    void set_BF() {
        int leftH = (left == nullptr) ? -1 : left->height;
        int rightH = (right == nullptr) ? -1 : right->height;
        BF = leftH - rightH;
    }

    void set_Height() {
        int leftH = (left == nullptr) ? -1 : left->height;
        int rightH = (right == nullptr) ? -1 : right->height;
        height = std::max(leftH, rightH) + 1;
    }

    test for us
};

#endif

// Path: AVLTree.h

my name is amir