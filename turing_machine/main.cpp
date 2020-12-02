/**
 * CptS 322 - Spring 2020
 * Turing Machine Driver
 * @author: Rebecca Helmann
 */
#include "turing_machine.h"
#include "input_strings.h"
#include "configuration_settings.h"
#include "commands.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Usage: TM <name of definition file>" << endl;
        return 0;
    }
    string command;
    string file_name = argv[1];
    Configuration_Settings config_settings = Configuration_Settings();

    Turing_Machine turing_machine = Turing_Machine(file_name);
    if (!turing_machine.is_valid_defintion()) {
        cout << "Failed to load " << file_name << ".def!" << endl << endl;
        return 0;
    }

    Input_Strings input_strings = Input_Strings(file_name, turing_machine);
    cout << "Successfully loaded " << file_name << ".def!" << endl;

    while(1)
    {
        cout << endl << "Command: ";
        cin >> command;

        if (command == "D" || command == "d") { // delete
            /* Delete input string from list */
            remove(input_strings);

        } else if (command == "X" || command == "x") { // exit
            /* Exit application */
            exit(input_strings, file_name);
            break;

        } else if (command == "H" || command == "h") { // help
            /* Help user by displaying commands */
            help();

        } else if (command == "I" || command == "i") { // insert
            /* Insert input string into list */
            insert(input_strings, turing_machine);

        } else if (command == "L" || command == "l") { // list
            /* List input strings */
            list(input_strings);

        } else if (command == "Q" || command == "q") { // quit
            /* Quit operation of TM on input string */
            quit(turing_machine);

        } else if (command == "R" || command == "r") { // run
            /* Run TM on input string */
            run(turing_machine, input_strings, config_settings);

        } else if (command == "E" || command == "e") { // set
            /* Set maximum number of transitions to perform */
            set(config_settings);

        } else if (command == "W" || command == "w") { // show
            /* Show status of application */
            show(turing_machine, config_settings, input_strings, file_name);

        } else if (command == "T" || command == "t") { // truncate
            /* Truncate instantaneous descriptions */
            truncate(config_settings);

        } else if (command == "V" || command == "v") { // view
            /* View TM */
            view(turing_machine);

        } else {
            cout << "Error! Invalid command." << endl;
        }
    }
    return 0;
}