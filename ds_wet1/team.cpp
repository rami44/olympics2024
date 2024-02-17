#include "team.h"
#include "Node.h"
// Constructor

Team::Team(int teamId, Sport sport, Node<int, Country> *country, int team_strength, int num_contestants):
        teamId(teamId), sport(sport), team_country(country),
        team_strength(team_strength), num_contestants(num_contestants), first_third_id(), second_third_id(),
        third_third_id(), first_third_strength(), second_third_strength(), third_third_strength() {}

void Team::delete_internal_trees() {
    first_third_id.delete_tree();
    second_third_id.delete_tree();
    third_third_id.delete_tree();
    first_third_strength.delete_tree();
    second_third_strength.delete_tree();
    third_third_strength.delete_tree();
}

// remove contestant
void Team::remove_contestant(int contestantId) {
    // find which tree contestant is in
    Node<int, Contestant> *node1 = first_third_id.get_node_from_key(contestantId);
    if (node1 != nullptr) { // if contestant is in first tree
        first_third_id.delete_key(contestantId);
        first_third_strength.delete_key(node1->get_data()->get_strength());
        // update trees
        if(first_third_id.get_numOfNodes() + 2 <= second_third_id.get_numOfNodes()){
            // after removing from first tree, we move from second to first
            move_node(second_third_id, first_third_id, second_third_strength, second_third_id.get_minNode());
        }
        num_contestants--;
        return;
    }
    Node<int, Contestant> *node2 = second_third_id.get_node_from_key(contestantId);
    if (node2 != nullptr) { // if contestant is in second tree
        second_third_id.delete_key(contestantId);
        second_third_strength.delete_key(node2->get_data()->get_strength());
        // update trees
        if(second_third_id.get_numOfNodes() + 2 <= third_third_id.get_numOfNodes()){
            // after removing from second tree, we move from third to second
            move_node(third_third_id, second_third_id, third_third_strength, third_third_id.get_minNode());
        }
        num_contestants--;
        return;
    }
    Node<int, Contestant> *node3 = third_third_id.get_node_from_key(contestantId);
    if (node3 != nullptr) { // if contestant is in third tree
        third_third_id.delete_key(contestantId);
        third_third_strength.delete_key(node3->get_data()->get_strength());
        // update trees
        if(third_third_id.get_numOfNodes() + 2 <= second_third_id.get_numOfNodes()){
            // after removing from third tree, we move from second to third
            move_node(second_third_id, third_third_id, second_third_strength, second_third_id.get_maxNode());
        }
        num_contestants--;
        return;
    }
}

// getters and setters

// get tree id1
BinaryTree<int, Contestant> *Team::get_tree_id1() {
    return &first_third_id;
}

// get tree id2
BinaryTree<int, Contestant> *Team::get_tree_id2() {
    return &second_third_id;
}

// get tree id3
BinaryTree<int, Contestant> *Team::get_tree_id3() {
    return &third_third_id;
}

// get tree strength1
BinaryTree<int, int> *Team::get_tree_strength1() {
    return &first_third_strength;
}

// get tree strength2

BinaryTree<int, int> *Team::get_tree_strength2() {
    return &second_third_strength;
}

// get tree strength3

BinaryTree<int, int> *Team::get_tree_strength3() {
    return &third_third_strength;
}


// get team_country

Node<int, Country> *Team::get_country() {
    return team_country;
}

// get team id
int Team::getTeamId() const {
    return teamId;
}

// get sport
Sport Team::get_sport() const {
    return sport;
}

// get team strength
int &Team::getTeamStrength() {
    return team_strength;
}


// get num contestant
int &Team::getNumContestants() {
    return num_contestants;
}

// template function to move node from one tree to another
void Team::move_node(BinaryTree<int, Contestant> &sourceTree_id, BinaryTree<int, Contestant> &destTree_id,
               BinaryTree<int, int> &sourceTree_strength, Node<int, Contestant> *moving_node) {

    int key = moving_node->get_key();
    std::shared_ptr<Contestant> data = moving_node->get_data();
    int strength = (*data).get_strength();

    sourceTree_id.delete_key(key); // delete max_second from 2 tree
    destTree_id.insert_key_and_data(key, data); // insert max_second to 3 tree
    // same thing for strength trees
    Node<int, int> *strength_node = sourceTree_strength.get_node_from_key(strength);
    (*strength_node->get_data())--;
    if (*strength_node->get_data() == 0) {
        sourceTree_strength.delete_key(strength);
    }
}

