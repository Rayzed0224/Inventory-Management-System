#include "blockchain.h"
#include "InventorySystem.h"
#include "UserSystem.h"
#include <iostream>
#include <chrono>
#include <thread>
#undef max

using namespace std;

int main() {
    srand((unsigned)time(nullptr));
    Blockchain supplyChain;
    UserSystem userSystem;
    InventorySystem inventorySystem(&supplyChain);

    bool running = true;
    bool randomDemandRunning = false;

    int choice;
    while (true) {
        clearScreen();
        cout << "1. Login\n2. Register User\n3. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 1 && userSystem.login()) break;
        if (choice == 2) userSystem.registerUser();
        if (choice == 3) return 0;
    }

    while (running) {
        clearScreen();
        cout << "===== SUPPLY CHAIN SYSTEM =====\n";
        cout << "1. View Inventory\n";
        cout << "2. View Demand\n";
        cout << "3. Toggle Random Demands (Currently: " << (randomDemandRunning ? "ON" : "OFF") << ")\n";
        cout << "4. Allocate Stock (Greedy)\n";
        cout << "5. View Blockchain\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: inventorySystem.viewInventory(); break;
        case 2: inventorySystem.viewDemand(); break;
        case 3: randomDemandRunning = !randomDemandRunning; cout << (randomDemandRunning ? "Random demand generation started.\n" : "Random demand generation stopped.\n"); break;
        case 4: inventorySystem.allocateStockGreedy(); break;
        case 5: supplyChain.displayChain(); break;
        case 6: running = false; break;
        default: cout << "Invalid choice.\n";
        }
        cout << "\nPress Enter to continue...";
        cin.ignore(); cin.get();

        if (randomDemandRunning) inventorySystem.generateRandomDemands(); // Controlled demand gen
    }
}
