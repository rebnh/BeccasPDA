#include "configuration_settings.h"
#include <iostream>
#include <fstream>
using namespace std;

Configuration_Settings::Configuration_Settings() : max_number_of_character(32),
                                                   max_number_of_transitions(1)
{
}
void Configuration_Settings::load(ifstream configuration)
{
    std::string inputLine, configKeyword;
    int newConfigValue, equalSignLoc;
    if (configuration.is_open())
    {
        while (configuration >> inputLine)
        {                                                                      //gets the a line in the file
            equalSignLoc = inputLine.find('=');                                //finds  where the equal sign that sepeates the keyword from the value is
            configKeyword = inputLine.substr(0, equalSignLoc - 1);             //grabs the keyword
            newConfigValue = atoi(inputLine.substr(equalSignLoc + 1).c_str()); //grabs the value
            if (!configKeyword.compare("MAXIMUM_TRANSITIONS"))
            {
                update_maximum_number_of_transitions(newConfigValue);
            }
            else if (!configKeyword.compare("MAXIMUM_CHARACTERS"))
            {
                update_maximum_number_of_character(newConfigValue);
            }
        }
    }
    return;
}

void Configuration_Settings::update_maximum_number_of_character(int new_setting)
{
    max_number_of_character = new_setting;
    cout << "Setting changed to " << max_number_of_character << "!" << endl;
}

void Configuration_Settings::update_maximum_number_of_transitions(int new_setting)
{
    max_number_of_transitions = new_setting;
    cout << "Setting changed to " << max_number_of_transitions << "!" << endl;
}

int Configuration_Settings::maximum_number_of_character() const
{
    return max_number_of_character;
}

int Configuration_Settings::maximum_number_of_transitions() const
{
    return max_number_of_transitions;
}