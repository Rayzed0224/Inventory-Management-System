#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <list>
#include <map>
#include <limits>
#include "nlohmann/json.hpp" // ADD THIS for JSON

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
using json = nlohmann::json;

struct Block {
    int id;
    string currentHash;
    string previousHash;
    string timestamp;
    string info;
    string stage;
    Block(int blockId, string prevHash, string blockInfo, string blockStage);
};

class Blockchain {
public:
    vector<Block> chain;
    Blockchain();
    void addBlock(string data, string stage);
    void displayChain();
    void saveBlockchain();
    void loadBlockchain();
    string generateRandomHash();
    string getTimestamp();
};

void clearScreen();

#endif
