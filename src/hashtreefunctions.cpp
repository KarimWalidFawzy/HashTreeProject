#include "../include/lib.hpp"
long long int hashFunction(Transaction t){
    std::string str = std::to_string(t.id) + t.data + t.hash;
    long long int hash = 0;
    for(int i = 0; i < str.length(); i++){
        hash = (hash * 31 + str[i]) % 1000000007;
    }
    return hash;
}
template <typename nodetype>
void HashTree<nodetype>::insert(nodetype d){
    if(root == nullptr){
        root = new HashTreeNode<nodetype>(d);
    }else{
        insertHelper(root, d);
    }
}
template <typename nodetype> 
void HashTree<nodetype>::insertHelper(HashTreeNode<nodetype>* node, nodetype d){
    if(d < node->data){
        if(node->left == nullptr){
            node->left = new HashTreeNode(d);
        }else{
            insertHelper(node->left, d);
        }
    }else{
        if(node->right == nullptr){
            node->right = new HashTreeNode(d);
        }else{
            insertHelper(node->right, d);
        }
    }
}
template <typename nodetype>
HashTree<nodetype>::HashTree(nodetype* arr){
    root = nullptr;
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        insert(arr[i]);
    }
}
template <typename nodetype>
HashTreeNode<nodetype>::~HashTreeNode(){
    delete left;
    delete right;
}