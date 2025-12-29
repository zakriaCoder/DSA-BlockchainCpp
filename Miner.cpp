#include "Miner.h"

Miner::Miner(int id) {
    minerID = id;
}

bool Miner::validateBalance(Wallet* sender, string tokenName, double amount, double gasFee) {
    int tokenIndex = sender->getTokenIndex(tokenName);
    if (tokenIndex == -1) {
        return false;
    }
    return sender->hasEnoughTokens(tokenIndex, amount + gasFee);
}

bool Miner::validateRecipient(string address, Wallet wallets[]) {
    for (int i = 0; i < 4; i++) {
        if (wallets[i].getAddress() == address) {
            return true;
        }
    }
    return false;
}

void Miner::broadcast(string message) {
    cout << "  [NODE-" << minerID << "] SIGNAL >> " << message << endl;
}

bool Miner::voteOnTransaction(Transaction tx, Wallet* sender, Wallet wallets[]) {
    cout << "  [VALIDATOR " << minerID << "] Verifying Transaction Integrity..." << endl;

    bool balanceOK = validateBalance(sender, tx.token, tx.amount, tx.gasFee);
    if (!balanceOK) {
        cout << "      [X] Balance Check   : FAILED (Insufficient " << tx.token << ")" << endl;
        return false;
    }
    cout << "      [+] Balance Check   : PASSED" << endl;

    bool recipientOK = validateRecipient(tx.receiver, wallets);
    if (!recipientOK) {
        cout << "      [X] Recipient Check : FAILED (Invalid Address)" << endl;
        return false;
    }
    cout << "      [+] Recipient Check : PASSED" << endl;

    return true;
}