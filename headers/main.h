#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>
#include <vector>
using namespace std;

vector<uint8_t> Hash(const string& input);
string toHexString(const vector<uint8_t>& bytes);

struct Transactions{
string transactionID;
string sender_pKey; //Sender public key
string receiver_pKey; //Receiver public key
double amount;

//Constructor
Transactions(string id, string sender, string receiver, double amnt):
transactionID(id), sender_pKey(sender), receiver_pKey(receiver), amount(amnt){}
};

string calculate_merkle_root(const vector<Transactions>& transaction);

struct BlockHeader{
  string pHash; //Previous hash
  time_t timestamp;
  int version;
  string mHash; //Merkle root hash
  int nonce;
  int dTarget; //Difficulty target
  
  //Constructor
  BlockHeader(string previousHash, int v, string merkleHash, int difficultyTarget):
  pHash(previousHash), version(v), mHash(merkleHash), dTarget(difficultyTarget) 
  {
  timestamp= time(nullptr);
  nonce=0;
  }
};

struct User{
string name;
string pKey; //Public key
double balance;

//Constructor
User(string Username, string publicKey, double balanceAmount):
name(Username), pKey(publicKey), balance(balanceAmount){}
};

vector<User> generate_users(int count);
vector<Transactions> generate_transactions(const vector<User> &users, int count);

struct Block{
  BlockHeader header;
  vector <Transactions> transaction;

  //Constructor
  Block(BlockHeader head, vector<Transactions> pendingTransactions):
  header(head), transaction(pendingTransactions){}
};

class Blockchain {
private:
    vector<Block> chain;
    vector<Transactions> pending_transactions;

public:
    //Constructor
    Blockchain() {
        // Add a genesis block when constructing a blockchain
        BlockHeader genesis_header("0", 1, "0", 1); // Initialized genesis header
        chain.push_back(Block(genesis_header, {})); // Genesis header and empty transaction array is added
    }
    // Hashing Block Header
    string hash_function(const BlockHeader &header) {
        string input =  header.pHash + 
                        to_string(header.timestamp) + 
                        to_string(header.version) + 
                        header.mHash + 
                        to_string(header.nonce) + 
                        to_string(header.dTarget);  // Input is concatenated
        vector<uint8_t> hash_bytes = Hash(input);   // Using my hash for input 
        return toHexString(hash_bytes);             // Convert the byte array to a hex string
    }

    // Add block function
    void add_block(Block new_block) {
        chain.push_back(new_block);
        cout<<"[INFO] Blokas pridėtas \n";
    }

    // Add transaction function
    void add_transaction(const Transactions &tx) {
        pending_transactions.push_back(tx);
        cout<<"[INFO] Transakcija pridėta \n";
    }

    // Block mining function
    Block mine_block(int difficulty) {
        BlockHeader header = chain.back().header;   // Initialized header which is the back of the chain
        header.dTarget = difficulty;                // Difficulty target is set

        // Calculate the Merkle root hash of the current pending transactions
        header.mHash = calculate_merkle_root(pending_transactions);

        // Set the version
        header.version = chain.back().header.version + 1;

        // Set timestamp 
        header.timestamp = time(nullptr);

        // Set the previous hash to the hash of the last block
        header.pHash = hash_function(chain.back().header);
        // Set the nonce to 0
        header.nonce = 0;
        // Mining process: adjust nonce until difficulty target is met
        // Proof-of-work
        // Loop is active until it finds a hash with O+difficulty zero's in the front
        while (hash_function(header).substr(0, difficulty) != string(difficulty, '0')) {    
            header.nonce++; // By changing nonce we change the hash function 
        }

        // Create new block and add to blockchain
        Block new_block(header, pending_transactions);
        pending_transactions.clear();
        add_block(new_block);
        cout << "[INFO] Blokas sėkmingai iškastas" << endl;
        return new_block;
    }

    // Display block function
    void display_block() const {
        for(const auto& block : chain) {
        cout << "Previous hash: " << block.header.pHash << "\n";
        cout << "Version: " << block.header.version << "\n";
        cout << "Timestamp: " << block.header.timestamp << "\n";
        cout << "Merkle Root hash: " << block.header.mHash << "\n";
        cout << "Difficulty: " << block.header.dTarget << "\n";
        cout << "Nonce: " << block.header.nonce << "\n";
        if(block.transaction.size()!=0)
        cout << "Transactions: \n";
         for (const auto &tx : block.transaction) {
            cout << "Transaction ID: " << tx.transactionID << "\n";
            cout << "Sender: " << tx.sender_pKey << " Receiver: " << tx.receiver_pKey << "\n";
            cout << "Amount: " << tx.amount << "\n";
        }
        cout<<endl;
        }
    }
};


#endif