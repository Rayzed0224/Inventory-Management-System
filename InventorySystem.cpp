#include "InventorySystem.h"
#include <algorithm>
#include <cstdlib>

InventorySystem::InventorySystem(Blockchain* bc) {
    inventoryFile = "inventory.json";
    demandFile = "demand.json";
    blockchain = bc;
    allowedLocations = { "KualaLumpur", "Johor", "Penang" };
    distanceFromKLIA = { { "KualaLumpur", 50 }, { "Johor", 320 }, { "Penang", 370 } };
    fixedInventory = { "Nvidia5070", "AMDRX7900", "Inteli9-14900K", "Ryzen9-7950X", "Z690", "Z790", "120mmFan", "140mmFan", "FanCooler", "WaterCooler" };
    loadData();
    initInventory();
}

void InventorySystem::initInventory() {
    for (auto& item : fixedInventory)
        if (inventory.find(item) == inventory.end())
            inventory[item] = (rand() % 30) + 20;
    saveData();
}

void InventorySystem::viewInventory() {
    cout << "\n--- Inventory ---\n";
    for (auto& it : inventory) cout << "Item: " << it.first << " | Quantity: " << it.second << endl;
}

void InventorySystem::viewDemand() {
    cout << "\n--- Demand ---\n";
    for (auto& loc : demand) {
        cout << loc.first << ":\n";
        for (auto& item : loc.second)
            cout << "  " << item.first << " -> " << item.second << endl;
    }
}

void InventorySystem::saveData() {
    json invJson, demJson;
    for (auto& it : inventory) invJson[it.first] = it.second;
    for (auto& loc : demand)
        for (auto& item : loc.second) demJson[loc.first][item.first] = item.second;
    ofstream(inventoryFile) << invJson.dump(4);
    ofstream(demandFile) << demJson.dump(4);
}

void InventorySystem::loadData() {
    ifstream invFile(inventoryFile), demFile(demandFile);
    json invJson, demJson;
    if (invFile) invFile >> invJson;
    if (demFile) demFile >> demJson;
    for (auto& [item, qty] : invJson.items()) inventory[item] = qty;
    for (auto& [loc, items] : demJson.items())
        for (auto& [item, qty] : items.items())
            demand[loc][item] = qty;
}

vector<pair<string, int>> InventorySystem::getSortedLocationsByDistance() {
    vector<pair<string, int>> sorted(distanceFromKLIA.begin(), distanceFromKLIA.end());
    sort(sorted.begin(), sorted.end(), [](auto& a, auto& b) { return a.second < b.second; });
    return sorted;
}

void InventorySystem::generateRandomDemands() {
    int randVal = rand() % 100;
    int locationIndex = (randVal < 60) ? 0 : (randVal < 85) ? 1 : 2;
    string randomItem = fixedInventory[rand() % fixedInventory.size()];
    int randomDemand = (rand() % 10) + 1;
    string location = allowedLocations[locationIndex];
    demand[location][randomItem] += randomDemand;
    blockchain->addBlock("Demand: " + to_string(randomDemand) + " units of " + randomItem + " at " + location, "Demand Generation");
    saveData();
}

void InventorySystem::allocateStockGreedy() {
    auto sortedLoc = getSortedLocationsByDistance();
    for (auto& item : fixedInventory) {
        int totalStock = inventory[item];
        if (totalStock == 0) continue;
        for (auto& loc : sortedLoc) {
            string location = loc.first;
            int locDemand = demand[location][item];
            if (locDemand == 0) continue;
            int allocateAmount = min(locDemand, totalStock);
            if (allocateAmount > 0) {
                demand[location][item] -= allocateAmount;
                totalStock -= allocateAmount;
                blockchain->addBlock("Allocated " + to_string(allocateAmount) + " of " + item + " to " + location, "Distribution");
                cout << "Allocated " << allocateAmount << " units of " << item << " to " << location << endl;
            }
            if (totalStock == 0) break;
        }
        inventory[item] = totalStock;
    }
    saveData();
}
