#ifndef INPUT_STRINGS_H
#define INPUT_STRINGS_H

#include "turing_machine.h"
#include <string>
#include <vector>
using namespace std;

class Input_Strings {
    private:
        vector<string> input_strings;
        bool string_status;
    public:
        Input_Strings(string string_file_name,
                        const Turing_Machine &turing_machine);
        void insert_string(string to_insert);
        void delete_string(int string_number);
        bool is_existing_string(int string_number) const;
        void list_strings() const;
        string get_string(int string_number) const;
        void write(string string_file_name) const;
        bool status() const;
};

#endif