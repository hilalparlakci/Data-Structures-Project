#include "file_data_functions.hpp"
#include <iostream>


// ADD; salary; department
// UPDATE; id; salary; department
// DELETE; id

//to get id salary and dep value from the operations file
void extract_operationsdata(string line, string& task, int& id, int& salary, int& department){
    unsigned long semi_index;
        unsigned long temp;

        if ( line.substr(0,3) == "ADD"){ //"ADD;__;__"
            task = "ADD";
            semi_index = line.find(';', 4); //search for the 2. semic.
            salary = stoi(line.substr(4, semi_index - 4)); // the data between 1. and 2. semic.
            department = stoi(line.substr(semi_index+1)); // after the 2.semic.
        }
        else if ( line.substr(0,6) == "UPDATE"){ //"UPDATE;__;__;__"
            task = "UPDATE";
            semi_index = line.find(';', 7);
            id = stoi(line.substr(7, semi_index - 7));
            temp=semi_index+1; //starting point after 2.semic.
            semi_index = line.find(';', temp); //3.semic.
            salary = stoi(line.substr(temp, semi_index - temp));
            temp=semi_index+1; //starting point after 3.semic.
            department = stoi(line.substr(temp)); //after the 3.semic.
        }
        else if (line.substr(0,6) == "DELETE"){ //"DELETE;__"
            task = "DELETE";
            id = stoi(line.substr(7)); //after the 1.semic.
        }
        else {
            cout << "Invalid operations.txt data." << endl;
        }
}

// get the data from the file's line
void extract_employeesdata(string line, int& id, int& salary, int& department){ //we passed id salary and dep with null values. then we updated their value with the file data.
    unsigned long semi_index=line.find(';');
    id = stoi(line.substr(0, semi_index-0));
    unsigned long temp = semi_index+1; // addition of 1: to search the next semic. after the prev semic.
    semi_index = line.find(';', temp);
    salary = stoi(line.substr(temp, semi_index - temp));
    temp=semi_index+1;
    department = stoi(line.substr(temp, line.length()-semi_index));
}

//adding objects to the map
void add_employee(map<int, Employee*>& map, int id , int salary, int department){
    Employee* employee = new Employee(id, salary, department); // new employee
    map[employee->get_id()] = employee; //insert into the map

}

//updating the data in the map
void update_employee(map<int, Employee*>& map, int id , int salary, int department, int last_id){
    if(id < 1 || id > last_id){  //checks if the id is in the valid id interval
        cout << "ERROR: An invalid ID to update"<< "\n";
        return;
    }
    auto it = map.find(id); // wanted employee's iterator
    if(it != map.end()){ //checks if the employee is in the map
        //update the employee
        it->second->set_salary(salary);
        it->second->set_department(department);
        return;
    }
    // employee is not in the map
    cout << "ERROR: An invalid ID to update"<< "\n";
    return;
}

void delete_employee(map<int, Employee*>& map, int id, int last_id){
    if(id < 1 || id > last_id){ //checks if the id is in the valid id interval
        cout << "ERROR: An invalid ID to delete"<< "\n";
        return;
    }
    if(map.empty() == true){  // checks if the map is empty
        cout << "ERROR: There is no Employee" << "\n";
        return;
    }
    auto it = map.find(id);
    if(it != map.end()){ //checks if the employee is in the map
        map.erase(it);
        return;
    }
    cout << "ERROR: An invalid ID to delete"<< "\n";
    return;
    
}
