// Contestant.h

#ifndef CONTESTANT_H
#define CONTESTANT_H

#include "wet1util.h"
#include "country.h"
#include "Node.h"

class Contestant {
private:
    int id;
    Sport sport;
    int strength;
    const Node<int, Country>* country; // Use const pointer to avoid modifying the pointed object
public:
    // Constructor
    Contestant(int id, Sport sport, int strength, const Node<int, Country>* country=nullptr);

    // Accessors
    int get_id() const;

    Sport get_sport() const;

    int& get_strength();

    void set_strength(int new_strength);


    int& get_num_of_teams();
    void set_num_of_teams();

    Node<int,Country>* get_country();


    void set_strength(int new_strength);
    void set_country(const Node<int, Country>* new_country);
};

#endif // CONTESTANT_H
