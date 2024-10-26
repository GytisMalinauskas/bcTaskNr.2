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

vector<uint8_t> betterHash(const string& input);
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
  int dTarget; //Difficiculty target
  
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
    std::vector<Block> chain;
    std::vector<Transactions> pending_transactions;

public:
    Blockchain() {
        // Add a genesis block
        BlockHeader genesis_header("0", 1, "0", 1);
        chain.push_back(Block(genesis_header, {}));
    }

    // Updated hash function
    std::string hash_function(const BlockHeader &header) {
        std::string input = header.pHash + 
                            std::to_string(header.timestamp) + 
                            std::to_string(header.version) + 
                            header.mHash + 
                            std::to_string(header.nonce) + 
                            std::to_string(header.dTarget);
                            
        // Use your betterHash function
        std::vector<uint8_t> hash_bytes = betterHash(input);
        
        // Convert the byte array to a hex string
        return toHexString(hash_bytes);
    }

    void add_block(Block new_block) {
        chain.push_back(new_block);
    }

    void add_transaction(const Transactions &tx) {
        pending_transactions.push_back(tx);
    }

    Block mine_block(int difficulty) {
        BlockHeader header = chain.back().header;
        header.dTarget = difficulty;

        // Calculate the Merkle root hash of the current pending transactions
        header.mHash = calculate_merkle_root(pending_transactions);

        // Mining process: adjust nonce until difficulty target is met
        while (hash_function(header).substr(0, difficulty) != std::string(difficulty, '0')) {
            header.nonce++;
        }

        // Create new block and add to blockchain
        Block new_block(header, pending_transactions);
        pending_transactions.clear();
        add_block(new_block);

        return new_block;
    }

    void display_block(const Block &block) const {
        std::cout << "Block Header: " << block.header.pHash << "\n";
        std::cout << "Timestamp: " << block.header.timestamp << "\n";
        std::cout << "Merkle Root: " << block.header.mHash << "\n";
        std::cout << "Difficulty: " << block.header.dTarget << "\n";
        std::cout << "Nonce: " << block.header.nonce << "\n";
        std::cout << "Transactions: \n";
        for (const auto &tx : block.transaction) {
            std::cout << "Transaction ID: " << tx.transactionID << "\n";
            std::cout << "Sender: " << tx.sender_pKey << " Receiver: " << tx.receiver_pKey << "\n";
            std::cout << "Amount: " << tx.amount << "\n";
        }
    }
};


#endif