#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Employee.hpp"
#include "file_data_functions.hpp"

using namespace std;

int main(int argc, char** argv) {
    vector <Employee> employee_vector;
    
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
        add_employee(employee_vector, id ,salary, department); // created an object with the given data, add it into the vector.
        
        if(id>last_id){ last_id=id; }
        
    }
    employeesdata.close();

    employee_vector.shrink_to_fit(); // no null element in the vector
    
    fstream operationsdata;
    operationsdata.open(argv[2], ios::in);
    if(!operationsdata.is_open()){ // check if the the txt file was correctly opened.
        cout << "operations file failed to open." << endl;
        return 1;
    }
    
    while(getline(operationsdata, line)){
        string task = " ";  // ADD or UPDATE or DELETE
        int task_id = 0;
        int task_salary = 0;
        int task_department = 0;
        extract_operationsdata(line, task, task_id, task_salary, task_department); // get the task values for the operations


        if (task == "ADD"){
            last_id++; // increase the id because of the increase of the employee number
            add_employee(employee_vector, last_id, task_salary, task_department);
            
        }

        else if (task == "UPDATE"){
            update_employee(employee_vector, task_id, task_salary, task_department, last_id);
            
        }

        else if (task == "DELETE"){
            delete_employee(employee_vector, task_id, last_id);
        }
    }

    operationsdata.close();

    ostringstream temp;  // created to store the final data
    
    for (auto & employee : employee_vector){
       temp << employee.get_id() << ";" << employee.get_salary() << ";" << employee.get_department() << endl;
    }
    
    ofstream vectorsolutiondata;
    vectorsolutiondata.open("vector_solution.csv", ios::out);
    //open the file only for reading so that when we opened again, the file will come cleared from previous data.
    
    if(!vectorsolutiondata.is_open()){ // check if its opened
        cout << "vector_solution.csv failed to open." << endl;
        return 1;
    }

    vectorsolutiondata << "Employee_ID;Salary;Department" << endl;  // add the header for the solution file

    vectorsolutiondata << temp.str(); // add all the data into the file
    
    vectorsolutiondata.close();
    
    return 0;
}
