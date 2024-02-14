#pragma once
#include "LinkedList.hpp"
#include <string>

using namespace std;

void extract_operationsdata(string , string& , int& , int& , int& );
void extract_employeesdata(string , int& , int& , int& );
void add_employee(LinkedList& , int , int , int );
void update_employee(LinkedList& , int , int, int , int );
void delete_employee(LinkedList& , int , int );
