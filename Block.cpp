#include "Block.h"

Block::Block() {
    blockNumber = 0;
    transaction = Transaction();
    prevHash = "";
    currentHash = "";
    timestamp = "";
}

Block::Block(int num, Transaction tx, string prev) {
    blockNumber = num;
    transaction = tx;
    prevHash = prev;
    currentHash = calculateHash();
    // Logic unchanged
    timestamp = "2024-12-01 10:00:00";
}

string Block::calculateHash() {
    return "Block_" + to_string(blockNumber) + "_Hash";
}

void Block::display() {
    // Box visual style
    cout << " +--------------------------------------------------------+" << endl;
    cout << " | BLOCK #" << blockNumber << "                                            |" << endl;
    cout << " +--------------------------------------------------------+" << endl;

    cout << " | Current Hash : " << currentHash << endl;
    cout << " | Previous Hash: " << prevHash << endl;
    cout << " | Timestamp    : " << timestamp << endl;
    cout << " | Payload (Tx) : " << transaction.txID << endl;

    cout << " +--------------------------------------------------------+" << endl;
}