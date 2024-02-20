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
        team->get_data()->add_contestant_to_tree(contestantId, team->get_data()->get_sport(),
                                                 contestant->get_data()->get_strength());
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
    if (contestant->get_data()->get_first_team() != teamId
        && contestant->get_data()->get_second_team() != teamId
        && contestant->get_data()->get_third_team() != teamId) {
        return StatusType::FAILURE;
    }
    try {
        team->get_data()->remove_contestant(contestantId);
        contestant->get_data()->get_num_of_teams()--; // update the team num for the contestant
        if (contestant->get_data()->get_first_team() == teamId) {
            contestant->get_data()->set_first_team(0);
        } else if (contestant->get_data()->get_second_team() == teamId) {
            contestant->get_data()->set_second_team(0);
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
    // Implementation for update_contestant_strength
    if (contestantId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    // find contestant in the contestants tree
    Node<int, Contestant> *contestant = contestants.get_node_from_key(contestantId);
    if (contestant == nullptr) {
        return StatusType::FAILURE;
    }
    // if we get here, contestant exists
    int old_strength = contestant->get_data()->get_strength();
    int new_strength = contestant->get_data()->get_strength() + change;
    if(new_strength<0){
        return StatusType::INVALID_INPUT;
    }

    // now for each of the teams that contestant belongs to, we need to update the contestant strength in his tree
    // for each of the teams that he is a part of we need to find which tree he is in and update his strength
    if (contestant->get_data()->get_first_team() != 0) { // team1 exists
        // find which strength_tree of team contestant belongs to
        Node<int, Team> *team1 = teams.get_node_from_key(contestant->get_data()->get_first_team()); // team1 from teams
        // find the tree of contestant
        Node<int, Contestant> *contestant_in_tree1 = team1->get_data()->get_tree_id1()->get_node_from_key(contestantId);
        if (contestant_in_tree1 != nullptr) { // contestant is in tree1
            team1->get_data()->update_strength(old_strength, new_strength, *team1->get_data()->get_tree_strength1());
        }
        Node<int, Contestant> *contestant_in_tree2 = team1->get_data()->get_tree_id2()->get_node_from_key(contestantId);
        if (contestant_in_tree2 != nullptr) { // contestant is in tree2
            team1->get_data()->update_strength(old_strength, new_strength, *team1->get_data()->get_tree_strength2());
        }
        Node<int, Contestant> *contestant_in_tree3 = team1->get_data()->get_tree_id3()->get_node_from_key(contestantId);
        if (contestant_in_tree3 != nullptr) { // contestant is in tree3
            team1->get_data()->update_strength(old_strength, new_strength, *team1->get_data()->get_tree_strength3());
        }
    }
    // Team2
    if (contestant->get_data()->get_second_team() != 0) { // team2 exists
        // contestant is in tree2
        Node<int, Team> *team2 = teams.get_node_from_key(contestant->get_data()->get_second_team());
        // find the tree of contestant
        Node<int, Contestant> *contestant_in_tree1 = team2->get_data()->get_tree_id1()->get_node_from_key(contestantId);
        if (contestant_in_tree1 != nullptr) { // contestant is in tree2
            team2->get_data()->update_strength(old_strength, new_strength, *team2->get_data()->get_tree_strength1());
        }
        Node<int, Contestant> *contestant_in_tree2 = team2->get_data()->get_tree_id2()->get_node_from_key(contestantId);
        if (contestant_in_tree2 != nullptr) { // contestant is in tree2
            team2->get_data()->update_strength(old_strength, new_strength, *team2->get_data()->get_tree_strength2());
        }
        Node<int, Contestant> *contestant_in_tree3 = team2->get_data()->get_tree_id3()->get_node_from_key(contestantId);
        if (contestant_in_tree3 != nullptr) { // contestant is in tree3
            team2->get_data()->update_strength(old_strength, new_strength, *team2->get_data()->get_tree_strength3());
        }
    }
    if (contestant->get_data()->get_third_team() != 0) { // team3 exists
        Node<int, Team> *team3 = teams.get_node_from_key(contestant->get_data()->get_third_team());
        // find the tree of contestant
        Node<int, Contestant> *contestant_in_tree1 = team3->get_data()->get_tree_id1()->get_node_from_key(contestantId);
        if (contestant_in_tree1 != nullptr) { // contestant is in tree3
            team3->get_data()->update_strength(old_strength, new_strength, *team3->get_data()->get_tree_strength1());
        }
        Node<int, Contestant> *contestant_in_tree2 = team3->get_data()->get_tree_id2()->get_node_from_key(contestantId);
        if (contestant_in_tree2 != nullptr) { // contestant is in tree3
            team3->get_data()->update_strength(old_strength, new_strength, *team3->get_data()->get_tree_strength2());
        }
        Node<int, Contestant> *contestant_in_tree3 = team3->get_data()->get_tree_id3()->get_node_from_key(contestantId);
        if (contestant_in_tree3 != nullptr) { // contestant is in tree3
            team3->get_data()->update_strength(old_strength, new_strength, *team3->get_data()->get_tree_strength3());
        }
    }
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
            int sum = team->get_data()->get_tree_strength1()->get_maxNode()->get_key();
            sum += team->get_data()->get_tree_strength2()->get_maxNode()->get_key();
            sum += team->get_data()->get_tree_strength3()->get_maxNode()->get_key();
            return output_t<int>(sum);
        }

    }
    catch (const std::exception &e) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }

}

StatusType Olympics::unite_teams(int teamId1, int teamId2) {
    // Implementation for unite_teams
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

output_t<int> Olympics::austerity_measures(int teamId) {
    // we want to remove 3 contestants from the team with the lowest strength
    // we will iterate over 3 strength trees and remove the three nodes with the lowest strength
    //
}


