#ifndef COMMANDS_H
#define COMMANDS_H

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
using namespace std;

void help();
void show(const Turing_Machine &turing_machine, const Configuration_Settings &config_settings,
            const Input_Strings &input_strings, string definition_file_name);
void view(const Turing_Machine &turing_machine);
void list(const Input_Strings &input_strings);
void insert(Input_Strings &input_strings, const Turing_Machine &turing_machine);
void remove(Input_Strings &input_strings);
void set(Configuration_Settings &config_settings);
void truncate(Configuration_Settings &config_settings);
void run(Turing_Machine &turing_machine, const Input_Strings &input_strings, const Configuration_Settings &config_settings);
void quit(Turing_Machine &turing_machine);
void exit(const Input_Strings &input_strings, string string_file_name);

#endif