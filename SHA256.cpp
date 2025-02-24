#include <iostream> 
#include "SHA256.h"
#include <bitset>
#include <vector>
#include <cmath>

using namespace std;

SHA256::SHA256(){
    initialize();
}

void SHA256::initialize(){
    // initial hash value for algorithm
    H[0] = 0x6a09e667;
    H[0] = 0xbb67ae85;
    H[0] = 0x3c6ef372;
    H[0] = 0xa54ff53a;
    H[0] = 0x510e527f;
    H[0] = 0x9b05688c;
    H[0] = 0x1f83d9ab;
    H[0] = 0x5be0cd19;
}

vector<bitset<8>> SHA256::padding(string input){
    // string in bits
    vector<bitset<8>> word;
    for (char c: input){
        word.push_back(bitset<8>(c));
    }
    word.push_back(bitset<8> (0x80));
    // finding the no. of zeroes to add
    int total_bits = (word.size()) * 8;
    int padding_bits = (448 - total_bits % 512 + 512) % 512;
    int padding_bytes = padding_bits / 8;
    for (int i = 0; i < padding_bytes; i++) {
        word.push_back(bitset<8>(0x00));
    }
    uint64_t original_length = input.size()*8;
    for (int i = 7; i >= 0; i--) {
        word.push_back(bitset<8>((original_length >> (i * 8)) & 0xFF));
    }
    return word;
}

uint32_t SHA256:: Ch(uint32_t x, uint32_t y, uint32_t z){
    
}

string SHA256:: sha_hash(){
    string input;
    cin >> input;
    vector<bitset<8>> word = padding(input);
    int word_size = word.size()*8;
    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];
    for (int i=0; i<word_size; i++){
        
    }
}