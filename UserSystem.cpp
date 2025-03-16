#include "blockchain.h"
#include "UserSystem.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

UserSystem::UserSystem() {
    userFile = "users.json"; // Now JSON!
    loadUsers();
}

void UserSystem::loadUsers() {
    ifstream file(userFile);
    if (!file) {
        cout << "No user data found. Initializing...\n";
        return;
    }
    json j;
    file >> j;
    users.clear();
    for (auto& [username, role] : j.items()) users[username] = role;
}

void UserSystem::saveUsers() {
    json j;
    for (auto& user : users) j[user.first] = user.second;
    ofstream(userFile) << j.dump(4);
}

bool UserSystem::login() {
    string username;
    cout << "Enter username: ";
    cin >> username;
    if (users.find(username) != users.end()) {
        currentUser = username;
        currentRole = users[username];
        cout << "Login successful. Role: " << currentRole << "\n";
        return true;
    }
    else {
        cout << "User not found.\n";
        return false;
    }
}

void UserSystem::registerUser() {
    string username, role;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter role (Admin, Store, Transporter, Distributor): ";
    cin >> role;
    users[username] = role;
    saveUsers();
    cout << "User registered successfully!\n";
}

void UserSystem::logout() {
    currentUser = "";
    currentRole = "";
    cout << "Logged out successfully. Returning to login screen...\n";
}
