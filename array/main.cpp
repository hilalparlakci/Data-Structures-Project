#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "file_data_functions.hpp"

using namespace std;

int main(int argc, char** argv) {
    
    int size_employee_array = 500000;
    //the size of the array will be set to the size of the dataset
    Employee *employee_array = new Employee[size_employee_array];
    
    fstream  employeesdata;
    employeesdata.open(argv[1], ios::in);
    string line;
    getline(employeesdata, line);
    if(!employeesdata.is_open()){
        cout << "data file failed to open." << endl;
        return 1;
    }
    
    int index = 0;
    while(getline(employeesdata, line) && index!=size_employee_array){
        int id = 0;
        int salary = 0;
        int department = 0;
        extract_employeesdata(line, id, salary, department);
        array_elementsetter(employee_array, index, id, salary, department);
        index+=1;
    }
    employeesdata.close();

    int last_id = employee_array[size_employee_array-1].get_id();

    fstream operationsdata;
    operationsdata.open(argv[2], ios::in);
    if(!operationsdata.is_open()){
        cout << "operations file failed to open." << endl;
        return 1;
    }
    
    while(getline(operationsdata, line)){
        string task = " ";
        int task_id = 0;
        int task_salary = 0;
        int task_department = 0;
        extract_operationsdata(line, task, task_id, task_salary, task_department);


        if (task == "ADD"){
            last_id++;
            employee_array = add_employee(employee_array, task_salary, task_department, size_employee_array, last_id);
            
        }

        else if (task == "UPDATE"){
            update_employee(employee_array, task_id, task_salary, task_department, size_employee_array, last_id);
            
        }

        else if (task == "DELETE"){
            employee_array = delete_employee(employee_array, task_id, size_employee_array, last_id);
        }
    }

    operationsdata.close();

    ostringstream temp;
    
    for (int i = 0; i < size_employee_array; i++){
       temp << employee_array[i].get_id() << ";" << employee_array[i].get_salary() << ";" << employee_array[i].get_department() << endl;
    }
    delete[] employee_array;

    ofstream arraysolutiondata;
    arraysolutiondata.open("array_solution.csv", ios::out);
    
    if(!arraysolutiondata.is_open()){
        cout << "array_solution.csv failed to open." << endl;
        return 1;
    }

    arraysolutiondata << "Employee_ID;Salary;Department" << endl;

    arraysolutiondata << temp.str();
    
    arraysolutiondata.close();
    
    
    return 0;
}
