#include "Node.hpp"
#include <stddef.h>

Node::Node(Employee data){ //create a node with given data
    this->data = data;
    this->next = NULL;
}

void Node::set_data(Employee data){
    this->data=data;
}

Employee Node::get_data(){
    return this->data;
}

void Node::set_next(Node* next){
    this->next=next;
}

Node* Node::get_next(){
    return this->next;
}
