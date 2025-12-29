#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <iostream>
#include "Block.h"
#include "Transaction.h"

using namespace std;

struct BlockNode {
    Block block;
    BlockNode* next;
    BlockNode(Block b) : block(b), next(nullptr) {}
};

class Blockchain {
private:
    BlockNode* head;
    BlockNode* tail;
    int blockCount;

public:
    Blockchain();
    void addBlock(Transaction tx);
    void displayChain();
    int getBlockCount();
};

#endif#pragma once
