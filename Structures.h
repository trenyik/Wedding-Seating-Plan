#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>

// Define a Guest structure to store guest details
struct Guest {
    std::string name;
    std::string relationship;
    std::string preference;
};

// Define a Table structure to store table details
struct Table {
    int capacity;
    std::vector<Guest> assignedGuests;
};

#endif // STRUCTURES_H
