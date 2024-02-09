#ifndef DATA_STRUCTURE_WET_1_BINARYTREE_H
#define DATA_STRUCTURE_WET_1_BINARYTREE_H

#include "Node.h"


template <class Key, class Data>
class BinaryTree{
    Node<Key,Data>* root ;
    int num_of_nodes;
    Node<Key,Data>* MaxNode;

public:

    BinaryTree();

    ~BinaryTree() = default;

    void DestroyTree();

    void EmptyTree();

    BinaryTree(const BinaryTree<Key,Data>&) = delete ;

    const BinaryTree& operator=( const BinaryTree<Key,Data>&) = delete;

    Node<Key,Data>* get_root() const;

    //setterrrrrr

    int get_num_of_nodes() const;

    void update_MaxNode();

    Node<Key,Data>* getMaxNode();


    bool add_node(Node<Key,Data>* new_node);

    Node<Key,Data>* delete_node_binary( Node<Key,Data>* to_delete);

    Node<Key,Data>* delete_emptynode_binary( Node<Key, Data>* to_delete);                                               ///// cutout

    Node<Key,Data>* find_node(Key key);

    void update_tree_stats(Node<Key,Data>* leaf);
    void update_tree_add(Node<Key,Data>* leaf);

    void LL_rolling( Node<Key,Data>* to_change );
    void LR_rolling( Node<Key,Data>* to_change );
    void RL_rolling( Node<Key,Data>* to_change );
    void RR_rolling( Node<Key,Data>* to_change );

    void apply_roll(Node<Key, Data>* rolling_node);

    void switch_node(Node<Key,Data>* node1 , Node<Key,Data>* node2);

    Node<Key,Data>* findNextNode( Node<Key,Data>* current_node);

    bool Delete(Key key);

    void removeThenInsert(Data data , Key& key , Key& oldKey);

    template<class Operation>
    void inOrder(Operation functionPointer, Node<Key,Data>* node);

    template<class Operation>
    void postOrder(Operation functionPointer, Node<Key,Data>* node);

    template<class Operation>
    void preOrder(Operation functionPointer, Node<Key,Data>* node);

    template<class Operation>
    void RL_inOrder(Operation& functionPointer, Node<Key,Data>* node);

};

template <class Key, class Data>
BinaryTree<Key,Data>::BinaryTree() : root(nullptr), num_of_nodes(0) , MaxNode(nullptr){}


template <class Key, class Data>
void BinaryTree<Key,Data>::DestroyTree(){
    Delete_Node<Key,Data> delete_operation;
    postOrder<Delete_Node<Key,Data>>(delete_operation, root);
}

/////////////
template <class Key, class Data>
void BinaryTree<Key,Data>::EmptyTree(){
    DeleteEmptyNodes<Key,Data> delete_nodes;
    postOrder<DeleteEmptyNodes<Key,Data>>(delete_nodes, root);
}
////////////

template <class Key, class Data>
Node<Key,Data>* BinaryTree<Key,Data>::get_root()const {
    return root;
}


template <class Key, class Data>
void BinaryTree<Key,Data>::update_MaxNode() {
    if(root == nullptr) return;
    Node<Key,Data>* current = root;
    while(current->get_right() != nullptr){
        current = current->get_right();
    }

    MaxNode = current;
}


template <class Key, class Data>
Node<Key,Data>* BinaryTree<Key,Data>::getMaxNode(){
    return MaxNode;
}


template <class Key, class Data>
int BinaryTree<Key,Data>::get_num_of_nodes() const{
    return num_of_nodes;
}


