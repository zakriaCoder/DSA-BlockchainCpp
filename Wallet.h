#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Wallet {
private:
    string username;
    string password;
    string walletAddress;
    string seedPhrase;

    string tokenNames[5] = { "BTC", "ETH", "SOL", "SUI", "TON" };
    string tokenNetworks[5] = { "Bitcoin mainnet", "ERC-20", "SPL", "SUI mainnet", "Jettons" };
    double tokenAmounts[5] = { 0.00044, 0.0067, 0.18, 9.0, 4.43 };
    double tokenPrices[5];
    double basePrices[5] = { 90909.0, 2985.0, 83.0, 2.0, 1.58 };
    double gasFees[5];

    double getRandomChange();
    string generateAddress(string name);
    string generateSeedPhrase();
    void updatePrices();
    double calculateTotal();
    double calculatePercentageChange(double currentTotal);

public:
    Wallet();
    Wallet(string uname, double btc, double eth, double sol, double sui, double ton);

    void createUserWallet(string uname, string pwd);
    bool login(string addr, string pwd);
    bool recoverWithSeed(string inputSeed);
    void resetPassword(string newPwd);
    bool hasEnoughTokens(int tokenIndex, double amount);
    int getTokenIndex(string tokenName);
    double getGasFee(int tokenIndex);
    void deductTokens(int tokenIndex, double amount);
    void showDashboard();
    void showCreationDetails();

    string getAddress();
    string getUsername();
    string getTokenName(int index);
    string getTokenNetwork(int index);
    double getTokenAmount(int index);
    bool isEmpty();
};

#endif#pragma once
