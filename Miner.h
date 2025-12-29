#ifndef MINER_H
#define MINER_H

#include <string>
#include <iostream>
#include "Wallet.h"
#include "Transaction.h"

using namespace std;

class Miner {
private:
    int minerID;

public:
    Miner(int id);
    bool validateBalance(Wallet* sender, string tokenName, double amount, double gasFee);
    bool validateRecipient(string address, Wallet wallets[]);
    void broadcast(string message);
    bool voteOnTransaction(Transaction tx, Wallet* sender, Wallet wallets[]);
};

#endif#pragma once
