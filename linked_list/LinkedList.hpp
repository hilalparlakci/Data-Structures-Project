#pragma once
#include <sstream>
#include "Node.hpp"

using namespace std;

class LinkedList{
    private:
        Node* head; //the beginning of the linkedlist
        Node* tail;  //the end of the linkedlist
        Node* get_prev(int);  //search the node of given id and return the previous node

    public:
        LinkedList();
        ~LinkedList();
        void addback_node(Employee);  //add a new node at the back with given Employee object
        void update_linkedlist_node(Node* , Employee);  //update the given node with given data
        void remove_node(int);  // remove the node of given id's object
        bool contains(int);  // checks if the data of given id is present in the linkedlist
        bool isEmpty();    // checks if the linkedlist is empty
        Node* find(int);   //find and return the node of given id
        Employee get_first();  //get the first node's data
        Employee get_last();   //get the last node's data
        Employee get_node(int);  // get the node of the given id
        void copy(ostringstream&);  // copy the data of the linkedlist to the ostringstream
        
};
