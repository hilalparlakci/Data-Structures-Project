#pragma omce
#include <map>
#include <string>
#include "Employee.hpp"

using namespace std;

void extract_operationsdata(string line, string& task, int& id, int& salary, int& department);
void extract_employeesdata(string line, int& id, int& salary, int& department);
void add_employee(map<int, Employee*>& map, int id , int salary, int department);
void update_employee(map<int, Employee*>& map, int id , int salary, int department, int last_id);
void delete_employee(map<int, Employee*>& map, int id, int last_id);
