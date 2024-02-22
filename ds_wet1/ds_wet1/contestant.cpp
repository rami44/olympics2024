// Contestant.cpp

#include "Contestant.h"

// Constructor
Contestant::Contestant(int id, Sport sport, int strength, int num_of_teams, Node<int, Country>* country):
        id(id), sport(sport), strength(strength), num_of_teams(num_of_teams), country(country),
        first_team(0),second_team(0),third_team(0), strength_obj(strength,id) {
    }

int Contestant::get_id() const {
    return id;
}

Sport Contestant::get_sport() const {
    return sport;
}

Node<int, Country>* Contestant::get_country()  {
    return country;
}

int& Contestant::get_num_of_teams() {
    return num_of_teams;
}

int& Contestant::get_strength() {
    return strength;
}

Strength_Obj& Contestant::get_strength_object() {
    return strength_obj;
}

void Contestant::set_strength(int new_strength) {
    strength = new_strength;
    strength_obj.setStrength(new_strength);
}

int Contestant::get_first_team() const {
    return first_team;
}

void Contestant::set_first_team(int team) {
    first_team = team;
}

int Contestant::get_second_team() const {
    return second_team;
}

void Contestant::set_second_team(int team) {
    second_team = team;
}

int Contestant::get_third_team() const {
    return third_team;
}

void Contestant::set_third_team(int team) {
    third_team = team;
}


bool Contestant::operator>(const Contestant& other) const {
    return id > other.id;
}

bool Contestant::operator<(const Contestant& other) const {
    return id < other.id;
}

bool Contestant::operator==(const Contestant& other) const {
    return id == other.id;
}
