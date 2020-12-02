#ifndef CONFIGURATION_SETTINGS_H
#define CONFIGURATION_SETTINGS_H

class Configuration_Settings {
    private:
        int max_number_of_cells;
        int max_number_of_transitions;
    public:
        Configuration_Settings();
        void update_maximum_number_of_cells(int new_setting);
        void update_maximum_number_of_transitions(int new_setting);
        int maximum_number_of_cells() const;
        int maximum_number_of_transitions() const;
};

#endif