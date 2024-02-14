#include "DoublySkipList_Node.hpp"
#include <stddef.h>

DoublySkipList_Node::DoublySkipList_Node(Employee * data) {
    this -> below = NULL;
    this -> next = NULL;
    this -> data = data;
}
void DoublySkipList_Node::set_next(DoublySkipList_Node * next) {
    this -> next = next;
}
void DoublySkipList_Node::set_below(DoublySkipList_Node * below) {
    this -> below = below;
}
void DoublySkipList_Node::set_data(Employee * data) {
    this -> data = data;
}
DoublySkipList_Node * DoublySkipList_Node::get_next() {
    return this -> next;
}
DoublySkipList_Node * DoublySkipList_Node::get_below() {
    return this -> below;
}
Employee * DoublySkipList_Node::get_data() {
    return this -> data;
}
int DoublySkipList_Node::get_data_id() {
    return this -> data -> get_id();
}
