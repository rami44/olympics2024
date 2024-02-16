// class team has the following data members:
// // key is TeamId
// // data is: sport (Sport enum), num_contestants (int), team_strength (int), countryId (shared_ptr)

#ifndef TEAM_H
#define TEAM_H

#include <memory>
#include "wet1util.h"
#include "country.h"
#include "contestant.h"
#include "binary_tree.h"

class Team {

private:
    int teamId;
    Sport sport;
    Node<int, Country> *team_country;
    int team_strength;
    int num_contestants;

    BinaryTree<int, Contestant> first_third_id;
    BinaryTree<int, Contestant> second_third_id;
    BinaryTree<int, Contestant> third_third_id;

    BinaryTree<int, int> first_third_strength;
    BinaryTree<int, int> second_third_strength;
    BinaryTree<int, int> third_third_strength;

public:

    // Constructor
    Team(int teamId, Sport sport,  Node<int, Country> *country, int team_strength = 0, int num_contestants = 0);

    // GETTERS AND SETTERS
    int getTeamId();

    Sport getSport();

    int &getNumContestants();

    int &getTeamStrength();

    std::shared_ptr<int> getCountryId();

    BinaryTree<int, Contestant>* find_id_tree(int contestantId);

    // divide contestants into thirds based on their strength, id and insert into corresponding trees
    void add_contestant_to_tree(int contestantId, Sport sport, int strength);

};

#endif //TEAM_H