#include "../headers/main.h"

int main() {
    Blockchain blockchain;

    // Generate 1000 users
    vector<User> users = generate_users(1000);

    // Generate 10000 transactions
    vector<Transactions> transactions = generate_transactions(users, 10000);

    // Add some transactions to the blockchain
    for (int i = 0; i < 100; ++i) {
        blockchain.add_transaction(transactions[i]);
    }

    // Mine a block
    Block new_block = blockchain.mine_block(3);

    // Display mined block
    blockchain.display_block(new_block);

    return 0;
}
