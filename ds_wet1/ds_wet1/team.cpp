#include "team.h"
#include "Node.h"
#include "strengthObject.h"
// Constructor

Team::Team(int teamId, Sport sport, Node<int, Country> *country, int team_strength, int num_contestants) :
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

//update the id trees after removing contestant with complexity of 0(1)
void Team::re_arrange_trees() {

    int size1 = first_third_id.get_numOfNodes();
    int size2 = second_third_id.get_numOfNodes();
    int size3 = third_third_id.get_numOfNodes();

    if (size1 - 2 >= size2) { // from tree1 to tree2
        move_node(first_third_id, second_third_id, first_third_strength, second_third_strength,
                  first_third_id.get_maxNode());
        return;
    }
    if (size1 - 2 >= size3) {  // from tree1 to tree2 and from tree2 to tree3
        move_node(first_third_id, second_third_id, first_third_strength, second_third_strength,
                  first_third_id.get_maxNode());
        move_node(second_third_id, third_third_id, second_third_strength, third_third_strength,
                  second_third_id.get_maxNode());
        return;
    }
    if (size2 - 2 >= size3) { // from tree2 to tree3
        move_node(second_third_id, third_third_id, second_third_strength, third_third_strength,
                  second_third_id.get_maxNode());
        return;
    }
    if (size2 - 2 >= size1) { // from tree2 to tree1
        move_node(second_third_id, first_third_id, second_third_strength, first_third_strength,
                  second_third_id.get_minNode());
        return;
    }
    if (size3 - 2 >= size2) { // from tree3 to tree2
        move_node(third_third_id, second_third_id, third_third_strength, second_third_strength,
                  third_third_id.get_minNode());
        return;
    }
    if (size3 - 2 >= size1) { // from tree3 to tree2 and from tree2 to tree1
        move_node(third_third_id, second_third_id, third_third_strength, second_third_strength,
                  third_third_id.get_minNode());
        move_node(second_third_id, first_third_id, second_third_strength, first_third_strength,
                  second_third_id.get_minNode());
        return;
    }
}

void Team::update_strength(Strength_Obj &old_strength, Strength_Obj &new_strength,
                           BinaryTree<Strength_Obj, int> &tree) {
    // find node with old strength
    Node<Strength_Obj, int> *node = tree.get_node_from_key(old_strength);
    if (node != nullptr) {
        tree.delete_key(old_strength);
    }
    std::shared_ptr<int> contestantId = node->get_data(); // contestant id

    // insert new strength
    tree.insert_key_and_data(new_strength, contestantId);
}

