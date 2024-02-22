// 
// 234218 Data Structures 1.
// Semester: 2024A (winter).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 



#include "wet1util.h"
#include "Olympicsa1.h"
#include "team.h"
#include "strengthObject.h"


Olympics::Olympics() : countries(), teams(), contestants() {}

// In the Olympics class destructor
Olympics::~Olympics() {
    // Iterate over all nodes in the "teams" tree and call delete_internal_trees for each node
    Team::Deleter deleter;
    teams.post_order(deleter, teams.get_root());
    // Delete the trees countries, teams, and contestants
    countries.delete_tree();
    contestants.delete_tree();
    teams.delete_tree();
}


StatusType Olympics::add_country(int countryId, int medals) {
    // Implementation for add_country
    if (countryId <= 0 || medals <= 0)
        return StatusType::INVALID_INPUT;
    try {
        std::shared_ptr<Country> newC = std::make_shared<Country>(countryId, medals);
        bool check = countries.insert_key_and_data(countryId, newC);
        if (check) {
            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    }
    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Olympics::remove_country(int countryId) {
    // Implementation for remove_country
    if (countryId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Node<int, Country> *country_to_delete = countries.get_node_from_key(countryId);
    if (country_to_delete == nullptr) {
        //country does not exist
        return StatusType::FAILURE;
    }
    Country &c = *(country_to_delete->get_data());
    if (c.getNumContestants() > 0 || c.getNumTeams() > 0) {
        return StatusType::FAILURE;
    }

    try {
        countries.delete_node(country_to_delete);
        return StatusType::SUCCESS;
    }
    catch (const std::exception &e) {
        return StatusType::FAILURE;
    }

}

StatusType Olympics::add_team(int teamId, int countryId, Sport sport) {
    // Implementation for add_team
    if (countryId <= 0 || teamId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        // std::shared_ptr<Country> newC = std::make_shared<Country>(countryId, medals);
        Node<int, Country> *c = countries.get_node_from_key(countryId);
        //the country does not exist
        if (c == nullptr) {
            return StatusType::FAILURE;
        }
        Node<int, Team> *t = teams.get_node_from_key(teamId);
        //team already inserted
        if (t != nullptr) {
            return StatusType::FAILURE;
        }
        c->get_data()->getNumTeams()++;//update the country team num
        std::shared_ptr<Team> new_team = std::make_shared<Team>(teamId, sport, c);
        teams.insert_key_and_data(teamId, new_team);
    }
    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::remove_team(int teamId) {
    // Implementation for remove_team
    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Node<int, Team> *team_node = teams.get_node_from_key(teamId);
    if (team_node == nullptr) {
        //team does not exist in teams tree
        return StatusType::FAILURE;
    }
    //team actually exists
    std::shared_ptr<Team> t = team_node->get_data();
    if (t->getNumContestants() > 0) {
        return StatusType::FAILURE;
    }
    try {
        teams.delete_key(teamId);
    }
    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }

}

StatusType Olympics::add_contestant(int contestantId, int countryId, Sport sport, int strength) {
    // Implementation for add_contestant

    if (countryId <= 0 || contestantId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        // std::shared_ptr<Country> newC = std::make_shared<Country>(countryId, medals);
        Node<int, Country> *country = countries.get_node_from_key(countryId);
        //the country does not exist
        if (country == nullptr) {
            return StatusType::FAILURE;
        }
        Node<int, Contestant> *contestant = contestants.get_node_from_key(contestantId);
        //team already inserted
        if (contestant != nullptr) {
            return StatusType::FAILURE;
        }
        country->get_data()->getNumContestants()++; //update the country contestants  num
        std::shared_ptr<Contestant> new_contestant = std::make_shared<Contestant>(contestantId, sport, strength, 0,
                                                                                  country);
        contestants.insert_key_and_data(contestantId, new_contestant);
    }
    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Olympics::remove_contestant(int contestantId) {
    // Implementation for remove_contestant
    if (contestantId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Node<int, Contestant> *contestant = contestants.get_node_from_key(contestantId);
    if (contestant == nullptr) {
        //contestant does not exist
        return StatusType::FAILURE;
    }
    if (contestant->get_data()->get_num_of_teams() > 0) {
        //contestant participate in such team
        return StatusType::FAILURE;
    }
    try {
        contestant->get_data()->get_country()->get_data()->getNumContestants()--;
        contestants.delete_key(contestantId);
    }
    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }

}

StatusType Olympics::add_contestant_to_team(int teamId, int contestantId) {
    // Implementation for add_contestant_to_team
    if (teamId <= 0 || contestantId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Node<int, Contestant> *contestant = contestants.get_node_from_key(contestantId);
    Node<int, Team> *team = teams.get_node_from_key(teamId);
    if (contestant == nullptr || team == nullptr) {
        return StatusType::FAILURE;
    }
    if (contestant->get_data()->get_num_of_teams() >= 3 || contestant->get_data()->get_sport() !=
                                                           team->get_data()->get_sport()) {
        return StatusType::FAILURE;
    }
    int team_num = contestant->get_data()->get_num_of_teams();
    if (team_num == 0) {
        contestant->get_data()->set_first_team(teamId);
    } else if (team_num == 1) {
        contestant->get_data()->set_second_team(teamId);
    } else {
        contestant->get_data()->set_third_team(teamId);
    }
    try {
        contestant->get_data()->get_num_of_teams()++;
        team->get_data()->setNumContestants(team->get_data()->getNumContestants() + 1);
        team->get_data()->add_contestant_to_tree(contestant->get_data());
        return StatusType::SUCCESS;
    }
    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Olympics::remove_contestant_from_team(int teamId, int contestantId) {
    // Implementation for remove_contestant_from_team
    if (teamId <= 0 || contestantId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Node<int, Contestant> *contestant = contestants.get_node_from_key(contestantId);
    Node<int, Team> *team = teams.get_node_from_key(teamId);
    if (contestant == nullptr || team == nullptr) {
        return StatusType::FAILURE;
    }
    // contestant is not in the team
    if (contestant->get_data()->get_first_team() != teamId
        && contestant->get_data()->get_second_team() != teamId
        && contestant->get_data()->get_third_team() != teamId) {
        return StatusType::FAILURE;
    }
    try {
        int team1 = contestant->get_data()->get_first_team();
        int team2 = contestant->get_data()->get_second_team();
        int team3 = contestant->get_data()->get_third_team();

        team->get_data()->remove_contestant(contestantId);
        contestant->get_data()->get_num_of_teams()--; // update the team num for the contestant
        if (team1 == teamId) {
            contestant->get_data()->set_first_team(team2);
            contestant->get_data()->set_second_team(team3);
            contestant->get_data()->set_third_team(0);
        } else if (team2 == teamId) {
            contestant->get_data()->set_second_team(team3);
            contestant->get_data()->set_third_team(0);
        } else {
            contestant->get_data()->set_third_team(0);
        }
        return StatusType::SUCCESS;
    }
    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Olympics::update_contestant_strength(int contestantId, int change) {
    if (contestantId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    // Find contestant in the contestants tree
    Node<int, Contestant> *contestantNode = contestants.get_node_from_key(contestantId);
    if (contestantNode == nullptr) {
        return StatusType::FAILURE;
    }

    // Get the contestant and their old strength
    Strength_Obj &oldStrength = contestantNode->get_data()->get_strength_object();

    // Calculate the new strength
    int newStrengthValue = oldStrength.getStrength() + change;
    if (newStrengthValue < 0) {
        return StatusType::FAILURE;
    }
    Strength_Obj newStrength(newStrengthValue, contestantId);

    // Update the contestant's strength in each team
    if (contestantNode->get_data()->get_first_team() != 0) {// contestant has team
        Node<int, Team> *teamNode1 = teams.get_node_from_key(contestantNode->get_data()->get_first_team());
        teamNode1->get_data()->update_contestant_strength_in_team(teamNode1, contestantId, oldStrength, newStrength);
    }
    if (contestantNode->get_data()->get_second_team() != 0) {// contestant has team2
        Node<int, Team> *teamNode2 = teams.get_node_from_key(contestantNode->get_data()->get_second_team());
        teamNode2->get_data()->update_contestant_strength_in_team(teamNode2, contestantId, oldStrength, newStrength);
    }
    if (contestantNode->get_data()->get_third_team() != 0) {// contestant has team3
        Node<int, Team> *teamNode3 = teams.get_node_from_key(contestantNode->get_data()->get_third_team());
        teamNode3->get_data()->update_contestant_strength_in_team(teamNode3, contestantId, oldStrength, newStrength);
    }
    contestantNode->get_data()->set_strength(newStrengthValue);
    return StatusType::SUCCESS;
}

output_t<int> Olympics::get_strength(int contestantId) {
    // Implementation for get_strength
    if (contestantId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);
    try {
        Node<int, Contestant> *contestant = contestants.get_node_from_key(contestantId);
        if (contestant == nullptr) {
            //contestant doesnt exist
            return output_t<int>(StatusType::FAILURE);
        }
        //this means that contestant id is valid and the contestant is within the contestants
        return output_t<int>(contestant->get_data()->get_strength());
    }
    catch (const std::exception &e) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }

}

output_t<int> Olympics::get_medals(int countryId) {
    // Implementation for get_medals
    if (countryId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    try {
        Node<int, Country> *country = countries.get_node_from_key(countryId);
        if (country == nullptr) {
            return output_t<int>(StatusType::FAILURE);
        }

        return output_t<int>(country->get_data()->getNumMedals());

    }
    catch (const std::exception &e) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }

}

output_t<int> Olympics::get_team_strength(int teamId) {
    // Implementation for get_team_strength
    if (teamId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    try {
        Node<int, Team> *team = teams.get_node_from_key(teamId);
        if (team == nullptr) {
            return output_t<int>(StatusType::FAILURE);
        }
        if (team->get_data()->getNumContestants() % 3 != 0) {
            return output_t<int>(0);
        } else {
            int sum = team->get_data()->get_tree_strength1()->get_maxNode()->get_key().getStrength();
            sum += team->get_data()->get_tree_strength2()->get_maxNode()->get_key().getStrength();
            sum += team->get_data()->get_tree_strength3()->get_maxNode()->get_key().getStrength();
            return output_t<int>(sum);
        }

    }
    catch (const std::exception &e) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }

}

StatusType Olympics::play_match(int teamId1, int teamId2) {
    // Implementation for play_match
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Node<int, Team> *team1 = teams.get_node_from_key(teamId1);
        Node<int, Team> *team2 = teams.get_node_from_key(teamId2);
        if (team1 == nullptr || team2 == nullptr) {
            return StatusType::FAILURE;
        }
        if (team1->get_data()->get_sport() != team2->get_data()->get_sport()) {
            return StatusType::FAILURE;
        }
        Node<int, Country> *country1 = countries.get_node_from_key(team1->get_data()
                                                                           ->get_country()->get_data()->getCountryId());
        Node<int, Country> *country2 = countries.get_node_from_key(team2->get_data()
                                                                           ->get_country()->get_data()->getCountryId());
        output_t<int> team1_strength = get_team_strength(teamId1);
        output_t<int> team2_strength = get_team_strength(teamId2);
        int score1 = country1->get_data()->getNumMedals() + team1_strength.ans();
        int score2 = country2->get_data()->getNumMedals() + team2_strength.ans();
        if (score1 > score2) {
            country1->get_data()->getNumMedals()++;
        }
        if (score2 > score1) {
            country2->get_data()->getNumMedals()++;
        }
        return StatusType::SUCCESS;
    }
    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Olympics::unite_teams(int teamId1, int teamId2) {

    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }
    Node<int, Team> *team1 = teams.get_node_from_key(teamId1);
    Node<int, Team> *team2 = teams.get_node_from_key(teamId2);

    if (team1 == nullptr || team2 == nullptr) {
        return StatusType::FAILURE;
    }

    int num_of_contestants_in_team1 = team1->get_data()->getNumContestants();
    int num_of_contestants_in_team2 = team2->get_data()->getNumContestants();
    int num_of_contestants = num_of_contestants_in_team1 + num_of_contestants_in_team2;

    if (team1->get_data()->get_sport() != team2->get_data()->get_sport()) { // if the sports are different
        return StatusType::FAILURE;
    }
    // if the countries are different
    if (team1->get_data()->get_country()->get_data()->getCountryId() !=
        team2->get_data()->get_country()->get_data()->getCountryId()) {
        return StatusType::FAILURE;
    }
    try {
        // create 6 empty arrays of nodes ContestantObject
        // inorder traversal over 6 id trees and insert the nodes into the arrays

        BinaryTree<int, Contestant>* id_tree1_team1 = team1->get_data()->get_tree_id1();
        BinaryTree<int, Contestant>* id_tree2_team1 = team1->get_data()->get_tree_id2();
        BinaryTree<int, Contestant>* id_tree3_team1 = team1->get_data()->get_tree_id3();
        BinaryTree<Strength_Obj, int>* strength_tree1_team1 = team1->get_data()->get_tree_strength1();
        BinaryTree<Strength_Obj, int>* strength_tree2_team1 = team1->get_data()->get_tree_strength2();
        BinaryTree<Strength_Obj, int>* strength_tree3_team1 = team1->get_data()->get_tree_strength3();




        Node<int, Contestant> **contestantArray_team1 = team1->get_data()->sort_id_trees_to_array();
        Node<int, Contestant> **contestantArray_team2 = team2->get_data()->sort_id_trees_to_array();
        // merge the two arrays into one id array
        Node<int, Contestant> **idArray = BinaryTree<int, Contestant>::mergeArrays(contestantArray_team1, contestantArray_team2,
                                                                        num_of_contestants_in_team1,
                                                                        num_of_contestants_in_team2);



        Node<Strength_Obj, int> **strengthArray_team1 = team1->get_data()->sort_strength_trees_to_array();
        Node<Strength_Obj, int> **strengthArray_team2 = team2->get_data()->sort_strength_trees_to_array();
        // merge the two arrays into one strength array
        Node<Strength_Obj, int> **strengthArray = BinaryTree<Strength_Obj, int>::mergeArrays(strengthArray_team1,
                                                                                      strengthArray_team2,
                                                                                      num_of_contestants_in_team1,
                                                                                      num_of_contestants_in_team2);

        // now we have the new id array and the new strength array

        // we need to create 3 new trees from each array
        // we need to figure out how to divide the array according to the number of contestants

        int size1, size2, size3;
        if (num_of_contestants % 3 == 0) {
            int size = num_of_contestants / 3;
            size1 = size;
            size2 = size;
            size3 = size;
        } else if (num_of_contestants % 3 == 1) {
            int size = num_of_contestants / 3;
            size1 = size + 1;
            size2 = size;
            size3 = size;
        } else { // num_of_contestants % 3 == 2
            int size = num_of_contestants / 3;
            size1 = size + 1;
            size2 = size + 1;
            size3 = size;
        }

        // divide the new id array into 3 arrays
        // and perform TreeToArray on each of the 3 sections of the id array

        // delete the old trees of team1 so i can assign the new trees to be the team2's trees

        id_tree1_team1->set_root(id_tree1_team1->sortedArrayToTree(idArray, 0, size1 - 1, nullptr));
        id_tree1_team1->update_maxNode(id_tree1_team1->get_root());
        id_tree1_team1->update_minNode(id_tree1_team1->get_root());

        id_tree2_team1->set_root(id_tree2_team1->sortedArrayToTree(idArray+size1, 0, size2 - 1, nullptr));
        id_tree2_team1->update_maxNode(id_tree2_team1->get_root());
        id_tree2_team1->update_minNode(id_tree2_team1->get_root());

        id_tree3_team1->set_root(id_tree3_team1->sortedArrayToTree(idArray+size1+size2, 0,
                                                                   size3 - 1, nullptr));
        id_tree3_team1->update_maxNode(id_tree3_team1->get_root());
        id_tree3_team1->update_minNode(id_tree3_team1->get_root());

        auto** new_str_array1 = new Node<Strength_Obj, int>*[size1]();
        auto** new_str_array2 = new Node<Strength_Obj, int>*[size2]();
        auto** new_str_array3 = new Node<Strength_Obj, int>*[size3]();

        int index1 = 0, index2 = 0, index3 = 0;

        for (int i = 0; i < num_of_contestants; ++i) {
            int id = strengthArray[i]->get_key().getId();
            // for each node in the strength array, check which tree its id is in and insert it into the correct array
            if (id <= id_tree1_team1->get_maxNode()->get_key()) { // if the id is in tree1
                new_str_array1[index1++] = strengthArray[i];
            }
            else if ((id >= id_tree2_team1->get_minNode()->get_key()) &&
                     (id <= id_tree2_team1->get_maxNode()->get_key())) { // if the id is in tree2
                new_str_array2[index2++] = strengthArray[i];
            }
            else { // if the id is in tree3
                new_str_array3[index3++] = strengthArray[i];
            }
        }

        // perform BSTtreefromArray on each of the 3 sections of the strength array
        strength_tree1_team1->set_root(
                strength_tree1_team1->sortedArrayToTree(new_str_array1, 0, size1 - 1, nullptr));
        strength_tree1_team1->update_maxNode(strength_tree1_team1->get_root());
        strength_tree1_team1->update_minNode(strength_tree1_team1->get_root());

        strength_tree2_team1->set_root(
                strength_tree2_team1->sortedArrayToTree(new_str_array2, 0, size2-1, nullptr));
        strength_tree2_team1->update_maxNode(strength_tree2_team1->get_root());
        strength_tree2_team1->update_minNode(strength_tree2_team1->get_root());

        strength_tree3_team1->set_root(strength_tree3_team1->sortedArrayToTree(
                new_str_array3, 0,  size3 - 1, nullptr));
        strength_tree3_team1->update_maxNode(strength_tree3_team1->get_root());
        strength_tree3_team1->update_minNode(strength_tree3_team1->get_root());

        // now we have the 6 new trees for team2 after merging

        // delete team2
        teams.delete_key(team2->get_key());

        // update num_contestant for team2
        team1->get_data()->setNumContestants(num_of_contestants);


        return StatusType::SUCCESS;

    }
    catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> Olympics::austerity_measures(int teamId) {
    // we want to remove 3 contestants from the team with the lowest strength
    // we will iterate over 3 strength trees and remove the three nodes with the lowest strength
    //
    if (teamId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    try {
        Node<int, Team> *team = teams.get_node_from_key(teamId);
        if (team == nullptr) {
            return output_t<int>(StatusType::FAILURE);
        }
        if (team->get_data()->getNumContestants() < 3) {
            return output_t<int>(StatusType::FAILURE);
        }

    }
    catch (const std::exception &e) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
}


