#ifndef FINAL_STATES_H
#define FINAL_STATES_H

#include "states.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Final_States {
    private:
        vector<string> final_states;
    public:
        Final_States();
        void load(ifstream &definition,
                    bool &valid);
        void validate(const States &states,
                        bool &valid) const;
        void view() const;
        bool is_element(string state) const;
};

#endif