#pragma once
#include <string>

using namespace std;

extern int last_id; 

bool isempty(const string& filename);
void retrieve_last_id(const string& filename);
string extract_method(const string& line);
void extract_add_parameters(const string& line, string& department, string& salary);
void extract_update_parameters(const string& line, string& task_id, string& department, string& salary);
void extract_delete_parameters(const string& line, string& task_id);
void add(const string& filename, string& department, string& salary);
void update(const string& filename, string& task_id, string& department, string& salary);
void delete_(const string& filename, string& task_id);
