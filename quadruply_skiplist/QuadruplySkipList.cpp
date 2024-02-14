#include <iostream>
#include <stddef.h>
#include <limits.h>
#include "QuadruplySkipList.hpp"

using namespace std;

QuadruplySkipList::QuadruplySkipList(int height_in) {
    
    this->height = height_in;
    
    // Create Employee objects for the head with -infinity and tail nodes with +infinity
    Employee* employee_head = new Employee(INT_MIN);
    Employee* employee_tail = new Employee(INT_MAX);
    
    // Create object for the head and tail nodes
    head = new QuadruplySkipList_Node(employee_head);
    tail = new QuadruplySkipList_Node(employee_tail);
    
    // Set initial links between head and tail nodes
    head->set_next(tail);
    tail->set_prev(head);
    
    QuadruplySkipList_Node* p_h = head;
    QuadruplySkipList_Node* p_t = tail;
    
    //Create head and tail nodes with lenght of height
    for (int i = 0; i < height; i++) {
        // Create head and tail nodes for the current level
        QuadruplySkipList_Node* node_head = new QuadruplySkipList_Node(employee_head);
        p_h->set_below(node_head);
        node_head->set_above(p_h);
        
        QuadruplySkipList_Node* node_tail = new QuadruplySkipList_Node(employee_tail);
        p_t->set_below(node_tail);
        node_tail->set_above(p_t);
        
        // Set next and prev links within the current level
        node_head->set_next(node_tail);
        node_tail->set_prev(node_head);
        
        p_h = p_h->get_below();
        p_t = p_t->get_below();
    }
}

QuadruplySkipList::~QuadruplySkipList() {
    
    QuadruplySkipList_Node * p = head; // Start from the top-level head node
    QuadruplySkipList_Node * temp;
    QuadruplySkipList_Node * n;
    
    // Loop through each level until the bottom level is reached
    while (p -> get_below() != NULL) {
        
        n = p->get_next(); // Move to the next node in the current level
        
        // Delete nodes in the current level
        while (n != NULL) {
            temp = n->get_next(); // Save the next node before deletion
            delete n; // Delete the current node
            n = temp; // Move to the next node
        }
        
        temp = p->get_below(); // store the next level
        delete p; // Delete the current level's head node
        p = temp; // Move to the next level's head node
    }
     
    // Delete nodes in the bottom level
    while (p != NULL) {
        temp = p->get_next(); // Save the next node before deletion
        delete p -> get_data(); // Delete the data associated with the current node
        delete p; // Delete the current node
        p = temp; // Move to the next node
    }
    
}

bool QuadruplySkipList::isEmpty(){ //checks if the skiplist is empty
    QuadruplySkipList_Node* p = this->bottom_head();
    return p->get_next()->get_data_id()==INT_MAX;
}

QuadruplySkipList_Node* QuadruplySkipList::bottom_head(){ //returns the bottom level head node
    QuadruplySkipList_Node* p = head;
    while(p->get_below()!=NULL){
        p=p->get_below();
    }
    return p;
}

QuadruplySkipList_Node* QuadruplySkipList::bottom_tail(){ //returns the bottom level tail node
    QuadruplySkipList_Node* p = tail;
    while(p->get_below()!=NULL){
        p=p->get_below();
    }
    return p;
}

int QuadruplySkipList::get_last_id(){ //get the last id of the skiplist
    return bottom_tail()->get_prev()->get_data_id();
}

QuadruplySkipList_Node* QuadruplySkipList::find(int search_id) {
    QuadruplySkipList_Node* n = head; // Start from the top-level head node
    
    // Loop through each level until the bottom level is reached
    while (n->get_below() != NULL) {
        n = n->get_below(); // Move to the next level
        
        // Traverse nodes in the current level
        while (n->get_next() != NULL) {
            if (n->get_next()->get_data_id() < search_id) {
                n = n->get_next(); // Move to the next node if its ID is smaller
            } else if (n->get_next()->get_data_id() == search_id) {
                return n->get_next(); // Found the node with the specified ID
            } else {
                break; // ID is larger, exit the loop
            }
        }
    }
    
    // Return the closest node with a smaller ID or the last node in the bottom level
    return n;
}

Employee* QuadruplySkipList::search(int search_id){ //return the employee of the given id
    QuadruplySkipList_Node* p = find(search_id);
    if(p->get_data_id()!=search_id){ //check if the id does not exits
        return NULL;
    }
    return p->get_data();
}

int QuadruplySkipList::randomLevel() { //find height of the column
    int lvl = 1;
    while (rand() % 2 == 0 && lvl < height) {
        lvl++;
    }
    return lvl;
};

void QuadruplySkipList::insert(Employee* data) {
    int id = data->get_id();
    
    // Find the position where the new employee should be inserted
    QuadruplySkipList_Node* position = find(id);
    
    // If an employee with the same ID already exists, do nothing and return
    if (position->get_data_id() == id) {
        return;
    }
    
    // Move to the next node in the bottom level
    position = position->get_next();
    
    // Create a new node for the employee data at the bottom level
    QuadruplySkipList_Node* node = new QuadruplySkipList_Node(data);
    
    // Set the links for the new node in the bottom level
    set_place(node, position);
    
    QuadruplySkipList_Node* p = node;
    
    // Randomly determine the level of the new node using coin flip
    int h = randomLevel();
    
    // Create nodes and set links for each level above the bottom level
    for (int i = 1; i < h; i++) {
        // Create a new node for the employee data at the current level
        QuadruplySkipList_Node* n = new QuadruplySkipList_Node(data);
        
        // Set above and below links for the new node at the current level
        p->set_above(n);
        n->set_below(p);
        p = n;
        
        // Move to the next node with above link or move to the next node in the bottom level
        while (true) {
            if (position->get_above() != NULL) {
                position = position->get_above();
                break;
            } else {
                position = position->get_next();
            }
        }
        
        // Set the links for the new node at the current level
        set_place(p, position);
    }
}


void QuadruplySkipList::remove(int remove_id) {
    QuadruplySkipList_Node* position = find(remove_id);
    
    // Check if the node with the specified ID exists in the skiplist
    if (position->get_data_id() != remove_id) {
        cout << "ERROR: An invalid ID to delete" << "\n";
        return;
    }
    
    // Delete the data associated with the node
    delete position->get_data();

    QuadruplySkipList_Node* p;

    // Remove nodes at all levels containing the specified ID
    while (position != NULL) {
        // Adjust the next and previous links to bypass the node being removed
        position->get_prev()->set_next(position->get_next());
        position->get_next()->set_prev(position->get_prev());

        // Save the current node to be deleted
        p = position;

        // Move to the node below in the next level
        position = position->get_below();

        // Delete the current node
        delete p;
    }
}

void QuadruplySkipList::set_place(QuadruplySkipList_Node* first, QuadruplySkipList_Node* sec){
    //set the links of the first into the place before sec
    first->set_prev(sec->get_prev());
    first->set_next(sec);
    sec->set_prev(first);
    first->get_prev()->set_next(first);
}


void QuadruplySkipList::dumpToFile(ofstream& out_file){
    QuadruplySkipList_Node* p = this->bottom_head();
    
    out_file << "Employee_ID;Salary;Department" << endl;
    while(p->get_next()->get_data_id()!=INT_MAX){ //loop through the skiplist until reaching the tail
        p=p->get_next();
        out_file << p->get_data()->get_id() << ";" << p->get_data()->get_salary() << ";" << p->get_data()->get_department()<<"\n";
    }
}
