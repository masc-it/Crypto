//
// Created by Mauro on 30/10/2019.
//

#ifndef CRYPTOTEST_CRYPTO_H
#define CRYPTOTEST_CRYPTO_H
#include <functional>
#include <cstring>
#include <taskflow.hpp>

class Crypto {

public:

    explicit Crypto(const char* key){

        this->key = key;
        key_length = strlen(key);

    };

    const char* get_key(){ return key;}
    size_t get_key_length() { return key_length; }

    static unsigned char crypt_v1b(unsigned char element, const char* key, size_t key_length);
    static unsigned char decrypt_v1b(unsigned char element, const char* key, size_t key_length);
private:

    const char* key = nullptr;
    size_t key_length = 0;


    static unsigned char circshift_left(unsigned char x, int n) {
        return (x << n) | (x >> (8 - n));
    }
    static unsigned char circshift_right(unsigned char x, int n) {
        return (x >> n) | (x << (8 - n));
    }

    static unsigned char reverse(unsigned char b) {
        return (b * 0x0202020202ULL & 0x010884422010ULL) % 1023;
    }



};


#endif //CRYPTOTEST_CRYPTO_H
