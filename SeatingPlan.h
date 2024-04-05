#ifndef SEATINGPLAN_H
#define SEATINGPLAN_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Structures.h"

// Define a TreeNode structure for the binary tree
struct TreeNode {
    Table table;
    TreeNode* left;
    TreeNode* right;
};

class SeatingPlan {
private:
    std::vector<Guest> guests;
    TreeNode* root; // Root of the binary tree
    std::unordered_map<std::string, std::vector<std::string>> guestRelationships;

public:
    SeatingPlan();

    void addGuest(const Guest& guest);

    void addTable(int capacity);

    void insertTable(TreeNode*& node, const Table& table);

    void addRelationship(const std::string& guest1, const std::string& guest2);

    void updateGuest(const std::string& name, const Guest& updatedGuest);

    void removeGuest(const std::string& name);

    void assignTables();

    void assignGuest(TreeNode* node, const Guest& guest);

    void displayTables(TreeNode* node) const;

    void manualAdjustments(const std::string& guestName, int destinationTableCapacity);

    void removeGuestFromTables(TreeNode* node, const std::string& guestName);

    void assignGuestToTable(TreeNode* node, const std::string& guestName, int capacity);

    void displayGuests() const;

    void displayTables() const;
};

#endif // SEATINGPLAN_H
