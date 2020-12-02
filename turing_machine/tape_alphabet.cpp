#include "tape_alphabet.h"
#include "uppercase.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

Tape_Alphabet::Tape_Alphabet():
    tape_alphabet("")
{

}

void Tape_Alphabet::load(ifstream &definition, bool &valid)
{
    string value;
    if ((getline(definition, value))) {
        istringstream iss(value);
        string item;
        while (iss >> item) {
            if ((item.length() == 1) && (item[0] != '\\') &&
            (item[0] != '[') && (item[0] != ']') &&
            (item[0] != '<') && (item[0] != '>')) {
                if (is_element(item[0])) {
                    cout << "Illegal tape alphabet." << endl;
                    valid = false;
                    return;
                }
                tape_alphabet = tape_alphabet + item[0];
            } else {
                cout << "Illegal tape alphabet." << endl;
                valid = false;
                return;
            }
        }
    } else {
        cout << "Illegal tape alphabet." << endl;
        valid = false;
    }
    if ((!(definition >> value)) ||
        (uppercase(value) != "TRANSITION_FUNCTION:")) {
        cout << "Missing keyword after tape alphabet." << endl;
        valid = false;
    }
}

void Tape_Alphabet::view() const 
{
    cout << "Gamma = {";
    for (int i = 0; i < (tape_alphabet.length() - 1); i++) {
        cout << tape_alphabet[i] << ", ";
    }
    cout << tape_alphabet[tape_alphabet.length() - 1] << "}" << endl << endl;
}

bool Tape_Alphabet::is_element(char character) const
{
    for (int i = 0; i < tape_alphabet.length(); i++) {
        if (character == tape_alphabet[i]) {
            return true;
        }
    }
    return false;
}