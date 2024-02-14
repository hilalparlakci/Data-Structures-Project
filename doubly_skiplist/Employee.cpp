#include "Employee.hpp"

Employee::Employee(int id) { //create an employee object with given data
    this -> id = id;
}

Employee::Employee(int id, int salary, int department) { //create an employee object with given data
    this -> id = id;
    this -> salary = salary;
    this -> department = department;
}
void Employee::set_salary(int salary) {
    this -> salary = salary;
}
void Employee::set_id(int id) {
    this -> id = id;
}
void Employee::set_department(int department) {
    this -> department = department;
}
int Employee::get_id() {
    return id;
}
int Employee::get_salary() {
    return salary;
}
int Employee::get_department() {
    return department;
}