template <class Key, class Data>
bool BinaryTree<Key,Data>::add_node(Node<Key,Data>* new_node){
    Node<Key,Data>* current_node = root;
    if(current_node == nullptr) {
        root = new_node ;
        root->set_father(nullptr);
        update_tree_add(new_node);
        num_of_nodes++;
        update_MaxNode();
        return true;
    }
    while(current_node->get_right() != nullptr || current_node->get_left() != nullptr ){
        if (*new_node == *current_node) {
            return false;
        }
        else if (*new_node < *current_node ) {
            if(current_node->get_left() == nullptr){
                new_node->set_father(current_node);
                current_node->set_left(new_node);
                update_tree_add(new_node);
                num_of_nodes++;
                update_MaxNode();
                return true;
            }
            current_node = current_node->get_left();
        }
        else{
            if (current_node->get_right() == nullptr){
                new_node->set_father(current_node);
                current_node->set_right(new_node);
                update_tree_add(new_node);
                num_of_nodes++;
                update_MaxNode();
                return true;
            }
            current_node = current_node->get_right();
        }
    }

    if (*new_node == *current_node){
        return false;
    }
    else if (*new_node < *current_node){
        new_node->set_father(current_node);
        current_node->set_left(new_node);
        update_tree_add(new_node);
        num_of_nodes++;
        update_MaxNode();
        return true;
    }
    else {
        new_node->set_father(current_node);
        current_node->set_right(new_node);
        update_tree_add(new_node);
        num_of_nodes++;
        update_MaxNode();
        return true;
    }


}



template <class Key, class Data>
Node<Key,Data>* BinaryTree<Key,Data>::find_node(Key key){
    Node<Key,Data>* current_node = root;
    if(current_node == nullptr){
        return nullptr;
    }

    while(current_node != nullptr){
        if(current_node->get_key() == key){
            return current_node;
        }
        else if(current_node->get_key() > key){
            current_node = current_node->get_left();
        }
        else{
            current_node = current_node->get_right();
        }
    }

    return nullptr;
}

template <class Key, class Data>
void BinaryTree<Key,Data>::update_tree_stats(Node<Key,Data>* leaf){
    Node<Key,Data>* current_node = leaf;
    while(current_node != nullptr) {
        current_node->set_height();
        current_node->set_balance_factor();
        current_node = current_node->get_father();
    }

}


template <class Key, class Data>
void BinaryTree<Key,Data>::update_tree_add(Node<Key,Data>* leaf){
    update_tree_stats(leaf);
    Node<Key,Data>* current_node = leaf;
    while( current_node != nullptr &&(current_node->get_balance_factor() != 2 &&
                                      current_node->get_balance_factor() != -2) ){
        current_node = current_node->get_father();
    }
    if(current_node == nullptr) return;
    apply_roll(current_node);
    update_tree_stats(leaf);
}


