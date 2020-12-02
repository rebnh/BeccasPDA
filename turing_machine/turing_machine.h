#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include "tape.h"
#include "input_alphabet.h"
#include "tape_alphabet.h"
#include "transition_function.h"
#include "states.h"
#include "final_states.h"
#include <string>
#include <vector>
using namespace std;

class Turing_Machine {
    private:
        Tape tape;
        Input_Alphabet input_alphabet;
        Tape_Alphabet tape_alphabet;
        Transition_Function transition_function;
        States states;
        Final_States final_states;
        vector<string> description;
        string initial_state;
        string current_state;
        string original_input_string;
        int number_of_transitions;
        bool valid;
        bool used;
        bool operating;
        bool accepted;
        bool rejected;
    public:
        Turing_Machine(string definition_file_name);
        void view_description() const;
        void view_instantaneous_description(int maximum_number_of_cells) const;
        void initialize(string input_string);
        void perform_transitions(int maximum_number_of_transitions);
        void terminate_operation();
        string input_string() const;
        int total_number_of_transitions() const;
        bool is_valid_defintion() const;
        bool is_valid_input_string(string input_string) const;
        bool is_used() const;
        bool is_operating() const;
        bool is_accepted_input_string() const;
        bool is_rejected_input_string() const;
};

#endif