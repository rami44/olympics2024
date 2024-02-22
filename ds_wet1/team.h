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
#include "strengthObject.h"

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

    BinaryTree<Strength_Obj, int> first_third_strength;
    BinaryTree<Strength_Obj, int> second_third_strength;
    BinaryTree<Strength_Obj, int> third_third_strength;

public:

    // Constructor
    Team(int teamId, Sport sport, Node<int, Country> *country, int team_strength = 0, int num_contestants = 0);

    struct Deleter {
    public:
        void operator()(const Node<int, Team> *node) const {
            if (node == nullptr) return;
            node->get_data()->delete_internal_trees();
        }
    };

    void move_node(BinaryTree<int, Contestant> &sourceTree_id, BinaryTree<int, Contestant> &destTree_id,
                         BinaryTree<Strength_Obj, int> &sourceTree_strength, BinaryTree<Strength_Obj, int> &desTree_strength,
                         Node<int, Contestant> *moving_node);

    // remove contestant
    void remove_contestant(int contestantId);

    void update_strength(Strength_Obj& old_strength, Strength_Obj& new_strength, BinaryTree<Strength_Obj, int> &tree);

    // GETTERS AND SETTERS

    // set num contestants
    void setNumContestants(int num_contestants);

    // get tree id1

    BinaryTree<int, Contestant> *get_tree_id1();

    // get tree id2

    BinaryTree<int, Contestant> *get_tree_id2();

    // get tree id3

    BinaryTree<int, Contestant> *get_tree_id3();

    // get team_country

    BinaryTree<Strength_Obj, int> *get_tree_strength1();

    // get tree strength2

    BinaryTree<Strength_Obj, int> *get_tree_strength2();

    // get tree strength3

    BinaryTree<Strength_Obj, int> *get_tree_strength3();

    Node<int,Country>* get_country();

    int getTeamId() const;

    Sport get_sport() const;

    int &getNumContestants();

    int& getTeamStrength();

    void delete_internal_trees();

    BinaryTree<int, Contestant> *find_id_tree(int contestantId);

    // divide contestants into thirds based on their strength, id and insert into corresponding trees
    void add_contestant_to_tree(int contestantId, Sport sport, int strength);

    //rearrange contesant trees after removing contestant
    void re_arrange_trees();

    void update_contestant_strength_in_team(Node<int, Team>* teamNode, int contestantId,
                                                  Strength_Obj& oldStrength, Strength_Obj& newStrength);


    Node<int, Contestant>** sort_id_trees_to_array() ;
    Node<Strength_Obj, int>** sort_strength_trees_to_array() ;



};


#endif //TEAM_H