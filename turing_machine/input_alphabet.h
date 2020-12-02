#ifndef INPUT_ALPHABET_H
#define INPUT_ALPHABET_H

#include "tape_alphabet.h"
#include <string>
#include <fstream>
using namespace std;

class Input_Alphabet {
    private:
        string input_alphabet;
    public:
        Input_Alphabet();
        void load(ifstream &definition,
                    bool &valid);
        void validate(const Tape_Alphabet &tape_alphabet,
                        bool &valid) const;
        void view() const;
        bool is_element(char character) const;
};

#endif