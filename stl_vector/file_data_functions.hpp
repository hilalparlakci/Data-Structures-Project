#pragma once
#include "Employee.hpp"
#include <string>
#include <vector>

using namespace std;

void extract_operationsdata(string line, string& task, int& id, int& salary, int& department);
void extract_employeesdata(string line, int& id, int& salary, int& department);
void add_employee(vector<Employee>& vector, int id , int salary, int department);
void update_employee(vector<Employee>& vector, int id , int salary, int department, int last_id);
void delete_employee(vector<Employee>& vector, int id, int last_id);
