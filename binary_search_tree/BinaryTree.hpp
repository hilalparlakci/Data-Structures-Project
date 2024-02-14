#pragma once
#include <fstream>
#include "Node.hpp"

using namespace std;

class BinaryTree{
    private:
        Node* root;
    public:
        BinaryTree();
        ~BinaryTree();
        Node* get_root();
        bool isEmpty();
        void insert(Employee*);
        void preorder_traverse(Node*);
        Node* Min(Node*);
        Node* find_parent(int);
        void remove(int);
        Employee* search(int id);
        int getHeight();
        int getHeight_Recursive(Node*);
        void printToFile(ofstream&);
        void printToConsole();
};

