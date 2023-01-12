#define DOCTEST_CONFIG_IMPLEMENT
#include <string>
#include "../doctest.h"
#include "../../Encoder.h"
#include "../../Encoder.cpp"
#include "../../Htree.h"
#include "../../Htree.cpp"


TEST_CASE("ENCODING EMPTY MESSAGE"){

    Encoder encode;
    std::unordered_map<std::string, char> emptyKeyTable;

    CHECK(encode.encodeMessage("") == "");
    CHECK(encode.getKeyTable() == emptyKeyTable);
    
}


TEST_CASE("Multiple times encoding"){

    Encoder encode;
    std::string messageToEncode = "ABRACADABRA123  \n  ABRACADABRA123";
    Encoder temp;
    std::string expected = temp.encodeMessage(messageToEncode);
    
    auto expectedKeyTable = temp.getKeyTable();
    auto size = encode.encodeMessage(messageToEncode).size();

    CHECK(encode.encodeMessage(messageToEncode) == expected);
    CHECK(size == expected.size());
    CHECK(encode.getKeyTable() == expectedKeyTable);

    size = encode.encodeMessage(messageToEncode).size();
    CHECK(encode.encodeMessage(messageToEncode) == expected);
    CHECK(encode.getKeyTable() == expectedKeyTable);
    CHECK(size == expected.size());

    messageToEncode = "ABRACADABRA";
    temp;
    expected = temp.encodeMessage(messageToEncode);
    
    expectedKeyTable = temp.getKeyTable();
    size = encode.encodeMessage(messageToEncode).size();

    CHECK(encode.encodeMessage(messageToEncode) == expected);
    CHECK(size == expected.size());
    CHECK(encode.getKeyTable() == expectedKeyTable);

    size = encode.encodeMessage(messageToEncode).size();
    CHECK(encode.encodeMessage(messageToEncode) == expected);
    CHECK(encode.getKeyTable() == expectedKeyTable);
    CHECK(size == expected.size());

}

TEST_CASE("ENCODING DIFFERENT THINGS"){

    Encoder encode1;
    std::string message = "ABRACADABRA";
    Encoder encode2;
    std::string expectedMessage = encode1.encodeMessage(message);
    std::unordered_map<std::string, char> expectedKeyTable = encode1.getKeyTable();

    CHECK(encode2.encodeMessage(message) == expectedMessage);
    CHECK(encode2.getKeyTable() == expectedKeyTable);

    message = "ABRACADABRA123 \n ABRACADABRA123";
    expectedMessage = encode1.encodeMessage(message);
    expectedKeyTable = encode1.getKeyTable();

    CHECK(encode2.encodeMessage(message) == expectedMessage);
    CHECK(encode2.getKeyTable() == expectedKeyTable);

    CHECK(encode2.encodeMessage("ABRACADABRA") != expectedMessage);
    CHECK(encode2.getKeyTable() != expectedKeyTable);

}


int main(){
    
    doctest::Context().run();

    return 0;
}