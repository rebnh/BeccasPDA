#ifndef CONFIGURATION_SETTINGS_H
#define CONFIGURATION_SETTINGS_H

class Configuration_Settings
{
private:
    int max_number_of_character;
    int max_number_of_transitions;

public:
    Configuration_Settings();
    void load(std::ifstream configuration);
    void update_maximum_number_of_character(int new_setting);
    void update_maximum_number_of_transitions(int new_setting);
    int maximum_number_of_character() const;
    int maximum_number_of_transitions() const;
};

#endif