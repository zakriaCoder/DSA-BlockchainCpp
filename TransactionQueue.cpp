#include "TransactionQueue.h"
#include <iostream> 
// Assuming iostream is available as per standard, no other libraries added.

using namespace std;

// =========================================================
//  CONSTRUCTOR & SETUP (LOGIC UNCHANGED)
// =========================================================

TransactionQueue::TransactionQueue() {
    front = 0;
    rear = -1;
    size = 0;
    initializeDummyTransactions();
}

void TransactionQueue::initializeDummyTransactions() {
    enqueue(new Transaction("addr_Alice_wallet", "addr_Bob_wallet", "BTC", "Bitcoin mainnet", 0.0001, 0.00001, "Pending"));
    enqueue(new Transaction("addr_Bob_wallet", "addr_Charlie_wallet", "ETH", "ERC-20", 0.5, 0.0001, "Pending"));
    enqueue(new Transaction("addr_Charlie_wallet", "addr_Alice_wallet", "SOL", "SPL", 10.0, 0.001, "Pending"));
}

// =========================================================
//  QUEUE OPERATIONS (LOGIC UNCHANGED)
// =========================================================

void TransactionQueue::enqueue(Transaction* tx) {
    if (size < 10) {
        rear = (rear + 1) % 10;
        queue[rear] = tx;
        size++;
    }
}

Transaction* TransactionQueue::dequeue() {
    if (size == 0) return nullptr;

    Transaction* tx = queue[front];
    front = (front + 1) % 10;
    size--;
    return tx;
}

bool TransactionQueue::isFull() {
    return size == 10;
}

bool TransactionQueue::isEmpty() {
    return size == 0;
}

int TransactionQueue::getSize() {
    return size;
}

// =========================================================
//  UI & DISPLAY FUNCTIONS (VISUALLY ENHANCED)
// =========================================================

void TransactionQueue::displayQueue() {
    cout << "\n";
    cout << "========================================================================" << endl;
    cout << "                       MEMPOOL (PENDING TRANSACTIONS)                   " << endl;
    cout << "========================================================================" << endl;
    cout << "  [NOTE] Simulation Logic: FIFO (First-In, First-Out)" << endl;
    cout << "------------------------------------------------------------------------" << endl;

    if (size == 0) {
        cout << "  [EMPTY] No pending transactions in the pool." << endl;
        cout << "========================================================================" << endl;
        return;
    }

    int index = front;
    for (int i = 0; i < size; i++) {
        cout << "  " << i + 1 << ". ";

        // Manual alignment for type
        if (i < 3) {
            cout << "[ SYSTEM ]  ";
        }
        else {
            cout << "[ USER   ]  ";
        }

        cout << queue[index]->sender << " -> " << queue[index]->receiver << endl;
        cout << "                 Value: " << queue[index]->amount << " " << queue[index]->token << endl;

        if (i < size - 1) {
            cout << "  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
        }

        index = (index + 1) % 10;
    }
    cout << "========================================================================" << endl;
}

void TransactionQueue::delayWithDots(int seconds) {
    for (int i = 0; i < seconds; i++) {
        cout << ".";
        for (int j = 0; j < 300000000; j++) {
            // Delay loop
        }
    }
}

void TransactionQueue::processQueue() {
    cout << "\n";
    cout << "========================================================================" << endl;
    cout << "                      NETWORK TRAFFIC CONTROLLER                        " << endl;
    cout << "========================================================================" << endl;
    cout << "  [INFO] Clearing preceding network congestion (3 Tx)..." << endl;
    cout << "------------------------------------------------------------------------" << endl;

    for (int i = 1; i <= 3; i++) {
        cout << "  [>>] Processing Block Data " << i << " ";
        delayWithDots(5);
        cout << " [ CONFIRMED ]" << endl;

        Transaction* dummy = dequeue();
        if (dummy) delete dummy;
    }

    cout << "------------------------------------------------------------------------" << endl;
    cout << "  [INFO] Network Clear. Now prioritizing USER transaction..." << endl;
    cout << "========================================================================" << endl;
}