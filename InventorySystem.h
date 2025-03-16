#pragma once
#ifndef INVENTORYSYSTEM_H
#define INVENTORYSYSTEM_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "blockchain.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class InventorySystem {
private:
    map<string, int> inventory;
    map<string, map<string, int>> demand;
    map<string, int> distanceFromKLIA;
    vector<string> allowedLocations;
    vector<string> fixedInventory;
    string inventoryFile;
    string demandFile;
    Blockchain* blockchain;

    void saveData();
    void loadData();
    vector<pair<string, int>> getSortedLocationsByDistance();

public:
    InventorySystem(Blockchain* bc);
    void viewInventory();
    void viewDemand();
    void generateRandomDemands();
    void allocateStockGreedy();
    void initInventory();
};

#endif
