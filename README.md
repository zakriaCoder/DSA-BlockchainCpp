# C++ Blockchain & Transaction Simulator

A comprehensive C++ simulation of a blockchain ecosystem, demonstrating the lifecycle of a cryptocurrency transaction from wallet creation to final block confirmation. This project utilizes custom Data Structures (Linked Lists, Queues) and Object-Oriented Programming to simulate Mempools, Mining validation, and Ledger immutability.

## 🚀 Key Features

* **Wallet Management:** Secure login/registration system with simulated address generation.
* **Transaction Lifecycle:**
    * **Mempool:** Transactions enter a `TransactionQueue` (FIFO) simulating network congestion.
    * **Validation:** `Miner` nodes verify sender balances and recipient validity.
    * **Consensus:** Transactions are mined into blocks with simulated Proof-of-Work delays.
* **Blockchain Ledger:** A singly linked list of `Block` objects containing cryptographic hashes.
* **Interactive UI:** Professional CLI dashboard for real-time monitoring of balances and chain state.

## 🛠️ Tech Stack

* **Language:** C++ (Standard 11+)
* **Concepts:** OOP (Polymorphism, Encapsulation), Linked Lists, Circular Queues, Pointers.
* **Environment:** Console Application (Cross-platform).

## 📦 Installation & Usage

### Prerequisites
* A C++ Compiler (GCC, G++, or MSVC).

### Build Instructions

1.  **Clone the repository**
    ```bash
    git clone (https://github.com/zakriaCoder/DSA/edit/main/)
    ```

2.  **Compile**
    ```bash
    g++ *.cpp -o blockchain_sim
    ```

3.  **Run**
    * Windows: `blockchain_sim.exe`
    * Linux/Mac: `./blockchain_sim`

## 🖥️ Usage Guide

1.  **Start:** Run the application and select "Create New Wallet".
2.  ** transact:** Navigate to "Send Transaction", select a recipient, and choose a token (BTC, ETH, SOL).
3.  **Simulate:** Watch the terminal as your transaction moves from "Pending" -> "Miner Verification" -> "Confirmed".
4.  **Verify:** Select "View Blockchain Ledger" to see your transaction permanently recorded in a block.

---
*Developed by Muhammad Zakria*
