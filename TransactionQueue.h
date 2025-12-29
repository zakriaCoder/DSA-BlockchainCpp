#pragma once
#ifndef TRANSACTIONQUEUE_H
#define TRANSACTIONQUEUE_H

#include <iostream>
#include "Transaction.h"

using namespace std;

class TransactionQueue {
private:
    Transaction* queue[10];
    int front, rear, size;

public:
    TransactionQueue();
    void initializeDummyTransactions();
    void enqueue(Transaction* tx);
    Transaction* dequeue();
    bool isFull();
    bool isEmpty();
    void displayQueue();
    int getSize();
    void delayWithDots(int seconds);
    void processQueue();
};

#endif