//
// Created by Mauro on 30/10/2019.
//

#include <cstring>
#include "Crypto.h"

unsigned char Crypto::crypt_v1b(unsigned char element, const char *key, size_t key_length) {

    element = circshift_left(element, 3);
    for (int k = 0; k < key_length; k++) {

        element ^= key[k];
    }

    element = circshift_left(element, 2);
    element = reverse(element);
    return element;
}

unsigned char Crypto::decrypt_v1b(unsigned char element, const char* key, size_t key_length){

    element = reverse(element);
    element = circshift_right(element, 2);
    for (int k = 0; k < key_length; k++){

        element ^= key[k];

    }
    element = circshift_right(element, 3);
    return element;
}
