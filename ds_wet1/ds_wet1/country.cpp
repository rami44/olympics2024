#include "country.h"

// Constructor
Country::Country(int countryId, int medals, int teams, int contestants) :
        countryId(countryId), num_medals(medals), num_teams(teams), num_contestants(contestants) {}

// Getter methods
int Country::getCountryId() {
    return countryId;
}

int& Country::getNumMedals() {
    return num_medals;
}

int &Country::getNumTeams() {
    return num_teams;
}

int &Country::getNumContestants() {
    return num_contestants;
}

// Setter methods
void Country::setNumMedals(int medals) {
    num_medals = medals;
}

void Country::setNumTeams(int teams) {
    num_teams = teams;
}

void Country::setNumContestants(int contestants) {
    num_contestants = contestants;
}

// Other methods
void Country::addMedal() {
    num_medals++;
}
