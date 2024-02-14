#pragma once
#include "Employee.hpp"

class QuadruplySkipList_Node{
    private:
        Employee* data;
        QuadruplySkipList_Node* next;
        QuadruplySkipList_Node* prev;
        QuadruplySkipList_Node* below;
        QuadruplySkipList_Node* above;
    public:
        QuadruplySkipList_Node(Employee*);
        void set_next(QuadruplySkipList_Node*);
        void set_prev(QuadruplySkipList_Node*);
        void set_below(QuadruplySkipList_Node*);
        void set_above(QuadruplySkipList_Node*);
        void set_data(Employee*);
    
        QuadruplySkipList_Node* get_next();
        QuadruplySkipList_Node* get_prev();
        QuadruplySkipList_Node* get_below();
        QuadruplySkipList_Node* get_above();
        Employee* get_data();
        int get_data_id();
};
