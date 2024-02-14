#pragma once
#include <fstream>
#include "Node.hpp"
#include "Employee.hpp"

using namespace std; //size of the binarytree

class BinaryTree{
    private:
        Node* root;
    public:
        BinaryTree();
        ~BinaryTree();
        Node* get_root();
        bool isEmpty();
        void insert(Employee*);
        Node* Min(Node*);
        Node* find_parent(int);
        void remove(int);
        Employee* search(int id);
        void printToFile(ofstream&);
};
