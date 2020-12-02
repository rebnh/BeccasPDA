#include "transition_function.h"
#include "transition.h"
#include "tape_alphabet.h"
#include "states.h"
#include "final_states.h"
#include "direction.h"
#include "uppercase.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

Transition_Function::Transition_Function()
{

}

void Transition_Function::load(ifstream &definition, bool &valid)
{
    string source;
    char read;
    string destination;
    char write;
    direction move;
    while (definition >> source) {
        if (uppercase(source) == "INITIAL_STATE:") {
            break;
        }
        definition >> read;
        definition >> destination;
        definition >> write;
        definition >> move;
        if (uppercase(move) != 'L' && uppercase(move) != 'R') {
            cout << "Invalid transition function." << endl;
            valid = false;
            return;
        }
        for (int i = 0; i < transitions.size(); i++) {
            if (transitions[i].source_state() == source &&
                transitions[i].read_character() == read) {
                cout << "Invalid transition function." << endl;
                valid = false;
                return;
            }
        }
        Transition temp = Transition(source, read, destination, write, move);
        transitions.push_back(temp);
    }
}

void Transition_Function::validate(const Tape_Alphabet &tape_alphabet,
                                    const States &states,
                                    const Final_States &final_states,
                                    bool &valid) const
{
    for (int i = 0; i < transitions.size(); i++) {
        if (final_states.is_element(transitions[i].source_state())) {
            cout << "Source state " << transitions[i].source_state() << " is in final states.\n";
            valid = false;
        }
        if (!states.is_element(transitions[i].source_state())) {
            cout << "Source state " << transitions[i].source_state() << " is not in states.\n";
            valid = false;
        }
        if (!tape_alphabet.is_element(transitions[i].read_character())) {
            cout << "Read character " << transitions[i].read_character() << " is not in tape alphabet.\n";
            valid = false;
        }
        if (!states.is_element(transitions[i].destination_state())) {
            cout << "Destination state " << transitions[i].destination_state() << " is not in states.\n";
            valid = false;
        }
        if (!tape_alphabet.is_element(transitions[i].write_character())) {
            cout << "Write character " << transitions[i].write_character() << " is not in tape alphabet.\n";
            valid = false;
        }
    }
}

void Transition_Function::view() const
{
    for (int i = 0; i < transitions.size(); i++) {
        cout << "delta(" << transitions[i].source_state() << ", ";
        cout << transitions[i].read_character() << ") = (";
        cout << transitions[i].destination_state() << ", ";
        cout << transitions[i].write_character() << ", ";
        cout << transitions[i].move_direction() << ")" << endl;
    }
    cout << endl;
}

void Transition_Function::find_transition(string source_state,
                                            char read_character,
                                            string &destination_state,
                                            char &write_character,
                                            direction &move_direction,
                                            bool &found) const
{
    for (int i = 0; i < transitions.size(); i++) {
        if ((transitions[i].source_state() == source_state) &&
            (transitions[i].read_character() == read_character)) {
            destination_state = transitions[i].destination_state();
            write_character = transitions[i].write_character();
            move_direction = transitions[i].move_direction();
            found = true;
            return;
        }
        found = false;
    }
}