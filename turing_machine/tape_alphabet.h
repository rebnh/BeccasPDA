#ifndef TAPE_ALPHABET_H
#define TAPE_ALPHABET_H

#include <string>
#include <fstream>
using namespace std;

class Tape_Alphabet {
    private:
        string tape_alphabet;
    public:
        Tape_Alphabet();
        void load(ifstream &definition,
                    bool &valid);
        void view() const;
        bool is_element(char character) const;
};

#endif