#include "final_states.h"
#include "states.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

Final_States::Final_States()
{

}

void Final_States::load(ifstream &definition, bool &valid)
{
    string value;
    if (getline(definition, value)) {
        istringstream iss(value);
        string state;
        while (iss >> state) {
            for (int i = 0; i < state.length(); i++) {
                if (!isalnum(state[i])) {
                    if (state[i] != '_') {
                        cout << "Illegal final states." << endl;
                        valid = false;
                        return;
                    }
                }
            }
            if (is_element(state)) {
                cout << "Illegal final states." << endl;
                valid = false;
                return;
            }
            final_states.push_back(state);
        }
    } else {
        cout << "Illegal final states." << endl;
        valid = false;
    }
    // if ((!(definition >> value)) ||
    //     (uppercase(value) != "INPUT_ALPHABET:")) {
    //     cout << "Missing keyword after final states." << endl;
    //     valid = false;
    // }
}

void Final_States::validate(const States &states, bool &valid) const
{
    for (int i = 0; i < final_states.size(); i++) {
        if (!states.is_element(final_states[i])) {
            cout << "Illegal final states." << endl;
            valid = false;
        }
    }
}

void Final_States::view() const
{
    cout << "F = {";
    for (int i = 0; i < (final_states.size() - 1); i++) {
        cout << final_states[i] << ", ";
    }
    cout << final_states[final_states.size() - 1] << "}" << endl;
}

bool Final_States::is_element(string state) const
{
    for (int i = 0; i < final_states.size(); i++) {
        if (state == final_states[i]) {
            return true;
        }
    }
    return false;
}