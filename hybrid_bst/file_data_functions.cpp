#include <iostream>
#include <string>
#include "BinaryTree.hpp"
#include "file_data_functions.hpp"

using namespace std;

// ADD; salary; department
// UPDATE; id; salary; department
// DELETE; id
// "PRINT": cout<< "P\n"; bt.printToConsole();
// "HEIGHT": cout<< "H "<< bt.getHeight()<<"\n";

extern int size_bst;

void extract_employeesdata(string line, int& id,int& salary, int& department ){
  
    unsigned long semi_index=line.find(';');
    id = stoi(line.substr(0, semi_index-0));
    
    unsigned long temp = semi_index+1; // addition of 1: to search the next semic. after the prev semic.
    semi_index = line.find(';', temp);
    salary = stoi(line.substr(temp, semi_index - temp));
    
    temp=semi_index+1;
    department = stoi(line.substr(temp, line.length()-semi_index));
}

void extract_operationsdata(string line, string& task, int& id, int& salary, int& department){
    unsigned long semi_index;
    unsigned long temp;

    if ( line.substr(0,3) == "ADD"){
        task = "ADD";
        semi_index = line.find(';', 4); //search for the second semic "ADD;__;__"
        salary = stoi(line.substr(4, semi_index - 4)); // the data between 1. and 2. semic.
        department = stoi(line.substr(semi_index+1));
    }
    else if ( line.substr(0,6) == "UPDATE"){
        task = "UPDATE";
        semi_index = line.find(';', 7);
        id = stoi(line.substr(7, semi_index - 7));
        temp=semi_index+1;
        semi_index = line.find(';', temp);
        salary = stoi(line.substr(temp, semi_index - temp));
        temp=semi_index+1;
        department = stoi(line.substr(temp));
    }
    else if (line.substr(0,6) == "DELETE"){
        task = "DELETE";
        id = stoi(line.substr(7));
    }
    else {
        cout << "Invalid operations.txt data." << endl;
    }
}

void add_employee(vector<BinaryTree*>& v, int id , int salary, int department){
    Employee* employee= new Employee(id, salary, department); //new employee created
    unsigned int i = id/5000;
    if(i > v.size()-1){
        BinaryTree* t = new BinaryTree();
        v.push_back(t);
    }
    v.at(i)->insert(employee);
}

void update_employee(vector<BinaryTree*>& v, int id , int salary, int department, int last_id){
    if(id < 1 || id > last_id ){  //employee does not exits if it is null
        cout << "ERROR: An invalid ID to update" <<"\n";
        return;
    }
    unsigned int i = id/5000;
    Employee* employee = v.at(i)->search(id); //find the employee if it exists
    if(employee==NULL){  //employee does not exits if it is null
        cout << "ERROR: An invalid ID to update" <<"\n";
        return;
    }
    employee->set_salary(salary);
    employee->set_department(department);
}

void delete_employee(vector<BinaryTree*>& v, int id, int last_id){
    if(id < 1 || id > last_id ){
        cout << "ERROR: An invalid ID to delete"<<"\n";
        return;
    }
    if(size_bst==0){ //check if there is no employee
        cout << "ERROR: There is no Employee"<<"\n";
        return;
    }
    unsigned int i = id/5000;
    v.at(i)->remove(id);
    return;
}

void print_vector(vector<BinaryTree*> v, ofstream &output_file){
    vector<BinaryTree*>::iterator i;
    for (i=v.begin(); i < v.end() ; i++){
        (*i)->printToFile(output_file);
    }
}
