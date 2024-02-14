#include <fstream>
#include <iostream>
#include <sstream>
#include "Employee.hpp"
#include "LinkedList.hpp"
#include "file_data_functions.hpp"

using namespace std;

int main(int argc, char** argv) {

    LinkedList employee_linkedlist;

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
        add_employee(employee_linkedlist, id ,salary, department); // created an object with the given data, add it into the vector.
        
    }
    employeesdata.close();


    int last_id = employee_linkedlist.get_last().get_id(); // last object's id

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
            add_employee(employee_linkedlist, last_id, task_salary, task_department);
            
        }

        else if (task == "UPDATE"){
            update_employee(employee_linkedlist, task_id, task_salary, task_department, last_id);
            
        }

        else if (task == "DELETE"){
            delete_employee(employee_linkedlist, task_id, last_id);
        }
    }

    operationsdata.close();

    ostringstream temp;  // created to store the final data

    employee_linkedlist.copy(temp);

    ofstream linkedlistsolutiondata;
    linkedlistsolutiondata.open("linked_list_solution.csv", ios::out);
    
    if(!linkedlistsolutiondata.is_open()){ // check if its opened
        cout << "linked_list_solution.csv failed to open." << endl;
        return 1;
    }

    linkedlistsolutiondata << "Employee_ID;Salary;Department" << endl;  // add the header

    linkedlistsolutiondata << temp.str(); // add all the data into the file
    
    linkedlistsolutiondata.close();

    return 0;
}
