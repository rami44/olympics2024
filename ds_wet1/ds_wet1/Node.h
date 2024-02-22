#ifndef DATA_STRUCTURE_WET1_NODE
#define DATA_STRUCTURE_WET1_NODE

#include <memory>

template<class Key, class Data>
class Node {
private:
    Key key;
    std::shared_ptr<Data> data;
    Node<Key,Data>* left;
    Node<Key,Data>* right;
    Node<Key, Data>* father;
    int height;
    int BF;

public:
    Node()=delete;
    //ctor
    Node(Key key, const std::shared_ptr<Data> &d) :key(key),data(d),left(nullptr),right(nullptr)
    ,father(nullptr), height(0), BF(0) {}


    void operator()(Node<Key,Data>* node_to_be_deleted){
        delete node_to_be_deleted;
    }

    //return the key
    Key get_key() const {
        return key;
    }

    void set_key(Key new_key) {
        key = new_key;
    }

    void set_data(std::shared_ptr<Data> new_data){
        data = new_data;
    }

    //return the data
    const std::shared_ptr<Data> get_data() const {
        return data;
    }

    std::shared_ptr<Data> get_data()  {
        return data;
    }

    virtual ~Node()=default;

    Node(const Node &other) = delete;

    Node &operator=(const Node &other) = delete;


    Node<Key, Data>* get_left() {
        return left;
    }


    Node<Key, Data>* get_right() {
        return right;
    }


    Node<Key, Data>* get_father() {
        return father;
    }


        //return left son
    Node<Key,Data>* get_left() const {
        return left;
    }

    //update the left node
    void set_left(Node<Key,Data>* newL) {
        left = newL;
        set_Height();
    }

    //return right son
    Node<Key,Data>* get_right() const {
        return right;
    }

    // update the right node
    void set_right(Node<Key,Data>* newR) {
        right = newR;
        set_Height();
    }

    void set_father(Node<Key,Data>* new_father) {
        father = new_father;
        set_Height();
    }

    Node<Key,Data>* get_father() const {
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


};

#endif

// Path: AVLTree.h

