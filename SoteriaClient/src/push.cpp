//
// Created by Daniele on 4/26/2022.
//

#include "push.h"

void Push(ArgParse::Context context) {
    std::cout << "Ran push function " << std::endl;
    for (auto& op: context.options) {
        std::cout << "Option: " << op->GetName() << " with value " << op->GetValue() << std::endl;
    }
    std::cout << " ---------------------------- " << std::endl;

    // open file
    std::ifstream file("F:/Coding/Cpp/Soteria2/test/secrets.txt", std::ios::binary|std::ios::ate);
    // figure out length of file
    std::ifstream::pos_type pos = file.tellg();
    if (pos == 0) {
        std::cout << "File has 0 length" << std::endl;
        return;
    }

    std::vector<char> result(pos);

    file.seekg(0, std::ios::beg);
    file.read(result.data(), pos);

    std::cout << "Contents of read in stuff\n";
    for (char c : result) {
        std::cout << c;
    }
    std::cout << "\n";
    /* A 256 bit key */
    auto *key = (unsigned char *)"01234567890123456789012345678901";

    /* A 128 bit IV */
    auto *iv = (unsigned char *)"0123456789012345";

    /*
     * Buffer for ciphertext. Ensure the buffer is long enough for the
     * ciphertext which may be longer than the plaintext, depending on the
     * algorithm and mode.
     */
    unsigned char ciphertext[pos*2];
    /* Buffer for the decrypted text */
    unsigned char decryptedtext[pos*2];

    int decryptedtext_len, ciphertext_len;

    /* Encrypt the plaintext */
    ciphertext_len = encrypt (reinterpret_cast<unsigned char*>(result.data()), static_cast<int>(result.size()), key, iv,
                              ciphertext);

    /* Do something useful with the ciphertext here */
    printf("Ciphertext is:\n");
    BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);

    /* Decrypt the ciphertext */
    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv,
                                decryptedtext);

    /* Add a NULL terminator. We are expecting printable text */
    decryptedtext[decryptedtext_len] = '\0';

    /* Show the decrypted text */
    printf("Decrypted text is:\n");
    printf("%s\n", decryptedtext);

}

