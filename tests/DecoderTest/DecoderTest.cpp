#define DOCTEST_CONFIG_IMPLEMENT
#include <string>
#include "../doctest.h"
#include "../../Decoder.h"
#include "../../Encoder.h"
#include "../../Encoder.cpp"
#include "../../Htree.h"
#include "../../Htree.cpp"

TEST_CASE("EMPTY MESSAGE RESULT AND EMPTY KEY TABLE"){

    Decoder decode;

    CHECK(decode.decodeMessage("") == "");
    CHECK(decode.decodeMessage("ABCD") == "");
    CHECK(decode.decodeMessage("01011011") == "");

    std::unordered_map<std::string, char> emptyKeyTable;
    CHECK_THROWS(decode.setKeyTable(emptyKeyTable));
}

TEST_CASE("DECODER TEST"){

    Encoder encode;
    Decoder decode;
    std::string message = "ABRACADABRA";
    std::string encodedMessage = encode.encodeMessage(message);
    std::unordered_map<std::string, char> keyTable = encode.getKeyTable();
    std::cout << std::endl;
    decode.setKeyTable(keyTable);
    CHECK(decode.decodeMessage(encodedMessage) == message);

}

TEST_CASE("DECODER TEST MULTIPLE"){

    Encoder encode;
    Decoder decode;
    std::string message = "ABRACADABRA";
    std::string encodedMessage = encode.encodeMessage(message);
    std::unordered_map<std::string, char> keyTable = encode.getKeyTable();
    decode.setKeyTable(keyTable);
    CHECK(decode.decodeMessage(encodedMessage) == message);

    message = "ABRACADABRA123 \n ABRACADABRA123";
    encodedMessage = encode.encodeMessage(message);
    keyTable = encode.getKeyTable();
    decode.setKeyTable(keyTable);
    CHECK(decode.decodeMessage(encodedMessage) == message);

}

TEST_CASE("CUSTOM KEY TABLE AND MESSAGE"){
    
    Decoder decode;
    std::unordered_map<std::string, char> keyTable;
    keyTable["0"] = 'A';;
    keyTable["10"] = 'L';
    keyTable["110"] = 'K';
    keyTable["111"] = 'N';

    CHECK(decode.decodeMessage("ALKAN") == "");
    decode.setKeyTable(keyTable);
    CHECK(decode.decodeMessage("0101100111") == "ALKAN");

}

int main(){
    
    doctest::Context().run();

    return 0;
}