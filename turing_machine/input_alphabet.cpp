#include "input_alphabet.h"
#include "tape_alphabet.h"
#include "uppercase.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

Input_Alphabet::Input_Alphabet():
    input_alphabet("")
{

}

void Input_Alphabet::load(ifstream &definition, bool &valid)
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
                    cout << "Illegal input alphabet." << endl;
                    valid = false;
                    return;
                }
                input_alphabet = input_alphabet + item[0];
            } else {
                cout << "Illegal input alphabet." << endl;
                valid = false;
                return;
            }
        }
    } else {
        cout << "Illegal input alphabet." << endl;
        valid = false;
    }
    if ((!(definition >> value)) ||
        (uppercase(value) != "TAPE_ALPHABET:")) {
        cout << "Missing keyword after input alphabet." << endl;
        valid = false;
    }
}

void Input_Alphabet::validate(const Tape_Alphabet &tape_alphabet,
                                bool &valid) const
{
    for (int i = 0; i < input_alphabet.length(); i++) {
        if (!tape_alphabet.is_element(input_alphabet[i])) {
            cout << "Illegal input alphabet." << endl;
            valid = false;
        }
    }
}

void Input_Alphabet::view() const
{
    cout << "Sigma = {";
    for (int i = 0; i < (input_alphabet.length() - 1); i++) {
        cout << input_alphabet[i] << ", ";
    }
    cout << input_alphabet[input_alphabet.length() - 1] << "}" << endl << endl;
}

bool Input_Alphabet::is_element(char character) const
{
    for (int i = 0; i < input_alphabet.length(); i++) {
        if (character == input_alphabet[i]) {
            return true;
        }
    }
    return false;
}