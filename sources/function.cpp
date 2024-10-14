#include "../headers/main.h"

string toHexString(const vector<uint8_t>& bytes) {
    stringstream ss;
    for (const auto& byte : bytes) {
        ss << hex << setw(2) << setfill('0') << (int)byte;
    }
    return ss.str();
}
// Patobulinta maišos funkcija su daugiau maišymo
vector<uint8_t> betterHash(const string& input) {
    // Fiksuotas išėjimo dydis - 256 bitai arba 32 baitai
    const size_t hashSize = 32;
    vector<uint8_t> hash(hashSize, 0xAA); // Inicializuojame su pradinėmis reikšmėmis
    
    // Pradinė vertė
    uint8_t salt = 0xAB;

    for (size_t i = 0; i < input.length(); ++i) {
        // Pirmiausia modifikuojame kiekvieną baitą
        for (size_t j = 0; j < hashSize; ++j) {
            // Naudojame XOR su simbolio verte, jo pozicija, salt ir baito pozicija
            hash[j] ^= (input[i] + salt + i * 31 + j * 17);
            // Pasukame baitus, kad įtakotume viso masyvo baitus
            hash[j] = ((hash[j] << 7) | (hash[j] >> 1)) ^ (salt * (i + 1));
        }
        salt = (salt * 33) + input[i]; // Modifikuojame salt, kad kiekvienas simbolis įtakotų tolimesnius ciklus
    }

    // Papildomas maišymas po pagrindinio ciklo
    for (size_t i = 0; i < hashSize; ++i) {
        hash[i] ^= (salt + i * 31);  // Dar daugiau chaoso
        hash[i] = ((hash[i] << 5) | (hash[i] >> 3)) ^ salt;
    }

    return hash;
}