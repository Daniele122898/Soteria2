//
// Created by Daniele on 4/26/2022.
//

#include <cpr/cpr.h>
#include <util.h>

#include "push.h"
#include "Parser.h"

void Push(ArgParse::CmdContext context) {
    LOG("Ran push function");
    for (auto &op: context.options) {
        LOG("Option: {} with value {}", op->GetName(), op->GetValue());
    }
    LOG(" ---------------------------- ");


    // open file
    /* A 256 bit key */
    unsigned char key[32];
    std::string pw = "testpassword1231231";
    sha256(reinterpret_cast<unsigned char *>(pw.data()), static_cast<int>(pw.size()), key);
//    auto *key = (unsigned char *)"01234567890123456789012345678901";

    Parser p{"F:/Coding/Cpp/Soteria2/test/data/.soteria"};
    std::vector<std::tuple<std::vector<unsigned char>, int, std::filesystem::path>> encFiles;
    for (auto &path: p.GetPaths()) {
//        LOGR(path);

        Util::File file(path.string());

        /* A 128 bit IV */
        auto *iv = (unsigned char *) "0123456789012345";

        /*
     * Buffer for ciphertext. Ensure the buffer is long enough for the
     * ciphertext which may be longer than the plaintext, depending on the
     * algorithm and mode.
     */
//        unsigned char ciphertext[file.Size() + 129];
        std::vector<unsigned char> ciphertext(file.Size() + 129);
        /* Buffer for the decrypted text */
//    unsigned char decryptedtext[file.Size()+1];

//    int decryptedtext_len, ciphertext_len;
        int ciphertext_len;

        /* Encrypt the plaintext */
        ciphertext_len = encrypt(reinterpret_cast<unsigned char *>(file.Raw()), static_cast<int>(file.Size()), key, iv,
                                 ciphertext.data());

        encFiles.emplace_back(std::move(ciphertext), ciphertext_len, path);
    }




//    Util::File::Write("F:/Coding/Cpp/Soteria2/test/enc/test_enc.txt", Util::GenerateHexString(ciphertext, ciphertext_len));

    /* Decrypt the ciphertext */
//    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv,
//                                decryptedtext);

    /* Add a NULL terminator. We are expecting printable text */
//    decryptedtext[decryptedtext_len] = '\0';

//    cpr::Response r = cpr::Post(cpr::Url{"https://cc104162-46e0-48ca-bffd-5e396e75c4f3.mock.pstmn.io/push"},
//                                cpr::Multipart{{"secret", cpr::File{"F:/Coding/Cpp/Soteria2/test/dec/test_dec.txt"}}});

    cpr::Multipart mp{};
    for (auto&& [ciphertext, len, path] : encFiles) {
        mp.parts.emplace_back("files", cpr::Buffer{ciphertext.data(), ciphertext.data() + len, path.filename().string()});
    }

    cpr::Response r = cpr::Post(cpr::Url{"http://127.0.0.1:18080/push"}, mp);

    LOGR(r.text);

}

