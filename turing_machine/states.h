#ifndef STATES_H
#define STATES_H

#include <string>
#include <vector>
#include <fstream>
using namespace std;

class States {
    private:
        vector<string> states;
    public:
        States();
        void load(ifstream &definition,
                    bool &valid);
        void view() const;
        bool is_element(string state) const;
};

#endif