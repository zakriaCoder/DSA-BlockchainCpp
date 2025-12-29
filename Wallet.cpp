#include "Wallet.h"

// =========================================================
//  LOGIC FUNCTIONS (UNCHANGED)
// =========================================================

double Wallet::getRandomChange() {
    static int counter = 0;
    counter++;
    return ((counter * 13) % 2000 - 1000) / 10000.0;
}

string Wallet::generateAddress(string name) {
    string addr = "addr_";
    size_t nameLength = name.length();
    size_t maxChars = (nameLength < 5) ? nameLength : 5;
    for (size_t i = 0; i < maxChars; i++) {
        addr += name[i];
    }
    addr += "_wallet";
    return addr;
}

string Wallet::generateSeedPhrase() {
    string seed = "";
    string words[] = { "alpha", "beta", "gamma", "delta", "echo", "foxtrot", "golf", "hotel" };
    for (int i = 0; i < 8; i++) {
        seed += words[i];
        if (i < 7) seed += " ";
    }
    return seed;
}

void Wallet::updatePrices() {
    for (int i = 0; i < 5; i++) {
        double changePercent = getRandomChange();
        tokenPrices[i] = basePrices[i] * (1.0 + changePercent);
    }
}

double Wallet::calculateTotal() {
    double total = 0;
    for (int i = 0; i < 5; i++) {
        total += tokenAmounts[i] * tokenPrices[i];
    }
    return total;
}

double Wallet::calculatePercentageChange(double currentTotal) {
    return ((currentTotal - 100.0) / 100.0) * 100.0;
}

Wallet::Wallet() {
    username = "";
    password = "";
    walletAddress = "";
    seedPhrase = "";

    gasFees[0] = 0.00001;
    gasFees[1] = 0.0001;
    gasFees[2] = 0.001;
    gasFees[3] = 0.1;
    gasFees[4] = 0.05;

    for (int i = 0; i < 5; i++) {
        tokenPrices[i] = basePrices[i];
    }
}

Wallet::Wallet(string uname, double btc, double eth, double sol, double sui, double ton) {
    username = "default";
    walletAddress = generateAddress(uname);
    password = "default123";
    seedPhrase = generateSeedPhrase();

    tokenAmounts[0] = btc;
    tokenAmounts[1] = eth;
    tokenAmounts[2] = sol;
    tokenAmounts[3] = sui;
    tokenAmounts[4] = ton;

    gasFees[0] = 0.00001;
    gasFees[1] = 0.0001;
    gasFees[2] = 0.001;
    gasFees[3] = 0.1;
    gasFees[4] = 0.05;

    for (int i = 0; i < 5; i++) {
        tokenPrices[i] = basePrices[i];
    }
}

void Wallet::createUserWallet(string uname, string pwd) {
    username = uname;
    password = pwd;
    walletAddress = generateAddress(uname);
    seedPhrase = generateSeedPhrase();

    gasFees[0] = 0.00001;
    gasFees[1] = 0.0001;
    gasFees[2] = 0.001;
    gasFees[3] = 0.1;
    gasFees[4] = 0.05;

    for (int i = 0; i < 5; i++) {
        tokenPrices[i] = basePrices[i];
    }
}

bool Wallet::login(string addr, string pwd) {
    return (walletAddress == addr && password == pwd);
}

bool Wallet::recoverWithSeed(string inputSeed) {
    return (seedPhrase == inputSeed);
}

void Wallet::resetPassword(string newPwd) {
    password = newPwd;
}

bool Wallet::hasEnoughTokens(int tokenIndex, double amount) {
    if (tokenIndex < 0 || tokenIndex >= 5) return false;
    return tokenAmounts[tokenIndex] >= amount;
}

int Wallet::getTokenIndex(string tokenName) {
    for (int i = 0; i < 5; i++) {
        if (tokenNames[i] == tokenName) {
            return i;
        }
    }
    return -1;
}

