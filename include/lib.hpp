#ifndef LIB_HPP
#define LIB_HPP
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <commdlg.h>
#include <gdiplus/gdiplus.h>
#elif defined(__linux__)
#include <SDL3/SDL.h>
#endif
//Hash tree 
template <typename nodetype>class HashTreeNode{
        public:
            nodetype data;
            HashTreeNode <nodetype>* left;
            HashTreeNode <nodetype>* right;
            HashTreeNode(nodetype d): data(d), left(nullptr), right(nullptr) {}
            ~HashTreeNode();
    };
template <typename nodetype> class HashTree{
    HashTreeNode <nodetype>* root;
    public:
    HashTree(): root(nullptr) {}
    ~HashTree() { delete root; }
    HashTree(nodetype* arr);
    void insert(nodetype d);
    void insertHelper(HashTreeNode<nodetype>* node, nodetype d);
    friend class HashTreeNode<nodetype>;
};
typedef struct {
    int id;
    std::string data;
    std::string hash;   
}Transaction;
#endif