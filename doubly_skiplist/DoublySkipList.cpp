#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include "DoublySkipList.hpp"

DoublySkipList::DoublySkipList(int height_in) {
    
    this->height = height_in; // Set the height of the skiplist

    // Create dummy nodes for the head and tail with minimum and maximum values
    Employee *employee_head = new Employee(INT_MIN);
    Employee *employee_tail = new Employee(INT_MAX);

    // Create head and tail nodes for the Doubly Skip List
    head = new DoublySkipList_Node(employee_head);
    tail = new DoublySkipList_Node(employee_tail);

    // Connect head to tail initially
    head->set_next(tail);

    // Initialize pointers for traversing levels of the skiplist
    DoublySkipList_Node *p_h = head;
    DoublySkipList_Node *p_t = tail;

    // Create nodes for each level
    for (int i = 0; i < height; i++) { //head and tail lenght will be equal to height
        
        // Create a new node for the head at the current level
        DoublySkipList_Node *node_head = new DoublySkipList_Node(employee_head);
        p_h->set_below(node_head);

        // Create a new node for the tail at the current level
        DoublySkipList_Node *node_tail = new DoublySkipList_Node(employee_tail);
        p_t->set_below(node_tail);

        // Connect the head and tail nodes at the current level
        node_head->set_next(node_tail);

        // Move to the next level
        p_h = p_h->get_below();
        p_t = p_t->get_below();
    }
}

DoublySkipList::~DoublySkipList() {
    // Initialize a pointer to traverse the levels of skiplist
    DoublySkipList_Node *p = head;
    DoublySkipList_Node *temp;

    // Loop through each level of the skiplist until the bottom level is reached
    while (p->get_below() != NULL) {
        // Initialize a pointer to traverse the nodes at the current level
        DoublySkipList_Node *n = p->get_next();

        // Loop through each node at the current level and delete them
        while (n != NULL) {
            temp = n->get_next();
            delete n;
            n = temp;
        }

        // Move to the next level in
        temp = p->get_below();
        delete p;
        p = temp;
    }

    // Loop through the bottom level and delete each node and its associated data
    while (p != NULL) {
        temp = p->get_next();
        delete p->get_data();
        delete p;
        p = temp;
    }
}
int DoublySkipList::randomLevel() { //find height of the column
    int lvl = 1;
    while (rand() % 2 == 0 && lvl < height) {
        lvl++;
    }
    return lvl;
};

DoublySkipList_Node * DoublySkipList::bottom_head() { //return the bottom level head
    DoublySkipList_Node * p = head;
    while (p -> get_below() != NULL) {
        p = p -> get_below();
    }
    return p;
}

bool DoublySkipList::isEmpty() { //checks if the skiplist is empty
    return bottom_head() -> get_next() -> get_data_id() == INT_MAX;
}

void DoublySkipList::dumpToFile(ofstream & out_file) {
    DoublySkipList_Node * p = this -> bottom_head();
    out_file << "Employee_ID;Salary;Department" << endl;

    while (p -> get_next() -> get_data_id() != INT_MAX) {
        p = p -> get_next();
        out_file << p -> get_data() -> get_id() << ";" << p -> get_data() -> get_salary() << ";" << p -> get_data() -> get_department() << "\n";
    }
}

DoublySkipList_Node* DoublySkipList::find(int search_id) {
    // Start from the top-left corner
    DoublySkipList_Node *p = head;

    // Traverse through each level
    while (p->get_below() != NULL) {
        p = p->get_below(); // Move down to the next level

        // Traverse horizontally on the current level until the correct position is reached
        while (p->get_next()->get_data_id() < search_id) {
            p = p->get_next();
        }

        // Check if the next node on this level has the search_id
        if (p->get_next()->get_data_id() == search_id) {
            // Return the node of the id
            return p->get_next();
        }
    }

    // If the search_id is not found return NULL
    return NULL;
}

void DoublySkipList::insert(Employee *data) {
    vector<DoublySkipList_Node *> before;
    //vector will store the nodes which the new node inserted after it for each level
    //{L4,L3,L2,L1,L0}

    // Get the id
    int search_id = data->get_id();

    // Start from the top-left corner
    DoublySkipList_Node *p = head;

    // Traverse through each level of the skiplist
    while (p->get_below() != NULL) {
        p = p->get_below(); // Move down to the next level

        // Traverse horizontally on the current level
        while (p->get_next()->get_data_id() < search_id) {
            p = p->get_next();
        }

        // Check if the next node on this level has the id
        if (p->get_next()->get_data_id() == search_id) {
            // If the Employee with the same ID already exists, do not insert
            return;
        }

        // Store the current node
        before.push_back(p);
    }

    // Determine the height of the new node randomly
    int h = randomLevel();

    // Create a new node with the given Employee data
    DoublySkipList_Node *n = new DoublySkipList_Node(data);
    DoublySkipList_Node *temp = n;

    // Build the tower structure for the new node
    for (int i = 1; i < h; i++) {
        temp->set_below(new DoublySkipList_Node(data));
        temp = temp->get_below();
    }

    // Insert the new node at each level of the Doubly Skip List
    for (auto i = before.begin() + (height - h); i < before.end(); i++) {
        n->set_next((*i)->get_next());
        (*i)->set_next(n);
        n = n->get_below();
    }
}

void DoublySkipList::remove(int remove_id) {
    // Vector to store nodes before the node to be removed on each level
    vector<DoublySkipList_Node*> before;
    //{L2,L1,L0}
    
    // Start at the head of the skip list
    DoublySkipList_Node* p = head;

    // Traverse the skip list to find the node to be removed and collect nodes before it
    while (p->get_below() != NULL) {
        p = p->get_below();
        while (p->get_next()->get_data_id() < remove_id) {
            p = p->get_next();
        }
        if (p->get_next()->get_data_id() == remove_id) {
            before.push_back(p);
        }
    }

    // If no such node is found
    if (before.size() == 0) {
        cout << "ERROR: An invalid ID to delete" << "\n";
        return;
    }

    // Retrieve the data from the first node in the 'before' vector
    Employee* employee = before.at(0)->get_next()->get_data();

    // Iterate over the nodes
    for (auto node : before) {
        // Adjust next pointers to skip over the node to be removed
        DoublySkipList_Node* temp = node->get_next();
        node->set_next(node->get_next()->get_next());

        // Delete the node
        delete temp;
    }

    // Delete the associated Employee object
    delete employee;
}

Employee* DoublySkipList::search(int search_id) {
    // Find the node with the given search_id
    DoublySkipList_Node* p = find(search_id);

    // If the node is not found, return NULL
    if (p == NULL) {
        return NULL;
    }

    // Return the employee data
    return p->get_data();
}
