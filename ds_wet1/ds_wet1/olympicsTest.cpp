#include <iostream>
#include "binary_tree.h" // Include the BinaryTree header file
#include "Node.h" // Include the Node header file
#include "wet1util.h" // Include the wet1util header file
#include "country.h" // Include the country header file
#include "team.h"
#include "Olympicsa1.h"
#include "StrengthObject.h"


using namespace std;

template <class Key, class Data>
void print_node(const Node<Key, Data> *node, std::ostream &os = std::cout) {
    os << " yes";
}

int main() {
    // Create an instance of the Olympics class
    Olympics olympics;

    // Test adding a country
    StatusType result1 = olympics.add_country(1, 5); // Adding a country with ID 1 and 5 medals
    if (result1 != StatusType::SUCCESS) {
        std::cerr << "Failed to add country." << std::endl;
        return 1; // Return non-zero to indicate failure
    }
    std::cout << "Country added successfully." << std::endl;

    // add another country
    StatusType result1_1 = olympics.add_country(2, 5); // Adding a country with ID 1 and 5 medals
    if (result1_1 != StatusType::SUCCESS) {
        std::cerr << "Failed to add country." << std::endl;
        return 1; // Return non-zero to indicate failure
    }
    std::cout << "Country added successfully." << std::endl;

    // Test adding a team
    StatusType result2 = olympics.add_team(101, 1, Sport::FOOTBALL); // Adding a team with ID 101 associated with country 1 and sport tennis
    if (result2 != StatusType::SUCCESS) {
        std::cerr << "Failed to add team." << std::endl;
        return 1; // Return non-zero to indicate failure
    }
    std::cout << "Team added successfully." << std::endl;

    // add another team

    StatusType result2_1 = olympics.add_team(102, 1, Sport::FOOTBALL); // Adding a team with ID 101 associated with country 1 and sport tennis
    if (result2_1 != StatusType::SUCCESS) {
        std::cerr << "Failed to add team." << std::endl;
        return 1; // Return non-zero to indicate failure
    }
    std::cout << "Team added successfully." << std::endl;


    // Test adding contestants to the team
    StatusType result3_1 = olympics.add_contestant(1001, 1, Sport::FOOTBALL, 80); // Add a contestant with ID 1001 to country 1, sport tennis, and strength 80
    StatusType result3_2 = olympics.add_contestant(1002, 1, Sport::FOOTBALL, 85); // Add a contestant with ID 1002 to country 1, sport tennis, and strength 85
    StatusType result3_3 = olympics.add_contestant(1003, 1, Sport::FOOTBALL, 90); // Add a contestant with ID 1003 to country 1, sport tennis, and strength 90
    StatusType result3_4 = olympics.add_contestant(1004, 1, Sport::FOOTBALL, 95); // Add a contestant with ID 1003 to country 1, sport tennis, and strength 90

    if (result3_1 != StatusType::SUCCESS || result3_2 != StatusType::SUCCESS || result3_3 != StatusType::SUCCESS || result3_4 != StatusType::SUCCESS) {
        std::cerr << "Failed to add contestants." << std::endl;
        return 1; // Return non-zero to indicate failure
    }
    std::cout << "Contestants added successfully." << std::endl;

    // Test adding contestants to the team
    StatusType result4_1 = olympics.add_contestant_to_team(101, 1001); // Add contestant 1001 to team 101
    StatusType result4_2 = olympics.add_contestant_to_team(101, 1002); // Add contestant 1002 to team 101
    olympics.add_contestant_to_team(102, 1003); // Add contestant 1003 to team 101
    olympics.add_contestant_to_team(102, 1004); // Add contestant 1003 to team 101

    Node<int, Team>* team1 = olympics.teams.get_node_from_key(101);

    std::cout << "team1 num_contestants: " << team1->get_data()->getNumContestants() << std::endl;


    std::cout << "Contestants added to team successfully." << std::endl;

    std::cout << "teams tree." << std::endl;
    olympics.teams.pre_order(print_node<int, Team>, olympics.teams.get_root());
    std::cout << std::endl;

    // print countries tree
    std::cout << "countries tree." << std::endl;
    olympics.countries.pre_order(print_node<int, Country>, olympics.countries.get_root());
    std::cout << std::endl;

    // print contestants
    std::cout << "contestants tree." << std::endl;
    olympics.contestants.pre_order(print_node<int, Contestant>, olympics.contestants.get_root());
    std::cout << std::endl;


    // print tree1
    std::cout << "tree1_id" << std::endl;
    olympics.teams.get_root()->get_data()->get_tree_id1()->pre_order(print_node<int, Contestant>,
            olympics.teams.get_root()->get_data()->get_tree_id1()->get_root());
    std::cout << std::endl;

    std::cout << "tree2_id" << std::endl;
    olympics.teams.get_root()->get_data()->get_tree_id2()->pre_order(print_node<int, Contestant>,
            olympics.teams.get_root()->get_data()->get_tree_id2()->get_root());
    std::cout << std::endl;

    // print tree3
    std::cout << "tree3_id" << std::endl;
    olympics.teams.get_root()->get_data()->get_tree_id3()->pre_order(print_node<int, Contestant>,
            olympics.teams.get_root()->get_data()->get_tree_id3()->get_root());
    std::cout << std::endl;

    // print tree1 strength
    std::cout << "tree1_strength" << std::endl;
    olympics.teams.get_root()->get_data()->get_tree_strength1()->pre_order(print_node<Strength_Obj, int>,
            olympics.teams.get_root()->get_data()->get_tree_strength1()->get_root());
    std::cout << std::endl;

    // print tree2 strength
    std::cout << "tree2_strength" << std::endl;
    olympics.teams.get_root()->get_data()->get_tree_strength2()->pre_order(print_node<Strength_Obj, int>,
            olympics.teams.get_root()->get_data()->get_tree_strength2()->get_root());
    std::cout << std::endl;

    std::cout << "tree3_strength" << std::endl;
    olympics.teams.get_root()->get_data()->get_tree_strength3()->pre_order(print_node<Strength_Obj, int>,
            olympics.teams.get_root()->get_data()->get_tree_strength3()->get_root());
    std::cout << std::endl;

    olympics.unite_teams(101, 102); // Unite teams 101 and 102

    // print id of team 101 and 102

    Node<int, Team>* team = olympics.teams.get_node_from_key(101);

    std::cout << "team1 id: " << team->get_data()->getTeamId() << std::endl;
    // print team2 num_contestants
    std::cout << "team1 num_contestants after unite: " << team1->get_data()->getNumContestants() << std::endl;

    // print team2 num_contestants
    Node<int, Team>* team2 = olympics.teams.get_node_from_key(102);
    if(team2 == nullptr){
        std::cout << "team2 is null" << std::endl;
    }
    else {
        std::cout << "team2 num_contestants after unite: " << team2->get_data()->getNumContestants() << std::endl;
    }
    return 0; // Return zero to indicate success
}