#include "file_functions.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


int last_id = 0;

bool isempty(const string& filename) {  // is file empty
    ifstream file;
    file.open(filename);
    
    string line = "";
    getline(file, line);
    
    bool result = file.eof() && (line == "" || line == "Employee_ID;Salary;Department");
    
    file.close();
    return result;
}

void retrieve_last_id(const string& filename) {
    fstream input;
    input.open(filename, ios::in);
    
    string line;
    string prev_line;
    while (getline(input, line)) {  //get the line
        if (line != "")
            prev_line = line;
    }
    input.close();
    
    int current_last_id = 0;
    if (prev_line != "" && prev_line != "Employee_ID;Salary;Department") {
        current_last_id = stoi(prev_line.substr(0, prev_line.find(";")));
    }
    last_id = current_last_id > last_id ? current_last_id : last_id;
}

// use it to get the task from operations.txt
string extract_method(const string& line) {
    string method = "";
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == ';') {
            break;
        }
        method = method + line[i];
    }
    return method;
}

//get add operation salary and dep
void extract_add_parameters(const string& line, string& department, string& salary) {
    size_t i = 4;
    
    salary = "";
    while (i < line.size()) {
        if (line[i] == ';') {
            break;
        }
        if (line[i] != '\r' && line[i] != '\n') {
            salary = salary + line[i];
        }
        i++;
    }
    
    i++;
    
    department = "";
    while (i < line.size()) {
        if (line[i] == ';') {
            break;
        }
        if (line[i] != '\r' && line[i] != '\n') {
            department = department + line[i];
        }
        i++;
    }
    
}

void extract_update_parameters(const string& line, string& task_id, string& department, string& salary) {
    size_t i = 7;
    
    task_id = "";
    while (i < line.size()) {
        if (line[i] == ';') {
            break;
        }
        task_id = task_id + line[i];
        i++;
    }
    
    i++;
    
    salary = "";
    while (i < line.size()) {
        if (line[i] == ';') {
            break;
        }
        if (line[i] != '\r' && line[i] != '\n') {
            salary = salary + line[i];
        }
        i++;
    }
    
    i++;
    
    department = "";
    while (i < line.size()) {
        if (line[i] == ';') {
            break;
        }
        if (line[i] != '\r' && line[i] != '\n') {
            department = department + line[i];
        }
        i++;
    }
}

void extract_delete_parameters(const string& line, string& task_id) {
    size_t i = 7;
    
    task_id = "";
    while (i < line.size()) {
        if (line[i] == ';') {
            break;
        }
        if (line[i] != '\r' && line[i] != '\n') {
            task_id = task_id + line[i];
        }
        i++;
    }
}

void add(const string& filename, string& department, string& salary) {
    retrieve_last_id(filename);
    stringstream new_line;
    new_line << (last_id + 1) << ";" << salary << ";" << department << endl;
    
    fstream output;
    output.open(filename, ios::app);
    output << new_line.str();
    output.close();
}

void update(const string& filename, string& task_id, string& department, string& salary) {
    if(stoi(task_id) > last_id || stoi(task_id) < 0) {
        cout << "ERROR: An invalid ID to update" << endl;
        return;
    }
    
    if (isempty(filename)) {
        cout << "ERROR: There is no Employee" << endl;
        return;
    }
    
    fstream input;
    input.open(filename, ios::in);
    
    stringstream content;
    
    bool found = false;
    string line;
    while (getline(input, line)) {
        string id = line.substr(0, line.find(";"));
        if (id == task_id) {  //found  the line
            content << task_id << ";" << salary << ";" << department << endl;
            found = true;
        } else {
            content << line << endl; // put the old data
        }
    }

    input.close();
    
    if (!found) {
        cout << "ERROR: An invalid ID to update" << endl;
        return;
    }
    
    ofstream output;
    output.open(filename, ios::trunc); //trunc
    output << content.str(); //file updated
    output.close();
}

void delete_(const string& filename, string& task_id) {
    if (stoi(task_id) > last_id || 0 > stoi(task_id) ){
        cout << "ERROR: An invalid ID to delete" << endl;
        return;
    }
    
    if (isempty(filename)) {
        cout << "ERROR: There is no Employee" << endl;
        return;
    }
    
    fstream input;
    input.open(filename, ios::in);
    
    stringstream content;
    bool found  = false;
    string line;
    while (getline(input, line)) {
        string id = line.substr(0, line.find(";"));
        if (id != task_id) {
            content << line << endl;
        } else {
            found = true;
        }
    }

    input.close();
    
    if (!found) {
        cout << "ERROR: An invalid ID to delete" << endl;
        return;
    }
    
    ofstream output;
    output.open(filename, ios::trunc);
    
    output << content.str();  //one line deleted
    output.close();
}

