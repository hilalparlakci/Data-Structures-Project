#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BinaryTree.hpp"
#include "Employee.hpp"
#include "file_data_functions.hpp"

using namespace std;

int size_bst;

int main(int argc, char** argv) {
    vector<BinaryTree*> v;
    size_bst=0; //the number of employee
    
    for(int i=0; i<101; i++){
        BinaryTree* t= new BinaryTree;
        v.push_back(t);
    }
    
    fstream employeesdata;
    employeesdata.open(argv[1], ios::in);
    string line;
    getline(employeesdata, line); //pass the header line
    if(!employeesdata.is_open()){ // check if the file can be opened
        cout << "data file failed to open." << endl;
        return 0;
    }
    int last_id=-1;
    
    int id;
    int salary;
    int department;
    while(getline(employeesdata,line)){
        extract_employeesdata(line, id, salary, department);
        Employee* employee = new Employee(id,salary,department);
        unsigned int i = id/5000;
        v.at(i)->insert(employee);
        if(id > last_id){ last_id=id;}
        size_bst+=1; //increase the employee size
        }
  
    employeesdata.close();

    fstream operationsdata;
    operationsdata.open(argv[2], ios::in);
    if(!operationsdata.is_open()){ // check if the the txt file was correctly opened.
        cout << "operations file failed to open." << endl;
        return 1;
    }
    
    while(getline(operationsdata, line)){
        string task = " ";
        int task_id = 0;
        int task_salary = 0;
        int task_department = 0;
        extract_operationsdata(line, task, task_id, task_salary, task_department); // get the task values for the operations

        if (task == "ADD"){
            last_id++; // increase the id because of the increase of the employee number
            add_employee(v, last_id, task_salary, task_department);
            size_bst+=1; //made addition to the employee size
        }
        else if (task == "UPDATE"){
            update_employee(v, task_id, task_salary, task_department, last_id);
        }
        else if (task == "DELETE"){
            delete_employee(v, task_id, last_id);
        }
    }
    operationsdata.close();

    ofstream solutiondata;
    solutiondata.open("hybrid_solution.csv", ios::out);
    if(!solutiondata.is_open()){ // check if its opened
        cout << "hybrid_solution.csv failed to open." << endl;
        return 1;
    }

    solutiondata << "Employee_ID;Salary;Department" << endl;  // add the header
    print_vector(v, solutiondata);
    solutiondata.close();
    
    //free the memory
    for (auto tree : v){
        delete tree ;
    }

    return 0;
}


