#include "../headers/main.h"

vector<User> generate_users(int count) {
    vector<User> users;                                     // Vector initialisation (with User struct)
    for (int i = 0; i < count; ++i) {                       // Loop for every user that is generated
        string name = "User" + to_string(i);                // Username
        string public_key = "public_key_" + to_string(i);   // Public key
        double balance = rand() % 10000;            // Generate balance
        users.push_back(User(name, public_key, balance));   // Generated users are pushed into vector
    }
    return users;                                           // Returning complete vector
}

vector<Transactions> generate_transactions(const vector<User> &users, int count) {
    vector<Transactions> transaction;                                                               // Vector initialisation (with Transactions struct)
    for (int i = 0; i < count; ++i) {                                                               // Loop for every transaction that is generated
        const User &sender = users[rand() % users.size()];                                          // Generate sender
        const User &receiver = users[rand() % users.size()];                                        // Generate receiver
        double amount = rand() % 100000;                                                            // Generate the transaction amount
        string transaction_id = to_string(i);                                                       // Transaction ID
        transaction.push_back(Transactions(transaction_id, sender.pKey, receiver.pKey, amount));    // Generated transactions are pushed into vector 
    }
    return transaction;                                                                             // Returning complete vector
}
