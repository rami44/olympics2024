// Strength_Obj.h
#ifndef STRENGTH_OBJ_H
#define STRENGTH_OBJ_H

#include <iostream>

class Strength_Obj {
private:
    int strength;
    int id;

public:
    Strength_Obj(int strength, int id);

    // Getter for strength
    int getStrength() const;

    // Setter for strength
    void setStrength(int newStrength);

    // Getter for id
    int getId() const;

    // Setter for id
    void setId(int newId);

    // Comparison operator <
    bool operator<(const Strength_Obj &other) const;

    // Comparison operator >
    bool operator>(const Strength_Obj &other) const;

    // Comparison operator ==
    bool operator==(const Strength_Obj &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Strength_Obj &s);
};

std::ostream &operator<<(std::ostream &os, const Strength_Obj &s) {
    os << "(" << s.strength << "," << s.id << ") ";
}

#endif // STRENGTH_OBJ_H

















