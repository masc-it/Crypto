//
// Created by Mauro on 03/11/2019.
//

#ifndef CRYPTOTEST_CRYPTOFILE_H
#define CRYPTOTEST_CRYPTOFILE_H
#define WIN32_LEAN_AND_MEAN

#include "Crypto.h"

#include <fstream>
#include <Windows.h>

class CryptoFile : Crypto {
private:
    void applyBuffer8Thread(unsigned char* buffer, size_t &size, std::function<unsigned char(unsigned char buff, const char *key, size_t key_length)> crypt);

public:
    explicit CryptoFile(const char *key) : Crypto(key) {};

    void encrypt(char* in, char* out);
    void decrypt(char* in, char* out);

    void encrypt2(char* in, char* out);
};


#endif //CRYPTOTEST_CRYPTOFILE_H
