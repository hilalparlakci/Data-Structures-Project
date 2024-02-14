#include <iostream>
#include <stack>
#include "Employee.hpp"
#include "BinaryTree.hpp"

extern int size_bst;

BinaryTree::BinaryTree(){
    Employee* dummy= new Employee(-1, -1, -1); //a dummy head employee
    root = new Node(dummy); //dummy head
}

BinaryTree::~BinaryTree(){
    stack<Node *> s;
    s.push(root);
    while (!s.empty()){
        Node* n = s.top();
        s.pop();
        
        //push the childs to the stack
        
        if (n->get_left() != NULL){
            s.push(n->get_left());
        }
        if (n->get_right() != NULL){
            s.push(n->get_right());
        }
        //delete the parent
        delete n;
    }
}

Node* BinaryTree::get_root(){
    return root->get_right();
}

bool BinaryTree::isEmpty(){
    return (get_root()==NULL);
}

void BinaryTree::insert(Employee* employee){
    Node* p = root; //search pointer
    while(true){
        if(employee->get_id() > p->get_employee_id()){ //the id is bigger so we continue with right
            if(p -> get_right() == NULL ){ // we came to the bottom
                p->set_right(new Node(employee));  // set the employee
                return;
            }
            p=p->get_right();
        }
        else if(employee->get_id() < p->get_employee_id()){//the id is smaller so we continue with left
            if(p -> get_left() == NULL ){ // we came to the bottom
                p->set_left(new Node(employee));
                return;
            }
            p=p->get_left();
        }
        else{ //the id already exists
            return;
        }
    }
}

void BinaryTree::printToFile(ofstream &output_file){
    //LEFT-ROOT-RIGHT
    stack<Node*> s;
    Node* n = get_root(); //start from the root
    
    while (n != NULL || !s.empty()) { //continue until to end of the path or no childeren exist
        while (n != NULL) { //continue to the bottom
            s.push(n);
            n = n->get_left(); //get the left childeren
        }
        n = s.top(); //leftmost
        s.pop(); //will be printed
        output_file << n->get_employee_id()<<";"<<n->get_employee_salary()<<";"<< n->get_employee_department()<<"\n";
        n = n->get_right(); //get the right child
    }
}

Node* BinaryTree::Min(Node* node){ //get the leftmost child
    while(node->get_left()!=NULL){
        node=node->get_left();
    }
    return node;
}

Node* BinaryTree::find_parent(int id){
    Node* p = get_root(); //search pointer
    Node* parent=root;
    
    while(p != NULL){ //search the node
        if(id < p->get_employee_id() ){
            parent=p;
            p = p->get_left(); //search the left subtree
        }
        else if( id > p->get_employee_id()){
            parent=p;
            p = p->get_right(); //search the rigth subtree
        }
        else{
            return parent;
        }
    }
    return NULL; //id does not exist
}
void BinaryTree::remove(int id) {
    Node* parent = find_parent(id);
    if(parent==NULL){
        //id does not exist
        cout << "ERROR: An invalid ID to delete"<<"\n";
        return;
    }
    // id exists
    
    Node* p; //soon to be removed node
    
    if(id < parent->get_employee_id() ){ //left child
        p=parent->get_left();
    }
    else{ //right child
        p=parent->get_right();
    }
    //p has been founded
    
    //Case1: No child
    
    if(p->get_left()==NULL && p->get_right()==NULL){
        delete p;
        
        if(id < parent->get_employee_id()){ //set the parent's child
            parent->set_left(NULL);
        }
        else{
            parent->set_right(NULL);
        }
    }
    
    // Case2: Node with only one child
    
    else if (p->get_left() == NULL) { //left child exist
        if(id < parent->get_employee_id()){//p is parent's left child
            parent->set_left(p->get_right()); //set the link between next and parent
        }
        else{ //p is parent's right child
            parent->set_right(p->get_right());
        }
        delete p; //delete the node
    }
    else if (p->get_right() == NULL) {//right child exist
        if(id < parent->get_employee_id()){
            parent->set_left(p->get_left());
        }
        else{
            parent->set_right(p->get_left());
        }
        delete p;
    }
    
    //Case3: Node with two child
    
    else{
        Node* min = Min(p->get_right()); //get right subtree's minimum
        //store the minimum employee object before the deletion call
        Employee* employee_min = new Employee(min->get_employee_id(),min->get_employee_salary(),min->get_employee_department());
        remove(min->get_employee_id());
        delete p->get_employee(); //free the heap
        p->set_employee(employee_min); //change employee with the minimum id
    }
    
    size_bst-=1; //decrease the employee size
}

//return the employee object of the given id.
Employee* BinaryTree::search(int id){
    Node* p = root->get_right();
    
    if(p == NULL){
        return NULL;
    }
    while(p!=NULL){
        if(p->get_employee_id() > id){
            p = p->get_left(); //search the left subtree
        }
        else if(p->get_employee_id() < id){
            p = p->get_right(); //search the rigth subtree
        }
        else{
            return p->get_employee();
        }
    }
    return NULL;
}
