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
string toHexString(const vector<uint8_t>& bytes);
vector<uint8_t> betterHash(const string& input);

struct Transactions{
int transactionID;
string sender;
string receiver;
double amount;
};

struct BlockHeader{
  string pHash;
  time_t timestamp;
  string mHash;
  int nonce;
  int dTarget;
  int version;
};

struct User{
string name;
int pKey;
double balance;
};

struct Block{
  BlockHeader header;
  vector <Transactions> transaction;
};

#endif