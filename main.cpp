#include <iostream>
#include "SeatingPlan.h"

int main() {
    SeatingPlan plan;

    // Adding some initial guests
    plan.addGuest({"John", "Friend", "Window Seat"});
    plan.addGuest({"Jane", "Family", "Vegetarian"});
    plan.addGuest({"Alice", "Colleague", "Aisle Seat"});
    plan.addGuest({"Bob", "Family", "Window Seat"});
    plan.addGuest({"Eve", "Friend", "Vegetarian"});

    // Adding some relationships
    plan.addRelationship("John", "Jane");
    plan.addRelationship("Alice", "Bob");

    // Adding some tables with capacities
    plan.addTable(4); // Table 1
    plan.addTable(6); // Table 2

    // Assigning guests to tables
    plan.assignTables();

    // Displaying table assignments
    std::cout << "Initial Seating Arrangement:" << std::endl;
    plan.displayTables();

    // Performing manual adjustments
    std::cout << "\nPerforming Manual Adjustment:\n";
    plan.manualAdjustments("John", 6); // Move John to Table

    // Displaying updated table assignments
    std::cout << "\nUpdated Seating Arrangement:\n" << std::endl;
    plan.displayTables();

    // Displaying guest list
    //std::cout << "\nGuest List:\n";
    //plan.displayGuests();

    // Updating a guest
    plan.updateGuest("John", {"John", "Friend", "Center Seat"});
    std::cout << "\nAfter Update:\n";
    plan.displayGuests();

    // Removing a guest
    plan.removeGuest("Eve");
    std::cout << "\nAfter Removal:\n";
    plan.displayGuests();

    return 0;
}
