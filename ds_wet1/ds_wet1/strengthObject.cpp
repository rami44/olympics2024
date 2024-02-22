// Strength_Obj.cpp

#include "strengthObject.h"

// Constructor with parameters
Strength_Obj::Strength_Obj(int strength, int id) : strength(strength), id(id) {}

// Getter for strength
int Strength_Obj::getStrength() const {
    return strength;
}

// Setter for strength
void Strength_Obj::setStrength(int newStrength) {
    strength = newStrength;
}

// Getter for id
int Strength_Obj::getId() const {
    return id;
}

// Setter for id
void Strength_Obj::setId(int newId) {
    id = newId;
}

// Comparison operator <
bool Strength_Obj::operator<(const Strength_Obj& other) const {
    if (strength == other.strength) {
        // If strengths are equal, compare based on id
        return id < other.id;
    }
    // Otherwise, compare based on strength
    return strength < other.strength;
}

// Comparison operator >
bool Strength_Obj::operator>(const Strength_Obj& other) const {
    if (strength == other.strength) {
        // If strengths are equal, compare based on id
        return id > other.id;
    }
    // Otherwise, compare based on strength
    return strength > other.strength;
}

// Comparison operator ==
bool Strength_Obj::operator==(const Strength_Obj& other) const {
    return strength == other.strength && id == other.id;
}