template <class Key, class Data>
void BinaryTree<Key,Data>::apply_roll(Node<Key,Data>* rolling_node){
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

template <class Key, class Data>
void BinaryTree<Key,Data>::LL_rolling(Node<Key, Data>* to_change)  {
    Node<Key,Data>* root_father = to_change->get_father();
    Node<Key,Data>* new_root = to_change->get_left();
    if (root_father != nullptr){
        if ((root_father->get_left()!= nullptr)&&(*(root_father->get_left()) == *to_change)){
            root_father->set_left(new_root);
        }
        else {
            root_father->set_right(new_root);
        }

        new_root->set_father(root_father);
    }
    else{
        new_root->set_father(nullptr);
        root = new_root;
    }

    to_change->set_father(new_root);
    to_change->set_left(new_root->get_right());
    if(to_change->get_left() != nullptr) to_change->get_left()->set_father(to_change);
    new_root->set_right(to_change);

    to_change->set_height();
    to_change->set_balance_factor();
    new_root->set_balance_factor();
    new_root->set_height();

}

template <class Key, class Data>
void BinaryTree<Key,Data>::LR_rolling(Node<Key, Data>* to_change) {
    Node<Key,Data>* root_father = to_change->get_father();
    Node<Key,Data>* left_son_of_new_root = to_change->get_left();
    Node<Key,Data>* new_root = left_son_of_new_root->get_right();

    if (root_father != nullptr){
        if ((root_father->get_left()!= nullptr)&&(*(root_father->get_left()) == *to_change)){
            root_father->set_left(new_root);
        }
        else {
            root_father->set_right(new_root);
        }

        new_root->set_father(root_father);
    }
    else{
        new_root->set_father(nullptr);
        root = new_root;
    }

    to_change->set_left(new_root->get_right());
    if(to_change->get_left() != nullptr) to_change->get_left()->set_father(to_change);

    left_son_of_new_root->set_right(new_root->get_left());
    if(left_son_of_new_root->get_right()!= nullptr) left_son_of_new_root->get_right()->set_father(left_son_of_new_root);

    new_root->set_right(to_change);
    new_root->set_left(left_son_of_new_root);
    new_root->get_left()->set_father(new_root);
    new_root->get_right()->set_father(new_root);

    to_change->set_height();
    to_change->set_balance_factor();
    left_son_of_new_root->set_height();
    left_son_of_new_root->set_balance_factor();
    new_root->set_balance_factor();
    new_root->set_height();

}

template <class Key, class Data>
void BinaryTree<Key,Data>::RL_rolling(Node<Key, Data>* to_change) {
    Node<Key,Data>* root_father = to_change->get_father();
    Node<Key,Data>* right_son_of_new_root = to_change->get_right();
    Node<Key,Data>* new_root = right_son_of_new_root->get_left();

    if (root_father != nullptr){
        if ((root_father->get_left()!= nullptr)&&(*(root_father->get_left()) == *to_change)){
            root_father->set_left(new_root);
        }
        else {
            root_father->set_right(new_root);
        }

        new_root->set_father(root_father);
    }
    else{
        new_root->set_father(nullptr);
        root = new_root;
    }

    to_change->set_right(new_root->get_left());
    if(to_change->get_right() != nullptr) to_change->get_right()->set_father(to_change);

    right_son_of_new_root->set_left(new_root->get_right());
    if(right_son_of_new_root->get_left() != nullptr) right_son_of_new_root->get_left()->set_father(right_son_of_new_root);

    new_root->set_right(right_son_of_new_root);
    new_root->set_left(to_change);
    new_root->get_left()->set_father(new_root);
    new_root->get_right()->set_father(new_root);

    to_change->set_height();
    to_change->set_balance_factor();
    right_son_of_new_root->set_height();
    right_son_of_new_root->set_balance_factor();
    new_root->set_balance_factor();
    new_root->set_height();
}

template <class Key, class Data>
void BinaryTree<Key,Data>::RR_rolling(Node<Key, Data>* to_change) {
    Node<Key,Data>* root_father = to_change->get_father();
    Node<Key,Data>* new_root = to_change->get_right();
    if (root_father != nullptr){
        if ((root_father->get_left()!= nullptr)&&(*(root_father->get_left()) == *to_change)){
            root_father->set_left(new_root);
        }
        else {
            root_father->set_right(new_root);
        }

        new_root->set_father(root_father);
    }
    else{
        new_root->set_father(nullptr);
        root = new_root;
    }

    to_change->set_father(new_root);
    to_change->set_right(new_root->get_left());
    if(to_change->get_right() != nullptr) to_change->get_right()->set_father(to_change);
    new_root->set_left(to_change);

    to_change->set_height();
    to_change->set_balance_factor();
    new_root->set_balance_factor();
    new_root->set_height();

}


template <class Key, class Data>
template<class Operation>
void BinaryTree<Key,Data>::inOrder(Operation functionPointer, Node<Key,Data>* node){
    if(node == nullptr) return;
    Node<Key,Data>* left_son = node->get_left();
    Node<Key,Data>* right_son = node->get_right();
    inOrder(functionPointer, left_son);
    functionPointer(node);
    inOrder(functionPointer, right_son);
}

template <class Key, class Data>
template<class Operation>
void BinaryTree<Key,Data>::postOrder(Operation functionPointer, Node<Key,Data>* node){
    if(node == nullptr) return;
    postOrder(functionPointer, node->get_left());
    postOrder(functionPointer, node->get_right());
    functionPointer(node);
}

template <class Key, class Data>
template<class Operation>
void BinaryTree<Key,Data>::preOrder(Operation functionPointer, Node<Key,Data>* node){
    if(node == nullptr) return;
    Node<Key,Data>* left_son = node->get_left();
    Node<Key,Data>* right_son = node->get_right();
    functionPointer(node);
    preOrder(functionPointer, left_son);
    preOrder(functionPointer, right_son);
}

template<class Key , class Data>
template<class Operation>
void BinaryTree<Key,Data>::RL_inOrder(Operation& functionPointer, Node<Key,Data>* node){
    if(node == nullptr) return;
    Node<Key,Data>* left_son = node->get_left();
    Node<Key,Data>* right_son = node->get_right();
    RL_inOrder(functionPointer, right_son);
    functionPointer(node);
    RL_inOrder(functionPointer, left_son);
}


template <class Key, class Data>
Node<Key,Data>* BinaryTree<Key,Data>::delete_node_binary( Node<Key, Data>* to_delete) {
    // V is a leaf

    if(to_delete->get_right() == nullptr && to_delete->get_left() == nullptr){
        if(to_delete->get_father() == nullptr) {
            root = nullptr;
            delete to_delete;
            return nullptr;
        }
        else if(to_delete->get_father()->get_right() == to_delete){
            to_delete->get_father()->set_right(nullptr);
            Node<Key, Data>* father = to_delete->get_father();
            delete to_delete;
            return father;
        }
        else{
            to_delete->get_father()->set_left(nullptr);
            Node<Key, Data>* father = to_delete->get_father();
            delete to_delete;
            return father;
        }
    }

        // V has one son
    else if(to_delete->get_left() == nullptr){
        if(to_delete->get_father() == nullptr) {
            root = to_delete->get_right();
            root->set_father(nullptr);
            delete to_delete;
            return nullptr;
        }
        else{
            if(to_delete->get_father()->get_right() == to_delete){
                Node<Key, Data>* father = to_delete->get_father();
                father->set_right(to_delete->get_right());
                to_delete->get_right()->set_father(father);
                delete to_delete;
                return father;
            }
            else{
                Node<Key, Data>* father = to_delete->get_father();
                father->set_left(to_delete->get_right());
                father->get_left()->set_father(father);
                delete to_delete;
                return father;
            }
        }
    }

    else if(to_delete->get_right() == nullptr){
        if(to_delete->get_father() == nullptr) {
            root = to_delete->get_left();
            root->set_father(nullptr);
            delete to_delete;
            return nullptr;
        }
        else{
            if(to_delete->get_father()->get_right() == to_delete){
                Node<Key, Data>* father = to_delete->get_father();
                father->set_right(to_delete->get_left());
                father->get_right()->set_father(father);
                delete to_delete;
                return father;
            }
            else{
                Node<Key, Data>* father = to_delete->get_father();
                father->set_left(to_delete->get_left());
                delete to_delete;
                return father;
            }
        }
    }

    // V has two sons
    Node<Key,Data>* next_inorder = findNextNode(to_delete);
    switch_node(to_delete, next_inorder);
    return delete_node_binary(next_inorder);
}


template <class Key, class Data>
Node<Key,Data>* BinaryTree<Key,Data>::findNextNode(Node<Key, Data> *current_node) {

    Node<Key,Data>* tmp = current_node;

    if(root == nullptr || current_node == nullptr) return nullptr;

    if(tmp->get_right() != nullptr){
        tmp = tmp->get_right();
        while(tmp->get_left() != nullptr){
            tmp = tmp->get_left();
        }
        return tmp;
    }

    else{
        while(  tmp->get_father() != nullptr && tmp->get_father()->get_right() == tmp){
            tmp = tmp->get_father();
        }

        if(tmp->get_father() == nullptr) return nullptr;
        else{
            return tmp->get_father();
        }
    }
}


template <class Key, class Data>
void BinaryTree<Key,Data>::switch_node(Node<Key,Data>* node1 , Node<Key,Data>* node2){
    Key key1 = node1->get_key();
    Key key2 = node2->get_key();
    std::shared_ptr<Data> data1 = node1->get_data();
    std::shared_ptr<Data> data2 = node2->get_data();
    node1->set_key(key2);
    node1->set_data(data2);
    node2->set_key(key1);
    node2->set_data(data1);

}


template <class Key, class Data>
bool BinaryTree<Key,Data>::Delete(Key key) {
    Node<Key, Data> *to_delete = find_node(key);
    if (to_delete == nullptr) return false;
    num_of_nodes--;
    Node<Key, Data> *father_of_delete = delete_node_binary(to_delete);
    if (father_of_delete == nullptr){
        update_MaxNode();
        return true;
    }
    Node<Key, Data> *current = father_of_delete;
    int old_height = father_of_delete->get_height();
    // Node<int,int>* father = father_of_delete;
    while (current != nullptr) {
        current->set_height();
        current->set_balance_factor();
        apply_roll(current);
        if (current->get_height() == old_height) break;
        current = current->get_father();
        if (current == nullptr) break;
        old_height = current->get_height();
    }
    update_tree_stats(father_of_delete);
    update_MaxNode();
    return true;
}



template <class Key, class Data>
Node<Key,Data>* BinaryTree<Key,Data>::delete_emptynode_binary( Node<Key, Data>* to_delete) {
    // V is a leaf
    DeleteEmptyNodes<Key,Data> delete_opt;
    if (to_delete->get_right() == nullptr && to_delete->get_left() == nullptr) {
        if (to_delete->get_father() == nullptr) {
            root = nullptr;
            delete_opt(to_delete);
            return nullptr;
        } else if (to_delete->get_father()->get_right() == to_delete) {
            to_delete->get_father()->set_right(nullptr);
            Node<Key, Data> *father = to_delete->get_father();
            delete_opt(to_delete);
            return father;
        } else {
            to_delete->get_father()->set_left(nullptr);
            Node<Key, Data> *father = to_delete->get_father();
            delete_opt(to_delete);
            return father;
        }
    }

        // V has one son
    else if (to_delete->get_left() == nullptr) {
        if (to_delete->get_father() == nullptr) {
            root = to_delete->get_right();
            delete_opt(to_delete);
            return nullptr;
        } else {
            if (to_delete->get_father()->get_right() == to_delete) {
                Node<Key, Data> *father = to_delete->get_father();
                father->set_right(to_delete->get_right());
                to_delete->get_right()->set_father(father);
                delete_opt(to_delete);
                return father;
            } else {
                Node<Key, Data> *father = to_delete->get_father();
                father->set_left(to_delete->get_right());
                father->get_left()->set_father(father);
                delete_opt(to_delete);
                return father;
            }
        }
    }
    else if(to_delete->get_right() == nullptr){
        if(to_delete->get_father() == nullptr) {
            root = to_delete->get_left();
            delete_opt(to_delete);
            return nullptr;
        }
        else{
            if(to_delete->get_father()->get_right() == to_delete){
                Node<Key, Data>* father = to_delete->get_father();
                father->set_right(to_delete->get_left());
                father->get_right()->set_father(father);
                delete_opt(to_delete);
                return father;
            }
            else{
                Node<Key, Data>* father = to_delete->get_father();
                father->set_left(to_delete->get_left());
                delete_opt(to_delete);
                return father;
            }
        }
    }

    // V has two sons
    Node<Key,Data>* next_inorder = findNextNode(to_delete);
    switch_node(to_delete, next_inorder);
    return delete_emptynode_binary(next_inorder);


}

template <class Key, class Data>
void BinaryTree<Key,Data>::removeThenInsert(Data data , Key& key , Key& oldKey){

    Node<Key,Data>* to_add = new Node<Key,Data>(key , std::make_shared<Data>(data));

    Delete(oldKey);
    add_node(to_add);
}









#endif //DATA_STRUCTURE_WET_1_BINARYTREE_H