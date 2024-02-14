#pragma once
#include <string>
#include "DoublySkipList.hpp"

void extract_operationsdata(string line, string& task, int& id, int& salary, int& department);
void extract_employeesdata(string line, int& id, int& salary, int& department);
void add_employee(DoublySkipList* skiplist, int id, int salary, int department);
void update_employee(DoublySkipList* skiplist, int id, int salary, int department, int last_id);
void delete_employee(DoublySkipList* skiplist, int id, int last_id);
