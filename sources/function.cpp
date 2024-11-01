#include "../headers/main.h"

string toHexString(const vector<uint8_t>& bytes) {
    stringstream ss;                                        //Initialize string stream 
    for (const auto& byte : bytes) {                        //Repeat for each vector "bytes" element
        ss << hex << setw(2) << setfill('0') << (int)byte;  //Hex for format, setfill('0') fills any space left, (int)byte for changing value type
    }
    return ss.str();                                        //Returns the whole string-hex
}

vector<uint8_t> Hash(const string& input) {
    const size_t hashSize = 32;                             // Fixed output size - 32 bytes or 256 bits
    vector<uint8_t> hash(hashSize, 0xAA);                   // Initialize hash with starting values, 0x is indicator of hex
    uint8_t salt = 0xAB;                                    // Initialize salt, for randomness and to ensure the hash value is not always the same 
    for (size_t i = 0; i < input.length(); ++i) {           // Repeat for every char of input
        for (size_t j = 0; j < hashSize; ++j) {             // Repeat for 'hashSize' times
            hash[j] ^= (input[i] + salt + i * 31 + j * 17); // ^ is XOR, which flips the bits for hash to be significally diff
            hash[j] = ((hash[j] << 7) | (hash[j] >> 1))     // << and >> shifts bits, | (Bitwise OR) combines the shifts
            ^ (salt * (i + 1));                             // XOR again for flipping and also more salt to ensure randomness
        }
        salt = (salt * 33) + input[i];                      // Salt modified to ensure more randomness
    }
    for (size_t i = 0; i < hashSize; ++i) {                 // Additional mixing
        hash[i] ^= (salt + i * 31);                         // XOR again for fliping, with different salt values
        hash[i] = ((hash[i] << 5) | (hash[i] >> 3)) ^ salt; // Shifting bits and adding XOR and salt
    }
    return hash;                                            // Returns complete hash
}

string calculate_merkle_root(const vector<Transactions>& transactions) {
    if (transactions.empty()) return ""; // Handle empty input

    vector<string> hashes;
    for (const auto& tx : transactions) {
        hashes.push_back(toHexString(Hash(tx.transactionID))); // Start with transaction IDs
    }

    while (hashes.size() > 1) {                                                 //
        vector<string> new_hashes;
        for (size_t i = 0; i < hashes.size(); i += 2) {
            // If there's an odd number of hashes, duplicate the last one
            string left = hashes[i];
            string right = (i + 1 < hashes.size()) ? hashes[i + 1] : hashes[i];
            
            new_hashes.push_back(toHexString(Hash(left + right))); // Concatenate and hash
        }
        hashes = new_hashes; // Move to the next level
    }
    return hashes.front(); // The last remaining hash is the Merkle root
}

bool transactionCheck(Transactions transaction, vector <User>& users){
    for(auto& user : users){
        if(transaction.sender_pKey==user.pKey){
            if (user.balance>=transaction.amount){
                user.balance-=transaction.amount;
                for(auto& user2 : users){
                    if(user2.pKey==transaction.receiver_pKey){
                        user2.balance+=transaction.amount;
                    }
                }
                cout << "[INFO] Transakcija priimta" << endl;
                return true;
            }
        }   
    }
    cout << "[INFO] Transakcija atmesta" << endl;
return false;
}
void checkBalance(const vector <User> &users){
    for(const auto& user : users)
    {
        cout << "User: " << user.pKey << " Balance: " << user.balance << endl;
    }
}
