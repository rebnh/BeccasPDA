#include "commands.h"
#include "final_states.h"
#include "input_alphabet.h"
#include "states.h"
#include "tape_alphabet.h"
#include "transition_function.h"
#include "tape.h"
#include "input_strings.h"
#include "configuration_settings.h"
#include "turing_machine.h"
#include <string>
#include <limits>
#include <iostream>
using namespace std;

void help()
{
    /* Help user by displaying commands */
    cout << endl << "d\tDelete\t\tDelete input string from list" << endl;
    cout << "x\tExit\t\tExit application" << endl;
    cout << "h\tHelp\t\tDisplay available commands" << endl;
    cout << "i\tInsert\t\tInsert input string into list" << endl;
    cout << "l\tList\t\tList input strings" << endl;
    cout << "q\tQuit\t\tQuit operation of Turing machine on input string" << endl;
    cout << "r\tRun\t\tRun Turing machine on input string" << endl;
    cout << "e\tSet\t\tSet maximum number of transitions to perform" << endl;
    cout << "w\tShow\t\tShow status of application" << endl;
    cout << "t\tTruncate\tTruncate instantaneous descriptions" <<endl;
    cout << "v\tView\t\tView Turing machine" << endl;
}

void show(const Turing_Machine &turing_machine, const Configuration_Settings &config_settings,
            const Input_Strings &input_strings, string definition_file_name)
{
    cout << endl << "CptS 323 - Spring 2020" << endl;
    cout << "Instructor: Neil Corrigan" << endl;
    cout << "Author: Rebecca Helmann" << endl;
    cout << "Version 0.1" << endl << endl;
    cout << "Settings:" << endl;
    cout << "\tNumber of transitions: " << config_settings.maximum_number_of_transitions() << endl;
    cout << "\tNumber of cells: " << config_settings.maximum_number_of_character() <<  endl;
    cout << "Turing machine:" << endl;
    cout << "\tName: " << definition_file_name << endl;
    if (turing_machine.is_operating()) {
        cout << "\tStatus: Currently running." << endl;
        cout << "\t\tInput string: " << turing_machine.input_string() << endl;
        cout << "\t\tTransitions so far: " << turing_machine.total_number_of_transitions() << endl;
    } else if (!turing_machine.is_used()) {
        cout << "\tStatus: Has not been run." << endl;
    } else {
        cout << "\tStatus: Completed operation." << endl;
        cout << "\t\tInput string: " << turing_machine.input_string() << endl;
        cout << "\t\tTransitions: " << turing_machine.total_number_of_transitions() << endl;
        if (turing_machine.is_accepted_input_string()) {
            cout << "\t\tAccepted." << endl;
        } else if (turing_machine.is_rejected_input_string()) {
            cout << "\t\tRejected." << endl;
        } else {
            cout << "\t\tTerminated early." << endl;
        }
    }
    cout << "Input string list:" << endl;
    if (input_strings.status()) {
        cout << "\tStatus: Will write." << endl;
    } else {
        cout << "\tStatus: Will not write." << endl;
    }
}

void view(const Turing_Machine &turing_machine)
{
    turing_machine.view_description();
}

void list(const Input_Strings &input_strings)
{
    input_strings.list_strings();
}

void insert(Input_Strings &input_strings, const Turing_Machine &turing_machine)
{
    string to_insert;
    cout << "Enter string: ";
    cin >> to_insert;
    if (!turing_machine.is_valid_input_string(to_insert)) {
        cout << "Error! Invlaid input string!" << endl;
        return;
    }
    input_strings.insert_string(to_insert);
}

void remove(Input_Strings &input_strings) // "delete" cmd
{
    int string_number;
    cout << "Enter number of string to delete: ";
    cin >> string_number;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Error! Invalid input string number!" << endl;
        return;
    }
    if (!input_strings.is_existing_string(string_number)) {
        cout << "Error! Invalid input string number!" << endl;
        return;
    }
    input_strings.delete_string(string_number);
}

void set(Configuration_Settings &config_settings)
{
    int new_setting;
    cout << "Number of transitions (current = " << config_settings.maximum_number_of_transitions() << "): ";
    cin >> new_setting;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Error! Invalid setting!" << endl;
        return;
    }
    if (new_setting <= 0) {
        cout << "Error! Invalid setting!" << endl;
        return;
    }
    config_settings.update_maximum_number_of_transitions(new_setting);
}

void truncate(Configuration_Settings &config_settings)
{
    int new_setting;
    cout << "Number of cells (current = " << config_settings.maximum_number_of_character() << "): ";
    cin >> new_setting;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Error! Invalid setting!" << endl;
        return;
    }
    if (new_setting <= 0) {
        cout << "Error! Invalid setting!" << endl;
        return;
    }
    config_settings.update_maximum_number_of_character(new_setting);
}

void run(Turing_Machine &turing_machine, const Input_Strings &input_strings, const Configuration_Settings &config_settings)
{
    if (!turing_machine.is_operating()) {
        int string_number;
        cout << "Input string number: ";
        cin >> string_number;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Error! Invalid input string number!" << endl;
            return;
        }
        if (!input_strings.is_existing_string(string_number)) {
            cout << "Error! Invalid input string number!" << endl;
            return;
        }
        turing_machine.initialize(input_strings.get_string(string_number));
        cout << turing_machine.total_number_of_transitions() << ". ";
        turing_machine.view_instantaneous_description(config_settings.maximum_number_of_character());
    }
    int check = turing_machine.total_number_of_transitions();
    turing_machine.perform_transitions(config_settings.maximum_number_of_transitions());
    if (check != turing_machine.total_number_of_transitions()) {
        cout << turing_machine.total_number_of_transitions() << ". ";
        turing_machine.view_instantaneous_description(config_settings.maximum_number_of_character());
    }
    if (turing_machine.is_accepted_input_string()) {
        cout << "Input string " << turing_machine.input_string() << " accepted in ";
        cout << turing_machine.total_number_of_transitions() << " transtitions!" << endl;
    } else if (turing_machine.is_rejected_input_string()) {
        cout << "Input string " << turing_machine.input_string() << " rejected in ";
        cout << turing_machine.total_number_of_transitions() << " transtitions!" << endl;
    }
}

void quit(Turing_Machine &turing_machine)
{
    if (!turing_machine.is_operating()) {
        cout << "Error! Turing machine not running." << endl;
        return;
    }
    turing_machine.terminate_operation();
    cout << "Input string " << turing_machine.input_string();
    cout << " is not accepted or rejected in "; 
    cout << turing_machine.total_number_of_transitions();
    cout << " transitions." << endl;
}

void exit(const Input_Strings &input_strings, string string_file_name)
{
    input_strings.write(string_file_name);
    return;
}