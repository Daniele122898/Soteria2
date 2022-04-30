//
// Created by Daniele on 4/26/2022.
//

#ifndef SOTERIA_ENC_H
#define SOTERIA_ENC_H

void handleErrors();

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext);

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext);

void crand(unsigned char *buffer, int buffer_len);

unsigned int sha256(unsigned char *text, int text_len, unsigned char *hashed);
#endif //SOTERIA_ENC_H
