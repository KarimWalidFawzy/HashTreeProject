#ifndef LIB_HPP
#define LIB_HPP
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <commdlg.h>
#include <gdiplus/gdiplus.h>
#elif defined(linux)
#include <SDL3/SDL.h>
#endif
//Hash tree 
template <typename nodetype>class HashTreeNode{
        public:
            nodetype data;
            HashTreeNode <nodetype>* left;
            HashTreeNode <nodetype>* right;
            HashTreeNode(nodetype d): data(d), left(nullptr), right(nullptr) {}
            void update(void);
};
 
// Unique pointer for hash tree node

// Hash tree class
template <typename nodetype> class HashTree{
    HashTreeNode <nodetype>* root;
    public:
    HashTree(): root(nullptr) {}
    HashTree(nodetype* arr);
    void insert(nodetype d);
    void update(void);
    void insertHelper(HashTreeNode<nodetype>* node, nodetype d);
    friend class HashTreeNode<nodetype>;
    HashTreeNode<nodetype>* getRoot() { return root; }
};
class Transaction {
    public:
        int id;
        char data[50];
        double amount;
        char name[50];
        Transaction(int i, const char* n, double a) : id(i), amount(a) {
            strcpy(name, n);
        }
        bool operator<(const Transaction& other) const {
            return amount < other.amount;
        }
        bool operator>(const Transaction& other) const {
            return amount > other.amount;
        }
};
HashTree<Transaction> readFileAndCreateHashTree(const char* filename);
//Hash Function for Transaction
long long int hashFunction(Transaction);
#endif