#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Transaction {
public:
    string sender;
    string receiver;
    string token;
    string network;
    double amount;
    double gasFee;
    string status;
    string txID;
    int blockNumber;

    Transaction();
    Transaction(string s, string r, string t, string n, double a, double g, string stat = "Pending", int block = -1);
    void display();
};

#endif