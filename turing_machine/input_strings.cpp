#include "input_strings.h"
#include "turing_machine.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

Input_Strings::Input_Strings(string string_file_name,
                                const Turing_Machine &turing_machine):
    string_status(false)
{
    ifstream input_string_file(string_file_name + ".str");
    string line;
    while (getline(input_string_file, line)) {
        if (turing_machine.is_valid_input_string(line)) {
            input_strings.push_back(line);
        } else {
            string_status = true;
        }
    }
    input_string_file.close();
}

void Input_Strings::insert_string(string to_insert)
{
    input_strings.push_back(to_insert);
    cout << "Inserted " << to_insert << " into list!" << endl;
    string_status = true;
}

void Input_Strings::delete_string(int string_number)
{
    if (is_existing_string(string_number)) {
        string temp = input_strings.at(string_number-1);
        input_strings.erase(input_strings.begin()+string_number-1);
        cout << "String " << temp << " deleted!" << endl;
        string_status = true;
        return;
    }
    cout << "Error! Invalid string number!" << endl;
}

bool Input_Strings::is_existing_string(int string_number) const
{
    if (string_number > input_strings.size() || string_number < 1) {
        return false;
    }
    return true;
}

void Input_Strings::list_strings() const
{
    for (int i = 1; i <= input_strings.size(); i++) {
        cout << i << ". " << input_strings.at(i-1) << endl;
    }
}

string Input_Strings::get_string(int string_number) const
{
    if (is_existing_string(string_number)) {
        return input_strings.at(string_number-1);
    }
    return "";
}

void Input_Strings::write(string string_file_name) const
{
    if (string_status) {
        ofstream input_string_file(string_file_name + ".str");
        for (int i = 0; i < input_strings.size(); i++) {
            input_string_file << input_strings.at(i);
            if (i < input_strings.size()-1) {
                input_string_file << endl;
            }
        }
        input_string_file.close();
        if (input_string_file.bad()) {
            cout << "Failed to write list to " << string_file_name << ".str!" << endl;
        }
        cout << "Succeeded in writing list to "<< string_file_name << ".str!" << endl;
    }
}

bool Input_Strings::status() const
{
    return string_status;
}