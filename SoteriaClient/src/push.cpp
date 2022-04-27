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
    File file("F:/Coding/Cpp/Soteria2/test/data/secrets.txt");
    /* A 256 bit key */
    unsigned char key[32];
    std::string pw = "testpassword1231231";
    sha256(reinterpret_cast<unsigned char*>(pw.data()), static_cast<int>(pw.size()),key);
//    auto *key = (unsigned char *)"01234567890123456789012345678901";

    /* A 128 bit IV */
    auto *iv = (unsigned char *)"0123456789012345";

    /*
     * Buffer for ciphertext. Ensure the buffer is long enough for the
     * ciphertext which may be longer than the plaintext, depending on the
     * algorithm and mode.
     */
    unsigned char ciphertext[file.Size()+129];
    /* Buffer for the decrypted text */
    unsigned char decryptedtext[file.Size()+1];

    int decryptedtext_len, ciphertext_len;

    /* Encrypt the plaintext */
    ciphertext_len = encrypt (reinterpret_cast<unsigned char*>(file.Raw()), static_cast<int>(file.Size()), key, iv,
                              ciphertext);

    File::Write("F:/Coding/Cpp/Soteria2/test/enc/test_enc.txt", generateHexString(ciphertext, ciphertext_len));

    /* Decrypt the ciphertext */
    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv,
                                decryptedtext);

    /* Add a NULL terminator. We are expecting printable text */
    decryptedtext[decryptedtext_len] = '\0';

    std::cout << "Writing decrypted text to file\n";
    File::Write("F:/Coding/Cpp/Soteria2/test/dec/test_dec.txt", decryptedtext, decryptedtext_len);

}

