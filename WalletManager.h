#pragma once
#ifndef WALLETMANAGER_H
#define WALLETMANAGER_H

#include <iostream>
#include "Wallet.h"
#include "Transaction.h"
#include "TransactionQueue.h"
#include "Blockchain.h"
#include "Miner.h"

using namespace std;

class WalletManager {
private:
    Wallet wallets[4];
    int userWalletIndex;
    Transaction* transactions[50];
    int transactionCount;
    bool dummyTransactionsAdded;
    TransactionQueue queue;
    Blockchain blockchain;
    Miner miners[3];

public:
    WalletManager();
    ~WalletManager();

    void createUserWallet(string uname, string pwd);
    bool loginUserWallet(string addr, string pwd);
    Wallet* getUserWallet();
    void showRecipientWallets();
    Wallet* getRecipientWallet(int index);
    void addTransaction(Transaction* tx);
    void showTransactionHistory();
    bool simulateMining(Transaction* tx, Wallet* sender);
    void showBlockchain();
};

#endif