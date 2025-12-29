#include <iostream>
#include <string>
#include "WalletManager.h" // Make sure this file exists in your folder!

using namespace std;

int main() {
    WalletManager manager;
    int choice;
    string username, password, address, seedInput;
    char recoveryChoice;
    int loginAttempts = 0;

    // Using R"(...)" allows you to paste the ASCII art exactly as is
        // without needing to manually type \n or escape backslashes.
    cout << R"(
==============================================================================
   ____  _            _       _           _        __     __     _____ 
  |  _ \| |          | |     | |         (_)       \ \   / /    |___ / 
  | |_) | | ___   ___| | ____| |__   __ _ _ _ __    \ \_/ /_   __ |_ \ 
  |  _ <| |/ _ \ / __| |/ / __| '_ \ / _` | | '_ \    \   / \ \/ /  | |
  | |_) | | (_) | (__|   < (__| | | | (_| | | | | |    | |   >  <  _| |
  |____/|_|\___/ \___|_|\_\___|_| |_|\__,_|_|_| |_|    |_|  /_/\_\|___|

==============================================================================
    
           BLOCKCHAIN WALLET SIMULATOR  |  DSA LAB PROJECT
    
      [+] HASHING MODULE ............ READY
      [+] LINKED LIST ............... READY
      [+] MINING PROTOCOL ........... ACTIVE
    
==============================================================================

Press ENTER to start...
)";

    cin.get();





    while (true) {
        // START EXCEPTION HANDLING
        try {
            cout << "\n+-----------------------------------------------------------+\n";
            cout << "|                       MAIN MENU                           |\n";
            cout << "+-----------------------------------------------------------+\n";
            cout << "|  1. Create Wallet                                         |\n";
            cout << "|  2. Login to Wallet                                       |\n";
            cout << "|  3. Exit Application                                      |\n";
            cout << "+-----------------------------------------------------------+\n";
            cout << "Enter Choice: ";


            // Check if input is a valid number
            if (!(cin >> choice)) {
                throw string("Invalid input! Please enter a number (1-3).");
            }

            if (choice == 1) {
                cout << "\n=== CREATE WALLET ===" << endl;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                manager.createUserWallet(username, password);

                if (manager.getUserWallet() == nullptr) {
                    throw string("Wallet creation failed!");
                }
                manager.getUserWallet()->showCreationDetails();

            }
            else if (choice == 2) {
                if (manager.getUserWallet() == nullptr || manager.getUserWallet()->isEmpty()) {
                    throw string("No wallet found! Please create a wallet first.");
                }

                loginAttempts = 0;

                while (loginAttempts < 3) {
                    cout << "\n=== LOGIN ===" << endl;
                    cout << "Enter wallet address: ";
                    cin >> address;
                    cout << "Enter password: ";
                    cin >> password;

                    if (manager.loginUserWallet(address, password)) {
                        cout << "\n*** LOGIN SUCCESSFUL! ***" << endl;

                        int walletChoice;
                        do {
                            try { // INNER TRY BLOCK
                                manager.getUserWallet()->showDashboard();

                                cout << "\n+-----------------------------------------------------------+\n";
                                cout << "|                     WALLET DASHBOARD                      |\n";
                                cout << "+-----------------------------------------------------------+\n";
                                cout << "|  1. Refresh Dashboard                                     |\n";
                                cout << "|  2. Send Tokens                                           |\n";
                                cout << "|  3. Receive Tokens                                        |\n";
                                cout << "|  4. View Transaction History                              |\n";
                                cout << "|  5. View Blockchain Ledger                                |\n";
                                cout << "|  6. Logout                                                |\n";
                                cout << "+-----------------------------------------------------------+\n";
                                cout << "Enter Choice: ";


                                if (!(cin >> walletChoice)) {
                                    throw string("Invalid menu choice! Enter a number.");
                                }

                                switch (walletChoice) {
                                case 1:
                                    break;

                                case 2: {
                                    cout << "\n=== SEND TOKENS ===" << endl;
                                    cout << "Select Token:" << endl;
                                    for (int i = 0; i < 5; i++) {
                                        cout << i + 1 << ". " << manager.getUserWallet()->getTokenName(i)
                                            << " (" << manager.getUserWallet()->getTokenNetwork(i) << ")" << endl;
                                    }

                                    int tokenChoice;
                                    cout << "Choice (1-5): ";
                                    if (!(cin >> tokenChoice)) throw string("Invalid token choice.");

                                    if (tokenChoice < 1 || tokenChoice > 5) {
                                        cout << "\n*** Invalid token choice! ***\n" << endl;
                                        break;
                                    }

                                    tokenChoice--;

                                    string tokenName = manager.getUserWallet()->getTokenName(tokenChoice);
                                    string network = manager.getUserWallet()->getTokenNetwork(tokenChoice);
                                    double available = manager.getUserWallet()->getTokenAmount(tokenChoice);
                                    double gasFee = manager.getUserWallet()->getGasFee(tokenChoice);

                                    cout << "\n--- Token Details ---" << endl;
                                    cout << "Selected: " << tokenName << endl;
                                    cout << "Network: " << network << endl;
                                    cout << "Available: " << available << " " << tokenName << endl;
                                    cout << "Network Gas Fee: " << gasFee << " " << tokenName << endl;

                                    manager.showRecipientWallets();

                                    int recipientChoice;
                                    cout << "\nSelect recipient (1-3): ";
                                    if (!(cin >> recipientChoice)) throw string("Invalid recipient choice.");

                                    if (recipientChoice < 1 || recipientChoice > 3) {
                                        cout << "\n*** Invalid recipient choice! ***\n" << endl;
                                        break;
                                    }

                                    Wallet* recipient = manager.getRecipientWallet(recipientChoice - 1);
                                    if (!recipient) {
                                        throw string("Recipient wallet error.");
                                    }

                                    string recipientAddress = recipient->getAddress();
                                    string recipientName = recipient->getUsername();

                                    double amount;
                                    cout << "Amount to send: ";
                                    if (!(cin >> amount)) throw string("Invalid amount entered.");

                                    if (amount <= 0) {
                                        cout << "\n*** Amount must be positive! ***\n" << endl;
                                        break;
                                    }

                                    double totalNeeded = amount + gasFee;
                                    if (!manager.getUserWallet()->hasEnoughTokens(tokenChoice, totalNeeded)) {
                                        cout << "\n*** INSUFFICIENT BALANCE! ***" << endl;
                                        break;
                                    }

                                    cout << "\n+-----------------------------------------------------------+\n";
                                    cout << "|                  TRANSACTION PREVIEW                      |\n";
                                    cout << "+-----------------------------------------------------------+\n";
                                    cout << "To: " << recipientName << endl;
                                    cout << "Total Cost: " << totalNeeded << " " << tokenName << endl;

                                    char confirm;
                                    cout << "\nConfirm transaction? [Y/N]: ";
                                    cin >> confirm;

                                    if (confirm == 'Y' || confirm == 'y') {
                                        Transaction* newTx = new Transaction(
                                            manager.getUserWallet()->getAddress(),
                                            recipientAddress,
                                            tokenName,
                                            network,
                                            amount,
                                            gasFee,
                                            "Pending");

                                        bool success = manager.simulateMining(newTx, manager.getUserWallet());

                                        if (!success) {
                                            delete newTx;
                                        }
                                    }
                                    else {
                                        cout << "\n*** Transaction cancelled. ***\n" << endl;
                                    }
                                    break;
                                }

                                case 3:
                                    cout << "\n=== RECEIVE TOKENS ===" << endl;
                                    cout << "Address: " << manager.getUserWallet()->getAddress() << endl;
                                    break;

                                case 4:
                                    manager.showTransactionHistory();
                                    break;

                                case 5:
                                    manager.showBlockchain();
                                    break;

                                case 6:
                                    cout << "\n*** Logging out... ***\n" << endl;
                                    break;

                                default:
                                    cout << "\n*** Invalid choice! ***\n" << endl;
                                }
                            }
                            catch (const string& e) { // CHANGED TO CONST
                                cout << "\n*********************************" << endl;
                                cout << "ERROR: " << e << endl;
                                cout << "*********************************\n" << endl;
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }

                        } while (walletChoice != 6);
                        break;
                    }
                    else {
                        loginAttempts++;
                        cout << "\n*** LOGIN FAILED! (Attempt " << loginAttempts << "/3) ***" << endl;

                        if (loginAttempts >= 3) {
                            cout << "*** Max attempts reached! Use recovery. ***" << endl;
                        }
                        else {
                            cout << "Recover? (R/T): ";
                            cin >> recoveryChoice;
                            if (recoveryChoice == 'R' || recoveryChoice == 'r') {
                                cout << "Seed Phrase: ";
                                cin.ignore();
                                getline(cin, seedInput);
                                if (manager.getUserWallet()->recoverWithSeed(seedInput)) {
                                    cout << "Recovered! Set new password: ";
                                    cin >> password;
                                    manager.getUserWallet()->resetPassword(password);
                                    break;
                                }
                                else {
                                    cout << "Invalid Seed." << endl;
                                }
                            }
                        }
                    }
                }
            }
            else if (choice == 3) {
                cout << "Exiting..." << endl;
                break;
            }
            else {
                cout << "\n*** Invalid choice! Select 1-3. ***\n" << endl;
            }

        }
        catch (const string& msg) { // CHANGED TO CONST
            cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            cout << "EXCEPTION: " << msg << endl;
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    return 0;
}