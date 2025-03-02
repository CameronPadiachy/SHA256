#include <iostream>
#include "SHA256.h"

using namespace std;

int main() {
    cout << "Please provide the string to be hashed: ";
    SHA256 hasher;
    string result = hasher.sha_hash();
    cout << "Final Hash: " << result << endl;
    return 0;
}