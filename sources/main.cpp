#include "../headers/main.h"

int main() {
    cout<<endl;
    Blockchain blockchain;

    // Generate 1000 users
    vector<User> users = generate_users(1000);

    // Generate 10000 transactions
    vector<Transactions> transactions = generate_transactions(users, 10);
    
    blockchain.add_transaction(transactions[0]);
    // Add some transactions to the blockchain
    for (int i = 1; i <= 9; ++i) {
        // Mine a block
        blockchain.add_transaction(transactions[i]);
        blockchain.mine_block(3);
    }

    //Display all blockchain blocks
    blockchain.display_block();
    
    return 0;
}
