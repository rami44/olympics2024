// Contestant.cpp

#include "Contestant.h"

// Constructor
Contestant::Contestant(int id, Sport sport, int strength, const Node<int, Country>* country)
        : id(id), sport(sport), strength(strength), country(country) {}


int Contestant::get_id() const {
    return id;
}

Sport Contestant::get_sport() const {
    return sport;
}

int Contestant::get_strength() const {
    return strength;
}

const Node<int, Country>* Contestant::get_country() const {
    return country;
}

// Mutators

void Contestant::set_strength(int new_strength) {
    strength = new_strength;
}

void Contestant::set_country(const Node<int, Country>* new_country) {
    country = new_country;
}
