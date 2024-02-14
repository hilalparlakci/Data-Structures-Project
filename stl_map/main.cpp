#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include "Employee.hpp"
#include "file_data_functions.hpp"

using namespace std;

int main(int argc, char** argv) {
    map<int, Employee*> employee_map;

    fstream employeesdata;
    employeesdata.open(argv[1], ios::in);
    string line;
    getline(employeesdata, line); //pass the header line
    if(!employeesdata.is_open()){ // check if the file can be opened
        cout << "data file failed to open." << endl;
        return 1;
    }
    int last_id=-1;
    while(getline(employeesdata, line)){
        int id = 0;
        int salary = 0;
        int department = 0;
        extract_employeesdata(line, id, salary, department); // get the employees data
        add_employee(employee_map, id ,salary, department); //  add it into the vector.
        if(id>last_id){
            last_id=id;
        }
    }
    employeesdata.close();

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
            last_id++; // increase the last id because of the addition
            add_employee(employee_map, last_id, task_salary, task_department);
        }
        else if (task == "UPDATE"){
            update_employee(employee_map, task_id, task_salary, task_department, last_id);
        }
        else if (task == "DELETE"){
            delete_employee(employee_map, task_id, last_id);
        }
    }
    operationsdata.close();

    ostringstream temp;  // created to store the final data
    map<int, Employee*>::iterator i;
    for (i = employee_map.begin(); i != employee_map.end(); i++) {
        temp <<  i->second->get_id() << ";" << i->second->get_salary()<< ";" << i->second->get_department()<< '\n';
    }
    ofstream mapsolutiondata;
    mapsolutiondata.open("map_solution.csv", ios::out);
    //open the file only for reading so that when we opened again, the file will come cleared from previous data.
    
    if(!mapsolutiondata.is_open()){ // check if its opened
        cout << "map_solution.csv failed to open." << endl;
        return 0;
    }
    mapsolutiondata << "Employee_ID;Salary;Department" << endl;  // add the header line
    mapsolutiondata << temp.str(); // add all the data into the file
    mapsolutiondata.close();
        
    for (i = employee_map.begin(); i != employee_map.end(); i++) {
        delete i->second;
    }
    return 0;
}
