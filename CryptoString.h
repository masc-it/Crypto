//
// Created by Mauro on 03/11/2019.
//

#ifndef CRYPTOTEST_CRYPTOSTRING_H
#define CRYPTOTEST_CRYPTOSTRING_H


#include <cstring>
#include "Crypto.h"
using namespace std;

class CryptoString : Crypto {

public:

    explicit CryptoString(const char *key) : Crypto(key) {};

    unsigned char* encrypt(const char* input);
    const char* decrypt();


private:

    size_t input_length = 0;
    unsigned char* input_encrypted = nullptr;
};


#endif //CRYPTOTEST_CRYPTOSTRING_H