BinaryTree<int, Contestant> *Team::find_id_tree(int contestantId) {
    auto &tree1 = first_third_id;
    auto &tree2 = second_third_id;
    auto &tree3 = third_third_id;

    int size1 = tree1.get_numOfNodes();
    int size2 = tree2.get_numOfNodes();
    int size3 = tree3.get_numOfNodes();

    // if all trees are empty
    if (size1 == 0 && size2 == 0 && size3 == 0) return &tree1;

    if (size1 == 1 && size2 == 0 && size3 == 0) { // if tree1 has only one node and tree2 and tree3 are empty
        if (contestantId < tree1.get_minNode()->get_key()) {
            move_node(tree1, tree2,first_third_strength, tree1.get_minNode());
            return &tree1;
        } // contestantId > max1,
        else return &tree2;
    }
    if (size1 == 1 && size2 == 1 && size3 == 0) {
        // contestantId > max2 -> tree3
        if(contestantId > tree2.get_minNode()->get_key()) return &tree3;
        // max1 < contestantId < min2 -> tree2
        else if(contestantId < tree2.get_minNode()->get_key() && contestantId > tree1.get_maxNode()->get_key()) {
            move_node(tree2, tree3, second_third_strength, tree2.get_maxNode());
            return &tree2;
        }
        else { // contestantId < max1 -> tree1
            move_node(tree1, tree2, first_third_strength, tree1.get_maxNode()); // 1->2
            move_node(tree2, tree3, second_third_strength, tree2.get_maxNode()); // 2->3
            return &tree1;
        }
    }

    // if we arrive here, for sure we have at least 3 nodes in the trees one in each
    int min1 = tree1.get_minNode()->get_key();
    int min2 = tree2.get_minNode()->get_key();
    int min3 = tree3.get_minNode()->get_key();

    int max1 = tree1.get_maxNode()->get_key();
    int max2 = tree2.get_maxNode()->get_key();
    int max3 = tree3.get_maxNode()->get_key();

    if (size1 == size2 && size2 == size3) {
        if (contestantId < min2) return &tree1;
        if (contestantId < min3) return &tree2;
        return &tree3;
    }

    if (size1 == size2) {
        if (size3 < size1) { // remaining tree is smaller 3<1=2
            if (contestantId > max2) return &tree3;
            else if (contestantId > max1) {
                move_node(tree2, tree3, second_third_strength, tree2.get_maxNode());
                return &tree2;
            } else { // here we know that contestantId < max1
                move_node(tree2, tree3, second_third_strength, tree2.get_maxNode());
                move_node(tree1, tree2, first_third_strength, tree1.get_maxNode());
                return &tree1;
            }
        } else { // remaining tree is larger (size3 > size1) 3>1=2
            if (contestantId < min2) return &tree1;
            if (contestantId < min3) return &tree2;
            else { // contestantId > min3
                move_node(tree3, tree2, third_third_strength, tree3.get_minNode());
                return &tree3;
            }
        }
    }

    if (size2 == size3) {
        if (size1 < size2) {
            if (contestantId < min2) return &tree1;
            if (contestantId < min3) {
                move_node(tree2, tree1, second_third_strength, tree2.get_minNode());
                return &tree2;
            } else { // contestantId > min3
                move_node(tree2, tree1, second_third_strength, tree2.get_minNode()); // 2->1
                move_node(tree3, tree2, third_third_strength, tree3.get_minNode());// 3->2
                return &tree3;
            }
        } else { // (size1 > size2)
            if (contestantId > max2) return &tree3;
            if (contestantId > max1) return &tree2;
            else { // contestantId < max1
                move_node(tree1, tree2, first_third_strength, tree1.get_maxNode());
                return &tree1;
            }
        }
    }

    if (size1 == size3) {
        if (size2 < size1) {
            if (contestantId > max1 && contestantId < min3) return &tree2;
            else if (contestantId > min3) {
                move_node(tree3, tree2, third_third_strength, tree3.get_minNode());
                return &tree3;
            } else { // contestantId < max1
                move_node(tree1, tree2, first_third_strength, tree1.get_maxNode());
                return &tree1;
            }
        } else { // (size2 > size1)
            if (contestantId < min2) return &tree1;
            if (contestantId > max2) return &tree3;
            else { // min2 < contestantId < max2
                move_node(tree2, tree3, second_third_strength, tree2.get_maxNode());
                return &tree2;
            }
        }
    }
    return nullptr; // Handle any other cases as needed
}



// divide contestants into strength trees
void Team::add_contestant_to_tree(int contestantId, Sport sport, int strength) {

    BinaryTree<int, Contestant> *tree = find_id_tree(contestantId);

    BinaryTree<int, int> *strength_tree;

    if (tree == &first_third_id) {
        strength_tree = &first_third_strength;
    } else if (tree == &second_third_id) {
        strength_tree = &second_third_strength;
    } else {
        strength_tree = &third_third_strength;
    }
    std::shared_ptr<Contestant> new_contestant = std::make_shared<Contestant>(contestantId, sport, strength);
    tree->insert_key_and_data(contestantId, new_contestant);

    if (strength_tree->get_node_from_key(strength) == nullptr) {
        std::shared_ptr<int> one = std::make_shared<int>(1);
        strength_tree->insert_key_and_data(strength, one);
    } else {
        Node<int, int> *node = strength_tree->get_node_from_key(strength);
        (*node->get_data())++;
    }
}