// remove contestant
void Team::remove_contestant(int contestantId) {
    // find which tree contestant is in
    Node<int, Contestant> *node1 = first_third_id.get_node_from_key(contestantId);
    if (node1 != nullptr) { // if contestant is in first tree
        first_third_strength.delete_key(node1->get_data()->get_strength_object());
        //after updating strength, we may need to rearrange between trees
        first_third_id.delete_key(contestantId);
        re_arrange_trees();
        num_contestants--;
        return;
    }
    Node<int, Contestant> *node2 = second_third_id.get_node_from_key(contestantId);
    if (node2 != nullptr) { // if contestant is in second tree
        second_third_strength.delete_key(node2->get_data()->get_strength_object());
        //after updating strength, we may need to rearrange between trees
        second_third_id.delete_key(contestantId);
        re_arrange_trees();
        num_contestants--;
        return;
    }
    Node<int, Contestant> *node3 = third_third_id.get_node_from_key(contestantId);
    if (node3 != nullptr) { // if contestant is in third tree
        third_third_strength.delete_key(node3->get_data()->get_strength_object());
        //after updating strength, we may need to rearrange between trees
        third_third_id.delete_key(contestantId);
        re_arrange_trees();
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
BinaryTree<Strength_Obj, int> *Team::get_tree_strength1() {
    return &first_third_strength;
}

// get tree strength2

BinaryTree<Strength_Obj, int> *Team::get_tree_strength2() {
    return &second_third_strength;
}

// get tree strength3

BinaryTree<Strength_Obj, int> *Team::get_tree_strength3() {
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

// set num contestants
void Team::setNumContestants(int numContestants) {
    Team::num_contestants = numContestants;
}

// template function to move node from one tree to another
void Team::move_node(BinaryTree<int, Contestant> &sourceTree_id, BinaryTree<int, Contestant> &destTree_id,
                     BinaryTree<Strength_Obj, int> &sourceTree_strength,
                     BinaryTree<Strength_Obj, int> &desTree_strength, Node<int, Contestant> *moving_node) {

    int key = moving_node->get_key();
    std::shared_ptr<Contestant> data = moving_node->get_data();
    Strength_Obj &strength = moving_node->get_data()->get_strength_object(); // strengthobject of moving

    sourceTree_id.delete_key(key); // delete from id source tree
    destTree_id.insert_key_and_data(key, data); // insert to id destination tree

    sourceTree_strength.delete_key(strength); // delete from strength source tree

    std::shared_ptr<int> contestant_id = std::make_shared<int>(key);
    desTree_strength.insert_key_and_data(strength, contestant_id); // insert to strength destination tree

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
            move_node(tree1, tree2, first_third_strength, second_third_strength, tree1.get_minNode());
            return &tree1;
        } // contestantId > max1,
        else return &tree2;
    }
    if (size1 == 1 && size2 == 1 && size3 == 0) {
        // contestantId > max2 -> tree3
        if (contestantId > tree2.get_minNode()->get_key()) return &tree3;
            // max1 < contestantId < min2 -> tree2
        else if (contestantId < tree2.get_minNode()->get_key() && contestantId > tree1.get_maxNode()->get_key()) {
            move_node(tree2, tree3, second_third_strength, third_third_strength, tree2.get_maxNode());
            return &tree2;
        } else { // contestantId < max1 -> tree1
            move_node(tree1, tree2, first_third_strength, second_third_strength, tree1.get_maxNode()); // 1->2
            move_node(tree2, tree3, second_third_strength, third_third_strength, tree2.get_maxNode()); // 2->3
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
                move_node(tree2, tree3, second_third_strength, third_third_strength, tree2.get_maxNode());
                return &tree2;
            } else { // here we know that contestantId < max1
                move_node(tree2, tree3, second_third_strength, third_third_strength, tree2.get_maxNode());
                move_node(tree1, tree2, first_third_strength, second_third_strength, tree1.get_maxNode());
                return &tree1;
            }
        } else { // remaining tree is larger (size3 > size1) 3>1=2
            if (contestantId < min2) return &tree1;
            if (contestantId < min3) return &tree2;
            else { // contestantId > min3
                move_node(tree3, tree2, third_third_strength, second_third_strength, tree3.get_minNode());
                return &tree3;
            }
        }
    }

    if (size2 == size3) {
        if (size1 < size2) {
            if (contestantId < min2) return &tree1;
            if (contestantId < min3) {
                move_node(tree2, tree1, second_third_strength, first_third_strength, tree2.get_minNode());
                return &tree2;
            } else { // contestantId > min3
                move_node(tree2, tree1, second_third_strength, first_third_strength, tree2.get_minNode()); // 2->1
                move_node(tree3, tree2, third_third_strength, second_third_strength, tree3.get_minNode());// 3->2
                return &tree3;
            }
        } else { // (size1 > size2)
            if (contestantId > max2) return &tree3;
            if (contestantId > max1) return &tree2;
            else { // contestantId < max1
                move_node(tree1, tree2, first_third_strength, second_third_strength, tree1.get_maxNode());
                return &tree1;
            }
        }
    }

    if (size1 == size3) {
        if (size2 < size1) {
            if (contestantId > max1 && contestantId < min3) return &tree2;
            else if (contestantId > min3) {
                move_node(tree3, tree2, third_third_strength, second_third_strength, tree3.get_minNode());
                return &tree3;
            } else { // contestantId < max1
                move_node(tree1, tree2, first_third_strength, second_third_strength, tree1.get_maxNode());
                return &tree1;
            }
        } else { // (size2 > size1)
            if (contestantId < min2) return &tree1;
            if (contestantId > max2) return &tree3;
            else { // min2 < contestantId < max2
                move_node(tree2, tree3, second_third_strength, third_third_strength, tree2.get_maxNode());
                return &tree2;
            }
        }
    }
    return nullptr; // Handle any other cases as needed
}

// divide contestants into strength trees
void Team::add_contestant_to_tree(std::shared_ptr<Contestant> contestant) {

    BinaryTree<int, Contestant> *tree = find_id_tree(contestant->get_id());

    BinaryTree<Strength_Obj, int> *strength_tree;

    if (tree == &first_third_id) {
        strength_tree = &first_third_strength;
    } else if (tree == &second_third_id) {
        strength_tree = &second_third_strength;
    } else {
        strength_tree = &third_third_strength;
    }
    tree->insert_key_and_data(contestant->get_id(), contestant);
    std::shared_ptr<int> contestant_id = std::make_shared<int>(contestant->get_id());
    strength_tree->insert_key_and_data(contestant->get_strength_object(), contestant_id);
}

