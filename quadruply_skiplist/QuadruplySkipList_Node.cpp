#include <stddef.h>
#include "QuadruplySkipList_Node.hpp"

using namespace std;

QuadruplySkipList_Node::QuadruplySkipList_Node(Employee* data){
    this->above=NULL;
    this->below=NULL;
    this->next=NULL;
    this->prev=NULL;
    this->data=data;
}
void QuadruplySkipList_Node::set_next(QuadruplySkipList_Node* next){
    this->next = next;
}
void QuadruplySkipList_Node::set_prev(QuadruplySkipList_Node* prev){
    this->prev = prev;
}
void QuadruplySkipList_Node::set_below(QuadruplySkipList_Node* below){
    this->below = below;
}
void QuadruplySkipList_Node::set_above(QuadruplySkipList_Node* above){
    this->above = above;
}
void QuadruplySkipList_Node::set_data(Employee* data){
    this->data =data;
}
QuadruplySkipList_Node* QuadruplySkipList_Node::get_next(){
    return this->next;
}
QuadruplySkipList_Node* QuadruplySkipList_Node::get_prev(){
    return this->prev;
}
QuadruplySkipList_Node* QuadruplySkipList_Node::get_below(){
    return this->below;
}
QuadruplySkipList_Node* QuadruplySkipList_Node::get_above(){
    return this->above;
}
Employee* QuadruplySkipList_Node::get_data(){
    return this->data;
}
int QuadruplySkipList_Node::get_data_id(){
    return this->data->get_id();
}
