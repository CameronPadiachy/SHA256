#ifndef SHA256_H
#define SHA256_h
#include <string>
#include <bitset>
#include <vector>
using namespace std;

class SHA256{
    public:
    SHA256();

    string sha_hash();
    
    private:
    void initialize();
    vector<bitset<8>> padding(string input);
    uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
    uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);
    uint32_t BigSigma_0(uint32_t x);
    uint32_t BigSigma_1(uint32_t x);
    uint32_t sigma_0(uint32_t x);
    uint32_t sigma_1(uint32_t x);
    uint32_t H[8];
    uint32_t a, b, c, d, e, f, g, h;

};




#endif 
