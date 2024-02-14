#pragma once
#include <fstream>
#include "QuadruplySkipList_Node.hpp"

using namespace std;

class QuadruplySkipList{
    private:
        QuadruplySkipList_Node* head;
        QuadruplySkipList_Node* tail;
        int height;
        void set_place(QuadruplySkipList_Node*, QuadruplySkipList_Node*);
        QuadruplySkipList_Node* bottom_head();
        QuadruplySkipList_Node* bottom_tail();
        int randomLevel();
    
    public:
        QuadruplySkipList(int height_in);
        ~QuadruplySkipList();
        bool isEmpty();
        int get_last_id();
        void insert(Employee* data);
        void remove(int remove_id);
        Employee* search(int search_id);
        QuadruplySkipList_Node* find(int search_id);
        void dumpToFile(ofstream& out_file);
};
