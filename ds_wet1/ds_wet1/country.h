// class Country which has the following data members:
// key is CountryId
// data is: num_medals (int), num_teams (int), num_contestants (int)


#ifndef COUNTRY_H
#define COUNTRY_H

#include <memory>
#include "wet1util.h"

class Country {
private:
    int countryId;
    int num_medals;
    int num_teams;
    int num_contestants;
public:
    Country(int countryId, int medals, int teams=0, int contestants=0);

    // GETTERS AND SETTERS

    int getCountryId();

    int& getNumMedals();

    int& getNumTeams();

    int& getNumContestants();

    void setNumMedals(int medals);

    void setNumTeams(int teams);

    void setNumContestants(int contestants);

    void addMedal();



};

#endif //COUNTRY_H