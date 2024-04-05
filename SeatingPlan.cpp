#include "SeatingPlan.h"
#include "Structures.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <functional> 

SeatingPlan::SeatingPlan() : root(nullptr) {}

void SeatingPlan::addGuest(const Guest& guest) {
    guests.push_back(guest);
    guestRelationships[guest.name] = {};
}

void SeatingPlan::addTable(int capacity) {
    insertTable(root, {capacity, {}});
}

void SeatingPlan::insertTable(TreeNode*& node, const Table& table) {
    if (node == nullptr) {
        node = new TreeNode{table, nullptr, nullptr};
    } else {
        if (table.capacity < node->table.capacity) {
            insertTable(node->left, table);
        } else {
            insertTable(node->right, table);
        }
    }
}

void SeatingPlan::addRelationship(const std::string& guest1, const std::string& guest2) {
    guestRelationships[guest1].push_back(guest2);
    guestRelationships[guest2].push_back(guest1);
}

void SeatingPlan::updateGuest(const std::string& name, const Guest& updatedGuest) {
    for (auto& guest : guests) {
        if (guest.name == name) {
            guest = updatedGuest;
            break;
        }
    }
}

void SeatingPlan::removeGuest(const std::string& name) {
    guests.erase(std::remove_if(guests.begin(), guests.end(), [&](const Guest& guest) {
        return guest.name == name;
    }), guests.end());
    guestRelationships.erase(name); 
    // Remove relationships of the deleted guest
}

void SeatingPlan::assignTables() {
    // Sort guests based on preferences (e.g., Window Seat first)
    std::sort(guests.begin(), guests.end(), [](const Guest& a, const Guest& b) {
        return a.preference < b.preference;
    });

    for (const auto& guest : guests) {
        assignGuest(root, guest);
    }
}

void SeatingPlan::assignGuest(TreeNode* node, const Guest& guest) {
    if (node == nullptr) {
        return;
    }

    if (node->table.capacity > node->table.assignedGuests.size()) {
        node->table.assignedGuests.push_back(guest);
    } else {
        // Recursively try to assign the guest to the left and right subtrees
        assignGuest(node->left, guest);
        assignGuest(node->right, guest);
    }
}

void SeatingPlan::displayTables(TreeNode* node) const {
    if (node != nullptr) {
        displayTables(node->left);
        std::cout << "Table (Capacity: " << node->table.capacity << "):" << std::endl;
        for (const auto& guest : node->table.assignedGuests) {
            std::cout << "- " << guest.name << " (" << guest.relationship << ", " << guest.preference << ")" << std::endl;
        }
        std::cout << std::endl;
        displayTables(node->right);
    }
}

void SeatingPlan::manualAdjustments(const std::string& guestName, int destinationTableCapacity) {
    removeGuestFromTables(root, guestName);
    assignGuestToTable(root, guestName, destinationTableCapacity);
}

void SeatingPlan::removeGuestFromTables(TreeNode* node, const std::string& guestName) {
    if (node == nullptr) {
        return;
    }

    auto& guests = node->table.assignedGuests;
    guests.erase(std::remove_if(guests.begin(), guests.end(), [&](const Guest& guest) {
        return guest.name == guestName;
    }), guests.end());

    removeGuestFromTables(node->left, guestName);
    removeGuestFromTables(node->right, guestName);
}

void SeatingPlan::assignGuestToTable(TreeNode* node, const std::string& guestName, int capacity) {
    if (node == nullptr) {
        return;
    }

    if (node->table.capacity == capacity) {
        auto guestIter = std::find_if(guests.begin(), guests.end(), [&](const Guest& guest) {
            return guest.name == guestName;
        });

        if (guestIter != guests.end()) {
            node->table.assignedGuests.push_back(*guestIter);
        } else {
            std::cout << "Guest not found." << std::endl;
        }
    } else if (capacity < node->table.capacity) {
        assignGuestToTable(node->left, guestName, capacity);
    } else {
        assignGuestToTable(node->right, guestName, capacity);
    }
}

void SeatingPlan::displayGuests() const {
    std::cout << "Guest List:\n";
    std::cout << "-----------\n";
    for (const auto& guest : guests) {
        std::cout << "Name: " << guest.name << ", Relationship: " << guest.relationship << ", Preference: " << guest.preference << std::endl;
    }
}

void SeatingPlan::displayTables() const {
    std::cout << "Table Assignments:\n";
    std::cout << "------------------\n";
    displayTables(root);
}
