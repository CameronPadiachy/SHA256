# 🔐 SHA-256 Encoder in C++

This project is a custom implementation of the SHA-256 cryptographic hash function written in C++. It replicates the message preprocessing, padding, message schedule generation, and compression function logic as defined by the SHA-2 standard.

## ⚙️ Features

- Full SHA-256 encryption pipeline:
  - Input string conversion to binary
  - Message padding to 512-bit blocks
  - Message schedule expansion
  - Core SHA-256 compression and hash computation
- Produces a valid 64-character hexadecimal SHA-256 hash
- Built from scratch using only C++ standard libraries (no crypto libraries)
- Console-based interaction (input + output)
- Clear hex output of the padded message (for debugging)

## 🚧 In Progress

This is the core hashing engine only. A simple web server for hashing via HTTP requests is planned. Future updates will include:

- ✅ Backend API (Node.js/Express or C++ server)
- ✅ Web frontend (React or basic HTML)
- ✅ Docker deployment
- ✅ Hash benchmarking and Bitcoin mining demo

## 💻 How to Use
If you wish to test the current hasher, ensure you have a compatible C++ compiler installed. Then run the following comands in terminal.
```bash
g++ -std=c++17 testing.cpp -o sha256
./sha256
```
Follow the given prompts.



### 1. Clone the repo

```bash
git clone https://github.com/CameronPadiachy/sha256-encoder.git
cd sha256-encoder

