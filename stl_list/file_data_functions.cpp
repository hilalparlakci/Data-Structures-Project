#include <iostream>
#include "file_data_functions.hpp"


// ADD; salary; department
// UPDATE; id; salary; department
// DELETE; id

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

void add_employee(list<Employee>& list, int id , int salary, int department){
    Employee employee(id, salary, department);
    list.push_back(employee); // add the object at the end of the list

}

void update_employee(list<Employee>& list, int id , int salary, int department, int last_id){
    if(id < 1 || id > last_id){  // id starts from 1 and cannot be bigger than the last id
        cout << "ERROR: An invalid ID to update";
        return;
    }
    else{
        for(auto & employee : list){
            if(employee.get_id() == id){  // if we find the id we change the data with the new one
                employee.set_salary(salary);
                employee.set_department(department);
                return;
            }
        }
        // there is no employee with the given id
        cout << "ERROR: An invalid ID to update";
        return;
    }
}

void delete_employee(list<Employee>& list, int id, int last_id){
    if(id < 1 || id > last_id){
        cout << "ERROR: An invalid ID to delete";
        return;
    }
    if(list.size() == 0){
        cout << "ERROR: There is no Employee";
        return;
    }

    for(auto i = list.begin(); i != list.end(); i++){
        if ((*i).get_id() == id) {
            list.erase(i);
            return; // do not continue to the function
        }
    }
    // there is no employee with the given id
    cout << "ERROR: An invalid ID to delete";
    return;
    
}


