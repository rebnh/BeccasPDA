#include "turing_machine.h"
#include "tape.h"
#include "input_alphabet.h"
#include "tape_alphabet.h"
#include "transition_function.h"
#include "states.h"
#include "final_states.h"
#include "uppercase.h"
#include "direction.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

    // private:
    //     Tape tape;
    //     Input_Alphabet input_alphabet;
    //     Tape_Alphabet tape_alphabet;
    //     Transition_Function transition_function;
    //     States states;
    //     Final_States final_states;
    //     vector<string> description;
    //     string initial_state;
    //     string current_state;
    //     string original_input_string;
    //     int number_of_transitions;
    //     bool valid;
    //     bool used;
    //     bool operating;
    //     bool accepted;
    //     bool rejected;

Turing_Machine::Turing_Machine(string definition_file_name)
{
    // tape = Tape();
    // input_alphabet = Input_Alphabet();
    // tape_alphabet = Tape_Alphabet();
    // transition_function = Transition_Function();
    // states = States();
    // final_states = Final_States();
    initial_state = "";
    current_state = "";
    original_input_string = "";
    number_of_transitions = 0;
    valid = true;
    used = false;
    operating = false;
    accepted = false;
    rejected = false;

    ifstream definition(definition_file_name + ".def");
    if (!definition.is_open()) {
        valid = false;
        return;
    }
    // get description
    string value;
    definition >> value;
    while (uppercase(value) != "STATES:") {
        description.push_back(value);
        definition >> value;
    }
    states.load(definition, valid);
    input_alphabet.load(definition, valid);
    tape_alphabet.load(definition, valid);
    transition_function.load(definition, valid);
    definition >> initial_state;
    if (!(definition >> value) || uppercase(value) != "BLANK_CHARACTER:") {
        cout << "Missing keyword after initial state." << endl;
        valid = false;
    }
    tape.load(definition, valid);
    final_states.load(definition, valid);

    definition.close();

    input_alphabet.validate(tape_alphabet, valid);
    transition_function.validate(tape_alphabet, states, final_states, valid);
    if (!states.is_element(initial_state)) {
        cout << "Initial state " << initial_state << " is not in states." << endl;
        valid = false;
    }
    tape.validate(input_alphabet, tape_alphabet, valid);
    final_states.validate(states, valid);
}

void Turing_Machine::view_description() const
{
    for (int i = 0; i < (description.size() - 1); i++) {
        cout << description[i] << " ";
    }
    if (description.size() > 0) {    
        cout << description[description.size() - 1] << endl << endl;
    }
    cout << "M = (Q, Sigma, Gamma, delta, q0, B, F) where" << endl << endl;
    states.view();
    input_alphabet.view();
    tape_alphabet.view();
    transition_function.view();
    cout << "q0 = " << initial_state << endl << endl;
    tape.view();
    final_states.view();
}

void Turing_Machine::view_instantaneous_description(int maximum_number_of_cells) const
{
    cout << tape.left(maximum_number_of_cells);
    cout << "[" << current_state << "]";
    cout << tape.right(maximum_number_of_cells);
    cout << endl;
}

void Turing_Machine::initialize(string input_string)
{
    used = true;
    operating = true;
    accepted = false;
    rejected = false;
    current_state = initial_state;
    number_of_transitions = 0;
    original_input_string = input_string;
    tape.initialize(original_input_string);
}

void Turing_Machine::perform_transitions(int maximum_number_of_transitions)
{
    string destination;
    char write;
    direction move;
    bool found = false;
    int i = maximum_number_of_transitions + 1;
    while (i > 0) {
        if (final_states.is_element(current_state)) {
            operating = false;
            accepted = true;
            return;
        }
        if (i > 1) {
            transition_function.find_transition(current_state, tape.current_character(),
                                                destination, write, move, found);
            if (found) {
                tape.update(write, move);
                current_state = destination;
                number_of_transitions++;
            } else {
                operating = false;
                rejected = true;
                return;
            }
            // checks if already at rejection point
            transition_function.find_transition(current_state, tape.current_character(),
                                                destination, write, move, found);
            if (!found && !final_states.is_element(current_state)) {
                operating = false;
                rejected = true;
                return;
            }
        }
        i--;
    }
}

void Turing_Machine::terminate_operation()
{
    operating = false;
}

string Turing_Machine::input_string() const
{
    return original_input_string;
}

int Turing_Machine::total_number_of_transitions() const
{
    return number_of_transitions;
}

bool Turing_Machine::is_valid_defintion() const
{
    return valid;
}

bool Turing_Machine::is_valid_input_string(string input_string) const
{
    if (input_string != "\\") {
        if (input_string.length() == 0) {
            return false;
        }
        for (int i = 0; i < input_string.length(); i++) {
            if (!input_alphabet.is_element(input_string[i])) {
                return false;
            }
        }
    }
    return true;
}

bool Turing_Machine::is_used() const
{
    return used;
}

bool Turing_Machine::is_operating() const
{
    return operating;
}

bool Turing_Machine::is_accepted_input_string() const
{
    return accepted;
}

bool Turing_Machine::is_rejected_input_string() const
{
    return rejected;
}