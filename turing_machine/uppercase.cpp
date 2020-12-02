#include "uppercase.h"
#include "direction.h"
#include <string>
#include <iostream>
using namespace std;

string uppercase(string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    return s;
}

direction uppercase(direction d) {
    return toupper(d);
}