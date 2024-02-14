#pragma once

class Employee {
    private:
        int id;
        int salary ;
        int department ;

    public:
        Employee();
        Employee(int, int, int);
        void set_salary(int);
        void set_id(int);
        void set_department(int);
        int get_id();
        int get_salary();
        int get_department();
};
