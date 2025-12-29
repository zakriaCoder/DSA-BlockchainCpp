#include "Blockchain.h"

Blockchain::Blockchain() {
    head = nullptr;
    tail = nullptr;
    blockCount = 0;
}

void Blockchain::addBlock(Transaction tx) {
    blockCount++;
    string prevHash = (tail == nullptr) ? "Genesis" : tail->block.currentHash;
    Block newBlock(blockCount, tx, prevHash);

    BlockNode* newNode = new BlockNode(newBlock);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    tx.blockNumber = blockCount;
    tx.status = "Confirmed";
}

void Blockchain::displayChain() {
    cout << "\n";
    cout << "==========================================================" << endl;
    cout << "                OFFICIAL BLOCKCHAIN LEDGER                " << endl;
    cout << "==========================================================" << endl;
    cout << "  [NOTE] Simulation Mode: Simplified Consensus" << endl;
    cout << "----------------------------------------------------------" << endl;

    if (head == nullptr) {
        cout << "  [STATUS] Ledger is empty. No blocks mined yet." << endl;
        cout << "==========================================================" << endl;
        return;
    }

    BlockNode* current = head;
    while (current != nullptr) {
        // Visual link between blocks
        if (current != head) {
            cout << "                          |  |" << endl;
            cout << "                          \\  /" << endl;
            cout << "                           \\/" << endl;
        }

        current->block.display();
        current = current->next;
    }

    cout << "==========================================================" << endl;
    cout << "  Total Chain Height: " << blockCount << endl;
    cout << "==========================================================" << endl;
}

int Blockchain::getBlockCount() {
    return blockCount;
}