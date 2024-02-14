#include <iostream>
#include <fstream>
#include <string>
#include "Employee.hpp"
#include "BinaryTree.hpp"
#include "file_data_functions.hpp"


using namespace std;

int main(int argc, char** argv) {
    
    BinaryTree* tree= new BinaryTree();
    
    int last_id=-1;
    
    fstream employeesdata;
    employeesdata.open(argv[1], ios::in);
    string line;
    getline(employeesdata, line); //pass the header line
    if(!employeesdata.is_open()){ // check if the file can be opened
        cout << "data file failed to open." << endl;
        return 1;
    }
    
    while(getline(employeesdata, line)){
        int id = 0;
        int salary = 0;
        int department = 0;
        extract_employeesdata(line, id, salary, department); // send the id salary and dep to be updated with the file data
        Employee* employee= new Employee(id,salary,department);// created an object with the given data, add it into the vector.
        tree->insert(employee);
        
        if(id>last_id){ last_id=id; }
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

        if(task== "PRINT"){
            tree->printToConsole();
        }
        else if(task =="HEIGHT"){
            cout << "H "<< tree->getHeight() << endl;
        }
        else if (task == "ADD"){
            last_id++; // increase the id because of the increase of the employee number
            add_employee(tree, last_id, task_salary, task_department);
            
        }

        else if (task == "UPDATE"){
            update_employee(tree, task_id, task_salary, task_department, last_id);
            
        }

        else if (task == "DELETE"){
            delete_employee(tree, task_id, last_id);
        }
    }
    operationsdata.close();

    ofstream solutiondata;
    solutiondata.open("binary_tree_solution.csv", ios::out);
    if(!solutiondata.is_open()){ // check if its opened
        cout << "binary_tree_solution.csv failed to open." << endl;
        return 1;
    }

    solutiondata << "Employee_ID;Salary;Department" << endl;  // add the header
    tree->printToFile(solutiondata);

    solutiondata.close();
    delete tree; //free the heap
    
    return 0;
}
