#include "configuration_settings.h"
#include <iostream>
using namespace std;

Configuration_Settings::Configuration_Settings():
    max_number_of_cells(32),
    max_number_of_transitions(1)
{

}

void Configuration_Settings::update_maximum_number_of_cells(int new_setting)
{
    max_number_of_cells = new_setting;
    cout << "Setting changed to " << max_number_of_cells << "!" << endl;
}

void Configuration_Settings::update_maximum_number_of_transitions(int new_setting)
{
    max_number_of_transitions = new_setting;
    cout << "Setting changed to " << max_number_of_transitions << "!" << endl;
}

int Configuration_Settings::maximum_number_of_cells() const
{
    return max_number_of_cells;
}

int Configuration_Settings::maximum_number_of_transitions() const
{
    return max_number_of_transitions;
}