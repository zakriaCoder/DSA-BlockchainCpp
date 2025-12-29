#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <iostream>
#include "Transaction.h"

using namespace std;

class Block {
public:
    int blockNumber;
    Transaction transaction;
    string prevHash;
    string currentHash;
    string timestamp;

    Block();
    Block(int num, Transaction tx, string prev = "");

    string calculateHash();
    void display();
};

#endif#pragma once
