//
// Created by Mauro on 03/11/2019.
//

#include "CryptoString.h"

unsigned char *CryptoString::encrypt(const char *input) {

    if ( input == nullptr) return nullptr;

    input_length = strlen(input);

    input_encrypted = new unsigned char[input_length];

    for ( size_t i = 0; i < input_length; i++){

        input_encrypted[i] = crypt_v1b(input[i], get_key(), get_key_length());

    }

    return input_encrypted;

}


const char *CryptoString::decrypt() {

    if ( input_encrypted == nullptr){
        return nullptr;
    }

    auto original = new char[input_length];

    for ( size_t i = 0; i < input_length; i++){
        original[i] = (char)decrypt_v1b(input_encrypted[i], get_key(), get_key_length());
    }

    delete [] input_encrypted ;
    input_length = 0;

    return original;

}