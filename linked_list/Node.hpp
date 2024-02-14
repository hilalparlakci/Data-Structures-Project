#pragma once
#include "Employee.hpp"

class Node{
    private:
        Employee data;
        Node* next; 
    public:
        Node();
        Node(Employee);
        ~Node();
        void set_data(Employee);
        Employee get_data();
        void set_next(Node*);
        Node* get_next();
};
