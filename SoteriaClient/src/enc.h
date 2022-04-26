//
// Created by Daniele on 4/26/2022.
//

#ifndef SOTERIA_ENC_H
#define SOTERIA_ENC_H

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

void handleErrors();
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext);
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext);

#endif //SOTERIA_ENC_H
