#include "states.h"
#include "uppercase.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

States::States()
{

}

void States::load(ifstream &definition, bool &valid)
{
    string value;
    if (getline(definition, value)) {
        istringstream iss(value);
        string state;
        while (iss >> state) {
            for (int i = 0; i < state.length(); i++) {
                if (!isalnum(state[i])) {
                    if (state[i] != '_') {
                        cout << "Illegal states.1" << endl;
                        valid = false;
                        return;
                    }
                }
            }
            if (is_element(state)) {
                cout << "Illegal states.2" << endl;
                valid = false;
                return;
            }
            states.push_back(state);
        }
    } else {
        cout << "Illegal states.3" << endl;
        valid = false;
    }
    if ((!(definition >> value)) ||
        (uppercase(value) != "INPUT_ALPHABET:")) {
        cout << "Missing keyword after states." << endl;
        valid = false;
    }
}

void States::view() const
{
    cout << "Q = {";
    for (int i = 0; i < (states.size() - 1); i++) {
        cout << states[i] << ", ";
    }
    cout << states[states.size() - 1] << "}" << endl << endl;
}

bool States::is_element(string state) const
{
    for (int i = 0; i < states.size(); i++) {
        if (state == states[i]) {
            return true;
        }
    }
    return false;
}