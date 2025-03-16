#include "blockchain.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void clearScreen() { system(CLEAR); }

Block::Block(int blockId, string prevHash, string blockInfo, string blockStage)
    : id(blockId), previousHash(prevHash), info(blockInfo), stage(blockStage), currentHash(""), timestamp("") {
}

string Blockchain::generateRandomHash() {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string randHash(12, ' ');
    for (auto& c : randHash) c = alphanum[rand() % (sizeof(alphanum) - 1)];
    return randHash;
}

string Blockchain::getTimestamp() {
    time_t rawtime;
    struct tm timeinfo;
    char buffer[20];
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);
    strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", &timeinfo);
    return string(buffer);
}

Blockchain::Blockchain() {
    loadBlockchain();
    if (chain.empty()) {
        Block genesis(0, "00000", "Genesis Block", "Initialization");
        genesis.currentHash = generateRandomHash();
        genesis.timestamp = getTimestamp();
        chain.push_back(genesis);
        saveBlockchain();
    }
}

void Blockchain::addBlock(string data, string stage) {
    Block newBlock(chain.size(), chain.back().currentHash, data, stage);
    newBlock.currentHash = generateRandomHash();
    newBlock.timestamp = getTimestamp();
    chain.push_back(newBlock);
    saveBlockchain();
}

void Blockchain::displayChain() {
    for (auto& b : chain) {
        cout << "\n--- Stage: " << b.stage << " ---\n";
        cout << "Block Number: " << b.id << "\nHash: " << b.currentHash << "\nPrev Hash: " << b.previousHash << "\nTime: " << b.timestamp << "\n" << b.info << "\n----------------------\n";
    }
}

void Blockchain::saveBlockchain() {
    json j;
    for (auto& b : chain) j.push_back({ {"id", b.id}, {"currentHash", b.currentHash}, {"previousHash", b.previousHash}, {"timestamp", b.timestamp}, {"info", b.info}, {"stage", b.stage} });
    ofstream("blockchain.json") << j.dump(4);
}

void Blockchain::loadBlockchain() {
    ifstream file("blockchain.json");
    if (!file) return;
    json j; file >> j;
    chain.clear();
    for (auto& b : j)
        chain.push_back(Block(b["id"], b["previousHash"], b["info"], b["stage"]));
}
