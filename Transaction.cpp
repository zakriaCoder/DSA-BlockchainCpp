#include "Transaction.h"

Transaction::Transaction() {
    sender = "";
    receiver = "";
    token = "";
    network = "";
    amount = 0.0;
    gasFee = 0.0;
    status = "Pending";
    txID = "";
    blockNumber = -1;
}

Transaction::Transaction(string s, string r, string t, string n, double a, double g, string stat, int block) {
    sender = s;
    receiver = r;
    token = t;
    network = n;
    amount = a;
    gasFee = g;
    status = stat;
    blockNumber = block;

    static int txCounter = 1000;
    txID = "TX" + to_string(txCounter++);
}

void Transaction::display() {
    cout << "\n";
    cout << "==========================================================" << endl;
    cout << "                   TRANSACTION RECEIPT                    " << endl;
    cout << "==========================================================" << endl;

    cout << "  Tx ID    : " << txID << endl;
    cout << "  Status   : " << status;
    if (status == "Confirmed") {
        cout << " (Block #" << blockNumber << ")";
    }
    cout << endl;

    cout << "----------------------------------------------------------" << endl;

    cout << "  Sender   : " << sender << endl;
    cout << "  Receiver : " << receiver << endl;

    cout << "----------------------------------------------------------" << endl;

    cout << "  Token    : " << token << endl;
    cout << "  Network  : " << network << endl;
    cout << "  Amount   : " << fixed << setprecision(6) << amount << " " << token << endl;
    cout << "  Gas Fee  : " << fixed << setprecision(6) << gasFee << " " << token << endl;

    cout << "==========================================================" << endl;
    cout << "\n";
}