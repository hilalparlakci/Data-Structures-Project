#pragma once
#include "Employee.hpp"

class DoublySkipList_Node {
    private:
    Employee* data;
    DoublySkipList_Node* next;
    DoublySkipList_Node* below;
    public:
    DoublySkipList_Node(Employee*);
    void set_next(DoublySkipList_Node* );
    void set_below(DoublySkipList_Node* );
    void set_data(Employee* );
    DoublySkipList_Node* get_next();
    DoublySkipList_Node* get_below();
    Employee* get_data();
    int get_data_id();
};
