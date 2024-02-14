#include <stddef.h>
#include "Node.hpp"

Node::Node(Employee* employee){
    this->employee=employee;
    this->left=NULL;
    this->right=NULL;
}
Node::~Node(){
    delete employee;
    //free the heap
}
void Node::set_left(Node* left){
    this->left = left;
}
void Node::set_right(Node* right){
    this->right = right;
}
void Node::set_employee(Employee* employee){
    this->employee =employee;
}
void Node::update_employee(int salary,int department){
    employee->set_salary(salary);
    employee->set_department(department);
}
Node* Node::get_left(){
    return this->left;
}
Node* Node::get_right(){
    return this->right;
}
Employee* Node::get_employee(){
    return this->employee;
}
int Node::get_employee_id(){
    return this->employee->get_id();
}
int Node::get_employee_salary(){
    return this->employee->get_salary();
}
int Node::get_employee_department(){
    return this->employee->get_department();
}
