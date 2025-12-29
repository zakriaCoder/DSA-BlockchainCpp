#include "WalletManager.h"

// =========================================================
//  CONSTRUCTOR & DESTRUCTOR (LOGIC UNCHANGED)
// =========================================================

WalletManager::WalletManager() : miners{ Miner(1), Miner(2), Miner(3) } {
    transactionCount = 0;
    userWalletIndex = -1;
    dummyTransactionsAdded = false;

    wallets[0] = Wallet("Alice", 0.001, 0.01, 0.5, 15.0, 10.0);
    wallets[1] = Wallet("Bob", 0.0005, 0.008, 0.3, 12.0, 8.0);
    wallets[2] = Wallet("Charlie", 0.0008, 0.012, 0.4, 18.0, 12.0);
}

WalletManager::~WalletManager() {
    for (int i = 0; i < transactionCount; i++) {
        delete transactions[i];
    }
}

// =========================================================
//  USER MANAGEMENT (LOGIC UNCHANGED)
// =========================================================

void WalletManager::createUserWallet(string uname, string pwd) {
    wallets[3].createUserWallet(uname, pwd);
    userWalletIndex = 3;
}

bool WalletManager::loginUserWallet(string addr, string pwd) {
    if (userWalletIndex == -1) return false;
    return wallets[3].login(addr, pwd);
}

Wallet* WalletManager::getUserWallet() {
    if (userWalletIndex == -1) return nullptr;
    return &wallets[userWalletIndex];
}

Wallet* WalletManager::getRecipientWallet(int index) {
    if (index >= 0 && index < 3) {
        return &wallets[index];
    }
    return nullptr;
}

void WalletManager::addTransaction(Transaction* tx) {
    if (transactionCount < 50) {
        transactions[transactionCount] = tx;
        transactionCount++;
    }
}

// =========================================================
//  UI DISPLAY FUNCTIONS (IMPROVED)
// =========================================================

void WalletManager::showRecipientWallets() {
    cout << "\n";
    cout << "========================================================================" << endl;
    cout << "                           RECIPIENT DIRECTORY                          " << endl;
    cout << "========================================================================" << endl;
    cout << "  ID   NAME                ADDRESS                                      " << endl;
    cout << "------------------------------------------------------------------------" << endl;

    for (int i = 0; i < 3; i++) {
        // Manual formatting to avoid adding iomanip if not present, 
        // though standard C++ usually allows basic alignment.
        cout << "  [" << i + 1 << "]  " << wallets[i].getUsername();

        // Simple spacing logic for alignment
        string spaceGap = "                  "; // 18 spaces
        if (wallets[i].getUsername().length() < 18) {
            cout << spaceGap.substr(0, 18 - wallets[i].getUsername().length());
        }

        cout << wallets[i].getAddress() << endl;
    }
    cout << "========================================================================" << endl;
}

void WalletManager::showTransactionHistory() {
    cout << "\n";
    cout << "========================================================================" << endl;
    cout << "                      CONFIRMED TRANSACTION LOG                         " << endl;
    cout << "========================================================================" << endl;

    bool hasConfirmed = false;

    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i]->status == "Confirmed") {
            transactions[i]->display(); // Assumes Transaction::display has its own format
            hasConfirmed = true;
        }
    }

    if (!hasConfirmed) {
        cout << "  [!] No confirmed transaction records found in the ledger." << endl;
    }
    cout << "========================================================================" << endl;
}

void WalletManager::showBlockchain() {
    cout << "\n";
    cout << "========================================================================" << endl;
    cout << "                          BLOCKCHAIN LEDGER                             " << endl;
    cout << "========================================================================" << endl;
    blockchain.displayChain();
    cout << "========================================================================" << endl;
}

// =========================================================
//  MINING SIMULATION (VISUALLY ENHANCED)
// =========================================================

bool WalletManager::simulateMining(Transaction* tx, Wallet* sender) {
    cout << "\n";
    cout << "========================================================================" << endl;
    cout << "                       TRANSACTION PROCESSING NODE                      " << endl;
    cout << "========================================================================" << endl;

    cout << "  [1] SUBMISSION  : Transaction received by Mempool." << endl;

    queue.displayQueue();
    queue.processQueue();

    cout << "\n  [2] VALIDATION  : Requesting Validator Nodes...";
    cout << "\n------------------------------------------------------------------------" << endl;

    bool allValid = true;
    for (int i = 0; i < 3; i++) {
        // Indented output for validators
        if (!miners[i].voteOnTransaction(*tx, sender, wallets)) {
            allValid = false;
        }
    }
    cout << "------------------------------------------------------------------------" << endl;

    if (!allValid) {
        cout << "\n  [!] CRITICAL ERROR : Consensus failed. Transaction rejected." << endl;
        cout << "========================================================================" << endl;
        return false;
    }

    cout << "\n  [3] BROADCAST   : Propagating to Network Peers..." << endl;
    for (int i = 0; i < 3; i++) {
        // Assuming miner broadcast prints something, we let it print
        miners[i].broadcast("     >> Node acknowledged signal.");
    }

    cout << "\n  [4] MINING      : Solving Proof-of-Work Algorithm";
    queue.delayWithDots(2); // Retaining logic

    cout << "\n     [*] Hashing Block 1/3 ... [ OK ]" << endl;
    queue.delayWithDots(2);
    cout << "     [*] Linking Hash  2/3 ... [ OK ]" << endl;
    queue.delayWithDots(2);
    cout << "     [*] Finalizing    3/3 ... [ OK ]" << endl;
    queue.delayWithDots(1);

    cout << "\n  [5] COMPLETION  : Block successfully appended to chain." << endl;

    // Core Logic
    blockchain.addBlock(*tx);
    tx->status = "Confirmed";

    int tokenIndex = sender->getTokenIndex(tx->token);
    if (tokenIndex != -1) {
        double totalDeduct = tx->amount + tx->gasFee;
        sender->deductTokens(tokenIndex, totalDeduct);
        cout << "  [INFO] WALLET   : Balance Updated (-" << totalDeduct << " " << tx->token << ")" << endl;
    }

    addTransaction(tx);
    cout << "  [INFO] HISTORY  : Ledger updated." << endl;

    cout << "========================================================================" << endl;

    // Display the chain status nicely
    showBlockchain();

    return true;
}