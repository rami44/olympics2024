#ifndef DATA_STRUCTURE_WET_1_BINARYTREE_H
#define DATA_STRUCTURE_WET_1_BINARYTREE_H

#include "Node.h"


    template<class Key, class Data>
    class BinaryTree{
    private:
    std::shared_ptr<Node<Key,Data>> root;
    int numOfNodes;
    std::shared_ptr<Node<Key,Data>> maxNode;
    public:
    //ctor
    BinaryTree():root(nullptr),numOfNodes(0),maxNode(nullptr){}
    virtual ~BinaryTree()=default;
    //copy and assignment operators are not valid
    BinaryTree(const BinaryTree<Key,Data>& other)=delete;
    BinaryTree& operator=(const BinaryTree<Key,Data>& other)=delete;

    std::shared_ptr<Node<Key,Data>> get_root()const{
        return root;
    }

    int get_numOfNodes()const{
        return numOfNodes;
    }

    std::shared_ptr<Node<Key,Data>> get_maxNode()const{
            return maxNode;
        }

    void update_maxNode(const std::shared_ptr<Node<Key,Data>>& curr){
        if(curr== nullptr) return;
        maxNode=curr;
        update_maxNode(curr->get_right());
    }

    bool node_exists(const std::shared_ptr<Node<Key,Data>>& node,const std::shared_ptr<Node<Key,Data>>& curr){
        Key k=node->get_key();
        if(curr== nullptr)
            return false;

        if(k==curr->get_key())
            return true;
        if(k<curr->get_key())
            return node_exists(node,curr->get_left());

        return node_exists(node,curr->get_right());

    }









};

#endif