double Wallet::getGasFee(int tokenIndex) {
    if (tokenIndex >= 0 && tokenIndex < 5) {
        return gasFees[tokenIndex];
    }
    return 0.0;
}

void Wallet::deductTokens(int tokenIndex, double amount) {
    if (tokenIndex >= 0 && tokenIndex < 5) {
        tokenAmounts[tokenIndex] -= amount;
    }
}

// =========================================================
//  IMPROVED UI FUNCTIONS
// =========================================================

void Wallet::showDashboard() {
    updatePrices();
    double total = calculateTotal();
    double percentChange = calculatePercentageChange(total);

    cout << "\n";
    cout << "==========================================================================" << endl;
    cout << "                             WALLET DASHBOARD                             " << endl;
    cout << "==========================================================================" << endl;

    // User Section
    cout << "  User    : " << left << setw(20) << username;
    cout << "  Status  : Connected" << endl;
    cout << "  Address : " << walletAddress << endl;
    cout << "--------------------------------------------------------------------------" << endl;

    // Balance Section
    cout << "  TOTAL ASSETS : $" << fixed << setprecision(2) << total;
    if (percentChange >= 0) {
        cout << "  (+" << setprecision(1) << percentChange << "% Increase)" << endl;
    }
    else {
        cout << "  (" << setprecision(1) << percentChange << "% Decrease)" << endl;
    }
    cout << "--------------------------------------------------------------------------" << endl;

    // Table Header
    cout << left << setw(8) << "  TOKEN"
        << right << setw(14) << "AMOUNT"
        << right << setw(16) << "PRICE ($)"
        << right << setw(14) << "24h %"
        << right << setw(18) << "VALUE ($)" << endl;

    cout << "  " << string(70, '-') << endl;

    // Table Rows
    for (int i = 0; i < 5; i++) {
        double value = tokenAmounts[i] * tokenPrices[i];
        double priceChange = ((tokenPrices[i] - basePrices[i]) / basePrices[i]) * 100.0;

        cout << left << "  " << setw(6) << tokenNames[i];

        if (tokenNames[i] == "BTC" || tokenNames[i] == "ETH") {
            cout << right << setw(14) << fixed << setprecision(5) << tokenAmounts[i];
        }
        else {
            cout << right << setw(14) << fixed << setprecision(2) << tokenAmounts[i];
        }

        cout << right << setw(16) << fixed << setprecision(2) << tokenPrices[i];

        cout << right << setw(13);
        if (priceChange >= 0) {
            cout << "+" << fixed << setprecision(1) << priceChange << "%";
        }
        else {
            cout << fixed << setprecision(1) << priceChange << "%";
        }

        cout << right << setw(18) << fixed << setprecision(2) << value << endl;
    }
    cout << "==========================================================================" << endl;
    cout << endl;
}

void Wallet::showCreationDetails() {
    cout << "\n";
    cout << "==========================================================================" << endl;
    cout << "                          NEW WALLET GENERATED                            " << endl;
    cout << "==========================================================================" << endl;
    cout << "  Username : " << username << endl;
    cout << "  Address  : " << walletAddress << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "                         !!! SECURITY ALERT !!!                           " << endl;
    cout << "  Save the Seed Phrase below. You will need it to recover this wallet." << endl;
    cout << "\n  >>  " << seedPhrase << "  <<\n" << endl;
    cout << "==========================================================================" << endl;
    cout << "\n";
}

string Wallet::getAddress() { return walletAddress; }
string Wallet::getUsername() { return username; }
string Wallet::getTokenName(int index) {
    if (index >= 0 && index < 5) return tokenNames[index];
    return "";
}
string Wallet::getTokenNetwork(int index) {
    if (index >= 0 && index < 5) return tokenNetworks[index];
    return "";
}
double Wallet::getTokenAmount(int index) {
    if (index >= 0 && index < 5) return tokenAmounts[index];
    return 0.0;
}
bool Wallet::isEmpty() {
    return username.empty();
}