void Team::update_contestant_strength_in_team(Node<int, Team> *teamNode, int contestantId,
                                              Strength_Obj &oldStrength, Strength_Obj &newStrength) {
    if (teamNode == nullptr) {
        return;
    }
    // find the tree of contestant
    Node<int, Contestant> *contestant_in_tree1 = teamNode->get_data()->get_tree_id1()->get_node_from_key(contestantId);
    if (contestant_in_tree1 != nullptr) { // contestant is in tree1
        teamNode->get_data()->update_strength(oldStrength, newStrength, *teamNode->get_data()->get_tree_strength1());
    }
    Node<int, Contestant> *contestant_in_tree2 = teamNode->get_data()->get_tree_id2()->get_node_from_key(contestantId);
    if (contestant_in_tree2 != nullptr) { // contestant is in tree2
        teamNode->get_data()->update_strength(oldStrength, newStrength, *teamNode->get_data()->get_tree_strength2());
    }
    Node<int, Contestant> *contestant_in_tree3 = teamNode->get_data()->get_tree_id3()->get_node_from_key(contestantId);
    if (contestant_in_tree3 != nullptr) { // contestant is in tree3
        teamNode->get_data()->update_strength(oldStrength, newStrength, *teamNode->get_data()->get_tree_strength3());
    }


}

Node<int, Contestant> **Team::sort_id_trees_to_array() {
    int size1 = first_third_id.get_numOfNodes();
    int size2 = second_third_id.get_numOfNodes();
    int size3 = third_third_id.get_numOfNodes();

    // Allocate memory for arrays
    Node<int, Contestant> **first_array = new Node<int, Contestant> *[size1]();
    Node<int, Contestant> **second_array = new Node<int, Contestant> *[size2]();
    Node<int, Contestant> **third_array = new Node<int, Contestant> *[size3]();

    // Fill the arrays with nodes
    int index1 = 0;
    first_third_id.storeInorderNodes(first_third_id.get_root(), first_array, &index1);

    int index2 = 0;
    second_third_id.storeInorderNodes(second_third_id.get_root(), second_array, &index2);

    int index3 = 0;
    third_third_id.storeInorderNodes(third_third_id.get_root(), third_array, &index3);

    // Merge first_array and second_array
    Node<int, Contestant> **mergedArray1 = first_third_id.mergeArrays(first_array, second_array, size1, size2);

    // Merge mergedArray1 and third_array
    Node<int, Contestant> **finalMergedArray = first_third_id.mergeArrays(mergedArray1, third_array, size1 + size2,
                                                                          size3);

    // Clean up memory
    delete[] first_array;
    delete[] second_array;
    delete[] third_array;
    delete[] mergedArray1;

    return finalMergedArray;
}

Node<Strength_Obj, int> **Team::sort_strength_trees_to_array() {
    int size1 = first_third_strength.get_numOfNodes();
    int size2 = second_third_strength.get_numOfNodes();
    int size3 = third_third_strength.get_numOfNodes();

    // Allocate memory for arrays
    Node<Strength_Obj, int> **first_array = new Node<Strength_Obj, int> *[size1]();
    Node<Strength_Obj, int> **second_array = new Node<Strength_Obj, int> *[size2]();
    Node<Strength_Obj, int> **third_array = new Node<Strength_Obj, int> *[size3]();

    // Fill the arrays with nodes
    int index1 = 0;
    first_third_strength.storeInorderNodes(first_third_strength.get_root(), first_array, &index1);

    int index2 = 0;
    second_third_strength.storeInorderNodes(second_third_strength.get_root(), second_array, &index2);

    int index3 = 0;
    third_third_strength.storeInorderNodes(third_third_strength.get_root(), third_array, &index3);

    // Merge first_array and second_array
    Node<Strength_Obj, int> **mergedArray1 = first_third_strength.mergeArrays(first_array, second_array, size1, size2);

    // Merge mergedArray1 and third_array
    Node<Strength_Obj, int> **finalMergedArray = first_third_strength.mergeArrays(mergedArray1, third_array,
                                                                                  size1 + size2, size3);

    // Clean up memory
    delete[] first_array;
    delete[] second_array;
    delete[] third_array;
    delete[] mergedArray1;

    return finalMergedArray;
}
