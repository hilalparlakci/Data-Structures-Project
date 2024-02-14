#pragma once
#include <string>
#include "Employee.hpp"

using namespace std;

void extract_operationsdata(string, string&, int&, int&, int&);
void extract_employeesdata(string, int&, int&, int&);
void array_elementsetter(Employee*, int, int, int, int);
Employee* add_employee(Employee*, int , int, int&, int);
void update_employee(Employee*, int, int, int, int , int);
Employee* delete_employee(Employee*, int, int&, int);
