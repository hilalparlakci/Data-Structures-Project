#pragma once
#include <iostream>
#include "Employee.hpp"
#include "DoublySkipList_Node.hpp"

using namespace std;

class DoublySkipList {
    private:
    DoublySkipList_Node* head;
    DoublySkipList_Node* tail;
    int height;
    DoublySkipList_Node* bottom_head();
    int randomLevel();
    
    public:
    DoublySkipList(int height_in);
    ~DoublySkipList();
    bool isEmpty();
    DoublySkipList_Node* find(int);
    void insert(Employee*);
    void remove(int);
    Employee* search(int);
    void dumpToFile(ofstream&);
};


