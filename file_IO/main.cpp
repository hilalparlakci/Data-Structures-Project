#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "file_functions.hpp"

using namespace std;

int main(int argc, char** argv) {
    
    const char* data_file = argv[1];
    const char* operations_file = argv[2];
    
    fstream operations_stream;
    operations_stream.open(operations_file, ios::in);
    if (!operations_stream.is_open()) {
        cout << "operations file failed to open." << endl;
        return 1;
    }
    
    retrieve_last_id(data_file);
    
    string operation_line;
    while (getline(operations_stream, operation_line)) {
        string method = extract_method(operation_line);
        
        if (method == "ADD") {
            string department, salary;
            extract_add_parameters(operation_line, department, salary);
            add(data_file, department, salary);
        }
        
        if (method == "UPDATE") {
            string task_id, department, salary;
            extract_update_parameters(operation_line, task_id, department, salary);
            update(data_file, task_id, department, salary);
        }
        
        if (method == "DELETE") {
            string task_id;
            extract_delete_parameters(operation_line, task_id);
            delete_(data_file, task_id);
        }
        
    }
    
    operations_stream.close();
 
    return 0;
}

