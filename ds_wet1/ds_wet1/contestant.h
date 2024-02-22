// Contestant.h

#ifndef CONTESTANT_H
#define CONTESTANT_H

#include "wet1util.h"
#include "country.h"
#include "Node.h"
#include "strengthObject.h"

class Contestant {
private:
    int id;
    Sport sport;
    int strength;
    int num_of_teams;
    Node<int, Country>* country;
    int first_team;
    int second_team;
    int third_team;
    Strength_Obj strength_obj;

public:
    // Constructor
    Contestant(int id, Sport sport, int strength, int num_of_teams = 0,
               Node<int, Country>* country = nullptr);

    // Accessors
    int get_id() const;

    Sport get_sport() const;

    int& get_strength();

    Strength_Obj& get_strength_object();

    void set_strength(int new_strength);

    int& get_num_of_teams();
    void set_num_of_teams();

    Node<int,Country>* get_country();


    int get_first_team() const;
    void set_first_team(int team);

    int get_second_team() const;
    void set_second_team(int team);

    int get_third_team() const;
    void set_third_team(int team);


    // Comparison operators based on the id
    bool operator>(const Contestant& other) const;
    bool operator<(const Contestant& other) const;
    bool operator==(const Contestant& other) const;

};

#endif // CONTESTANT_H
