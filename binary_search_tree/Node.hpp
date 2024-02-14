#pragma once
#include "Node.hpp"
#include "Employee.hpp"

class Node{
    private:
        Employee* employee;
        Node* left;
        Node* right;
    public:
        Node(Employee*);
        ~Node();
        void set_left(Node*);
        void set_right(Node*);
        void set_employee(Employee*);
        void update_employee(int,int);
        Node* get_left();
        Node* get_right();
        Employee* get_employee();
        int get_employee_id();
        int get_employee_salary();
        int get_employee_department();
};
