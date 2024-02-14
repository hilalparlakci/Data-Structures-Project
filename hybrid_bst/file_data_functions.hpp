#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "BinaryTree.hpp"
#include "file_data_functions.hpp"

using namespace std;

void extract_employeesdata(string, int&, int&, int&);
void extract_operationsdata(string, string&, int&, int&, int&);
void add_employee(vector<BinaryTree*>&, int, int, int);
void update_employee(vector<BinaryTree*>&, int, int, int, int);
void delete_employee(vector<BinaryTree*>&, int, int);
void print_vector(vector<BinaryTree*>, ofstream&);
