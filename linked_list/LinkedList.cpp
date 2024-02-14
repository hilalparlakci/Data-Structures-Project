#include "LinkedList.hpp"
#include <iostream>

using namespace std;

LinkedList::LinkedList(){
    head=NULL;
    tail=NULL;
    //when thee linked list created, it is empty
}

LinkedList::~LinkedList(){
    Node* current = head;
    while( current != NULL ) {
        Node* next = current->get_next();  //points to the next node
        delete current;  //get rid of the current
        current = next;
        }
}


bool LinkedList::contains(int id){  //returns true if the given id is in the linkedlist
    Node* p=head;
    while(p!=NULL && p->get_data().get_id()!=id) {
        p=p->get_next(); // go to the next node
    }
    if(p==NULL){  //the linkedlist finished
        return false;
    }
    else{
        return true;
    }
}


Employee LinkedList::get_first(){ // returns the first object of the linkedlist
     Node* p = head;
     return p->get_data();
}

Employee LinkedList::get_last(){  // returns the last object of the linkedlist
     Node* p = tail;
     return p->get_data();
}


Node* LinkedList::get_prev(int id){  //return the previous node of the given id.
    Node* p = head;

    if(id == head->get_data().get_id())
        return NULL;
    else{
        while(p->get_next()){
            if(p->get_next()->get_data().get_id()==id){ // if the id founded
                return p; //return current node that has the id data in the next of it.
            }
            p=p->get_next();
        }
        return p;
    }

}

Node* LinkedList::find(int id){ // return the node of the given id if there is one.
    Node* p=head;
    while(p!=NULL && p->get_data().get_id()!=id) {
        p=p->get_next(); // go to the next node
    }
    if (p == NULL) { //travesing has finished
        return NULL;
    }
    else {
        return p;
    }
    
}


bool LinkedList::isEmpty(){  // checks if the linkedlist is empty
    if(head==NULL){
        return true;
    }
    else{
        return false;
    }
}

void LinkedList::addback_node(Employee employee){
    Node* new_node = new Node(employee);
    if(head==NULL){ //the linkedlist is empty  new element will be both the head and the tail
        head=new_node;
        tail=new_node;
        return;
    }
    else{
        tail->set_next(new_node); //add the node after the tail
        tail=new_node; //new node will be the tail now
        return;
    }
}

void LinkedList::update_linkedlist_node(Node* node, Employee data) {
        node->set_data(data); //updated the node's data
    }

void LinkedList::remove_node(int id){
    Node* prev = this->get_prev(id);
   
    if(prev==NULL){  //the node that will be removed is the head.
        Node* old_head=head;  //store the old data
        head=head->get_next();
        old_head->set_next(NULL); //remove the link between
        delete old_head; //removed
    }

    else if(prev->get_next()==tail){ //the node is the tail
        tail=prev; //set the new tail
        delete tail->get_next();
        tail->set_next(NULL);
    }

    else if(prev == tail){
        cout<<"No element with given id"<<endl;
    }

    else{
        Node* cur = prev->get_next();
        prev->set_next(cur->get_next());
        cur->set_next(NULL);
        delete cur;
    }
}

void LinkedList::copy(ostringstream& temp){  // it will copy the linked list to the given ostrnigstream
    for(Node *p = head; p; p = p->get_next()) {
        auto employee = p->get_data();
        temp << employee.get_id() << ";" << employee.get_salary() << ";" << employee.get_department() << endl;
    }
}
