#include <iostream> 
#include "SHA256.h"
#include <bitset>
#include <bit>
#include <vector>
#include <cmath>

using namespace std;

SHA256::SHA256(){
    initialize();
}

bitset<32> operator+(const bitset<32>& lhs, const bitset<32>& rhs) {
    unsigned long result = (lhs.to_ulong() + rhs.to_ulong()) % (1UL << 32);
    return bitset<32>(result);
}

void SHA256::initialize(){
    // initial hash value for algorithm
    H[0] = 0x6a09e667;
    H[1] = 0xbb67ae85;
    H[2] = 0x3c6ef372;
    H[3] = 0xa54ff53a;
    H[4] = 0x510e527f;
    H[5] = 0x9b05688c;
    H[6] = 0x1f83d9ab;
    H[7] = 0x5be0cd19;

    uint32_t Stds[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    for (int i=0; i<64; i++){
        K[i] = Stds[i];
    }
};

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
    return (x & y) ^ (~x & z);
}

uint32_t SHA256::Maj(uint32_t x, uint32_t y, uint32_t z){
    return (x & y) ^ (x & z) ^ (y & z);
}

template <typename T> T SHA256::S(T x, int y){
    return (x>>y)|(x<<(32-y));
}

template <typename T> T SHA256::R(T x, int y){
    return (x>>y);
}

uint32_t SHA256::BigSigma_0(uint32_t x){
    return ( S<uint32_t>(x,2) ^ S<uint32_t>(x, 13) ^ S<uint32_t>(x, 22));
}

uint32_t SHA256::BigSigma_1(uint32_t x){
    return (S<uint32_t>(x,6) ^ S<uint32_t>(x, 11) ^ S<uint32_t>(x, 25));
}

template <typename T> T SHA256::sigma_0(T x){
    return (S<T>(x,7) ^ S<T>(x, 18) ^ R<T>(x, 3));
}

template <typename T> T SHA256::sigma_1(T x){
    return (S<T>(x,17) ^ S<T>(x, 19) ^ R<T>(x, 10));
}

bitset<32>* SHA256::message_schedule(vector<bitset<8>> padded_in, size_t index){
    bitset<32>* w_p = new bitset<32>[64];
    for (int i=0; i<64; i++){
        bitset<32> temp(padded_in[index + i].to_ulong());
        w_p[i / 4] |= (temp << (24 - (8 * (i % 4))));
    }
    for (int j=16; j<=63; j++){
        w_p[j] = sigma_1(w_p[j-2]) + w_p[j-7] + sigma_0(w_p[j-15]) + w_p[j-16];
    }
    return w_p;
}

string SHA256:: sha_hash(){
    string input;
    cin >> input;
    vector<bitset<8>> word = padding(input);
    int word_size = word.size()*8;
    for (int i=0; i<=word_size/512; i++){ //parsing paddedmessage into 512 bit blocks
        a = H[0];
        b = H[1];
        c = H[2];
        d = H[3];
        e = H[4];
        f = H[5];
        g = H[6];
        h = H[7];

        uint32_t T1, T2;
        bitset<32>* W = message_schedule(word, i*512);
        for (int j = 0; j<=63; j++){
            T1 = h + BigSigma_1(e) + Ch(e,f,g) + K[j] + (W[j].to_ulong());
            T2 = BigSigma_0(a) + Maj(a,b,c);
            h = g;
            g = f;
            f = e;
            e = d+T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }
        H[0] = a + H[0];
        H[1] = b + H[1];
        H[2] = c + H[2];
        H[3] = d + H[3];
        H[4] = e + H[4];
        H[5] = f + H[5];
        H[6] = g + H[6];
        H[7] = h + H[7];
    }
    string s;
    for (auto i : H){
        cout<<i;
    }
    return "complete";
}