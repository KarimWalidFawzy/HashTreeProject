#include "../include/lib.hpp"
long long int hashFunction(Transaction t){
    std::string str = std::to_string(t.id) + t.data;
    long long int hash = 0;
    for(int i = 0; i < str.length(); i++){
        hash = (hash * 31 + (int)str[i]) % 1000000007;
    }
    return hash;
}
template <typename nodetype>
void HashTree<nodetype>::insert(nodetype d){
    if(this->root == nullptr){
        // Create a new node and set it as the root
        this->root = new HashTreeNode<nodetype>(d);
        return;
    }
    HashTreeNode<nodetype>* current = root;
    while (true) {
        if (d < current->data) { // Or compare hashes if that's your goal
            if (current->left == nullptr) {
                current->left = new HashTreeNode(d);
                break;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = new HashTreeNode(d);
                break;
            }
            current = current->right;
        }
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
void HashTree<nodetype>::update(void){
    // Update the hash tree
    if(root == nullptr){
        return;
    }
    // Update the left and right subtrees
    // Update the root node
    root->data = hashFunction(root->data);
    // Update all nodes
    if(root->left != nullptr){
        root->left->update();
    }
    if(root->right != nullptr){
        root->right->update();
    }
}
template <typename nodetype>
void HashTreeNode<nodetype>::update(void){
    // Update the hash tree
    if(left == nullptr && right == nullptr){
        return;
    }
    // Update the left and right subtrees
    if(left != nullptr){
        left->data = hashFunction(left->data);
        left->update();
    }
    if(right != nullptr){
        right->data = hashFunction(right->data);
        right->update();
    }
    // Update the root node
    data = hashFunction(data);
}
HashTree <Transaction> readFileAndCreateHashTree(const char* filename) {
    std::ifstream fin(filename);
    std::string line;
    std::string filecontents;
    HashTree<Transaction> tree;
    while (std::getline(fin, line)) {
        filecontents += line + ";";
    }
    for (int i = 0; i < filecontents.length(); i++) {
        if(filecontents.substr(i,strlen("Transaction")) == "Transaction" || 
           filecontents.substr(i,strlen("transaction")) == "transaction")
        {
           i += strlen("Transaction");
           while (!isdigit(filecontents[i]))
           {
                i++;
           }
           int l=0;
           while (filecontents[i+l]!=':')
           {
                l++;            
           }
           std::string id = filecontents.substr(i, l);
           std::cout<<id<<" ";
           i += l+1;
           l=0;
           while (filecontents[i+l]!=':')
           {l++;}
            std::string name = filecontents.substr(i, l);
            i += l+1;
            l=0;
            while (filecontents[i+l]!=':' && filecontents[i+l]!=';')
            {l++;}
            std::cout<<name<<" ";
            std::string amount = filecontents.substr(i, l);
            i += l+1;
            std::cout<<amount<<std::endl;
            Transaction t(std::stoi(id), name.c_str(), std::stod(amount));
            tree.insert(t);
        }  
    }  
    std::cout << "File read successfully" << std::endl;
    // Implement file reading and hash tree creation logic here
    // This is a placeholder function
    return tree;
}