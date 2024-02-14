#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "Employee.hpp"
#include "file_data_functions.hpp"


//get id salary and department from operations data
void extract_operationsdata(string line, string& task, int& id, int& salary, int& department){
    unsigned long semi_index=line.find(';'); //find the first semic.
    task = line.substr(0, semi_index-0); // first part is the one of the tasks(add,update,delete)
    unsigned long temp = semi_index+1; // the index after the first semic.

    if ( task == "ADD"){
        semi_index = line.find(';', temp); //search for the second semic from first semic index+1 (;_)
        salary = stoi(line.substr(temp, semi_index - temp)); // the data between 1. and 2. semic. the length of the substr is the difference of the prev and current index of semic.
        temp=semi_index+1; // the index after the sec semic.
        department = stoi(line.substr(temp, line.length()-semi_index)); // the data from the last semic. index+1 to the end of the line.
    }
    else if ( task == "UPDATE"){
        semi_index = line.find(';', temp);
        id = stoi(line.substr(temp, semi_index - temp));
        temp=semi_index+1;
        semi_index = line.find(';', temp);
        salary = stoi(line.substr(temp, semi_index - temp));
        temp=semi_index+1;
        department = stoi(line.substr(temp, line.length()-semi_index));
    }
    else if (task == "DELETE"){
       id = stoi(line.substr(temp));
    }
    else {
        cout << "Invalid operations.txt data." << endl;
    }
}

// get the data from the file's line
//we passed id salary and dep with null values. then we updated their value with the file data.
void extract_employeesdata(string line, int& id, int& salary, int& department){
    unsigned long semi_index=line.find(';');
    id = stoi(line.substr(0, semi_index-0));
    unsigned long temp = semi_index+1; // addition of 1: to search the next semic. after the prev semic.
    semi_index = line.find(';', temp);
    salary = stoi(line.substr(temp, semi_index - temp));
    temp=semi_index+1;
    department = stoi(line.substr(temp, line.length()-semi_index));
}

// set the employees id salary and dep
void array_elementsetter(Employee* arr, int index, int id, int salary, int department){
    arr[index].set_id(id);
    arr[index].set_salary(salary);
    arr[index].set_department(department);
}

// ADD; salary; department
// UPDATE; id; salary; department
// DELETE; id


Employee* add_employee(Employee *arr, int salary , int department, int &size, int last_id) {
    Employee* new_employee_array = new Employee[size+1];  //we make the array 1 size bigger
    for(int i = 0; i < size; i++){
        new_employee_array[i] = arr[i]; //put the old data into new data
    }
    //last element will be the addition data
    new_employee_array[size].set_id(last_id);  
    new_employee_array[size].set_salary(salary);
    new_employee_array[size].set_department(department);
    
    delete[] arr;

    size++;  // increase the size 
    return new_employee_array;
}

void update_employee(Employee* arr, int id, int salary, int department, int size , int last_id){
    if(id < 1 || id > last_id){
        cout << "ERROR: An invalid ID to update";
        return;
    }
    else{
        for(int i = 0; i < size; i++){
            if(arr[i].get_id() == id){  // if we find the id we change the date with the new one
                arr[i].set_salary(salary);
                arr[i].set_department(department);
                return;
            }
        }
        cout << "ERROR: An invalid ID to update";
        return;
    }
}

Employee* delete_employee(Employee* arr, int id, int &size, int last_id){  // passed the references 
    if(id < 1 || id > last_id ){ //must be between the current id that has been given to the employees
        cout << "ERROR: An invalid ID to delete";
        return arr;
    }
    if(size == 0){
        cout << "ERROR: There is no Employee";
        return arr;
    }
    
    bool found = false;
    for(int i = 0; i < size; i++){ //check if the id is in the array
        if (arr[i].get_id() == id) {
            found = true;
            break;
        }
    }
    if(!found){ // id is not in the array
        cout << "ERROR: An invalid ID to delete";
        return arr;
    }

    //now the id is valid we can delete the data

    size=size-1; //size decreased because of the deletion task
    Employee* new_employee_array = new Employee[size]; 
    int index=0; //write the data index = index
    for(int i = 0; i < size+1; i++){ //read for data index = i
        if (arr[i].get_id() != id) {
            new_employee_array[index] = arr[i];
            index++;  
        }
    }
    
    delete[] arr;
    return new_employee_array;
}
