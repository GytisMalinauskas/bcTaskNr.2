#include "../headers/main.h"

int main() {
    cout << endl;
    Blockchain blockchain;
    int userCount, transactionCount, blockCount, transactionCount2, transactionSum=0, difficulty, maxNonce;
    bool transactionStop=false;
    // Inputs for generating
    cout << "[INPUT] Įveskite vartotojų skaičių: ";
    cin >> userCount;
    cout << "[INPUT] Įveskite transakcijų skaičių: ";
    cin >> transactionCount;
    cout << "[INPUT] Įveskite blokų, kuriuos kasime, skaičių: ";
    cin >> blockCount;
    cout << "[INPUT] Įveskite sudėtingumą: ";
    cin >> difficulty;
    cout << "[INPUT] Įveskite makslimalų nonce skaičių: ";
    cin >> maxNonce;

    int tr = transactionCount;

    // Generate users
    vector<User> users = generate_users(userCount);
    //checkBalance(users);
    // Generate transactions
    vector<Transactions> transactions = generate_transactions(users, transactionCount);

    for (int i = 0; i < blockCount; i++) {
        if(transactionStop==false){
        cout << endl << "[INFO] Jūs kasate " << i+1 << "-ąjį bloką" << endl;
        cout << "[INPUT] Įveskite transakcijų, kurios įeis į šį bloką, skaičių: ";
        cin >> transactionCount2;
        transactionSum+=transactionCount2;
        if (transactionSum < transactionCount){
            for (int j = tr - 1; j > tr-transactionCount2; --j) {
                // Add transactions
                bool checkHash = transactionHashValueCheck(transactions[j]);
                if(checkHash == true){
                    bool check = transactionCheck(transactions[j],users);
                    if(check == true){
                        blockchain.add_transaction(transactions[j]); 
                    } 
                }  
            }
            tr -= transactionCount2;
        }
        if(transactionSum >= transactionCount){
            cout << "[WARNING] pasiektas transakcijų limitas" << endl;
            transactionCount2+=(transactionCount-transactionSum);
            for (int j = tr - 1; j > tr-transactionCount2; --j) {
                // Add transactions
                bool checkHash = transactionHashValueCheck(transactions[j]);
                if(checkHash == true){
                    bool check = transactionCheck(transactions[j],users);
                    if(check == true){
                        blockchain.add_transaction(transactions[j]); 
                    } 
                }  
            }
            transactionStop=true;
        }
        }
        blockchain.mine_block(difficulty, maxNonce);
    }        
    //Display all blockchain blocks
    cout << endl;
    blockchain.display_block();
    //checkBalance(users);

    return 0;
}
