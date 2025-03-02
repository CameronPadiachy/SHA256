#ifndef SHA256_H
#define SHA256_h
#include <string>
#include <bitset>
#include <vector>
using namespace std;

class SHA256{
    public:
    SHA256();
    friend bitset<32> operator+(const bitset<32>& lhs, const bitset<32>& rhs);
    string sha_hash();
    
    private:
    void initialize();
    bitset<32>* message_schedule(vector<bitset<8>>, size_t index);
    vector<bitset<8>> padding(string input);
    uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
    uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);
    uint32_t BigSigma_0(uint32_t x);
    uint32_t BigSigma_1(uint32_t x);
    template <typename T> T sigma_0(T x);
    template <typename T> T sigma_1(T x);
    template <typename T> T S(T x, int y);
    template <typename T> T R(T x, int y);
    uint32_t H[8];
    uint32_t W[64];
    uint32_t a, b, c, d, e, f, g, h;
    uint32_t K[64];
};




#endif 
