#define DOCTEST_CONFIG_IMPLEMENT
#include <string>
#include <fstream>
#include "../doctest.h"
#include "../../System.h"
#include "../../System.cpp"
#include "../../Decoder.h"
#include "../../Encoder.h"
#include "../../Encoder.cpp"
#include "../../HTree.h"
#include "../../HTree.cpp"

TEST_CASE("EMPTY INPUTS"){

    System s;

    CHECK_THROWS(s.setInputFileName(""));
    CHECK_THROWS(s.setOutputFileName(""));

    CHECK_THROWS(s.start());
    CHECK(s.getMode() == -1);
    CHECK(!s.getWorkWithBits());
    
}

TEST_CASE("STANDARD COMPRESSION TEST"){
    
    System s;

    s.setInputFileName("test");
    s.setOutputFileName("test-result");

    CHECK(s.getInputFileName() == "test");
    CHECK(s.getOutputFileName() == "test-result");
    CHECK(s.getMode() == -1);

    CHECK(!s.getWorkWithBits());
    s.setMode(0);
    s.setWorkWithBits(0);
    CHECK(s.getMode() == 0);
    CHECK(!s.getWorkWithBits());
    
    CHECK_NOTHROW(s.start());
    CHECK(s.getMode() == -1);
    CHECK_THROWS(s.start());
    
}

TEST_CASE("COMPRESSION TO BITS TEST"){

    System s;

    s.setInputFileName("testbits");
    s.setOutputFileName("testbits-result");

    CHECK(s.getInputFileName() == "testbits");
    CHECK(s.getOutputFileName() == "testbits-result");
    CHECK(s.getMode() == -1);

    s.setMode(0);
    s.setWorkWithBits(1);
    CHECK(s.getMode() == 0);
    CHECK(s.getWorkWithBits());
    
    CHECK_NOTHROW(s.start());
    CHECK(s.getMode() == -1);
    CHECK_THROWS(s.start());

}

TEST_CASE("STANDARD DECOMPRESSION TEST"){

    System s;

    s.setInputFileName("test-result");
    s.setOutputFileName("test");

    s.setMode(1);
    CHECK(s.getMode() == 1);
    CHECK(!s.getWorkWithBits());
    CHECK_NOTHROW(s.start());
    std::ifstream file("test");
    char c;
    std::string decoded;
    while(file.get(c)){
        decoded.push_back(c);
    }
    file.close();
    CHECK(decoded == "ABRACADABRA");
    CHECK(s.getMode() == -1);
    CHECK_THROWS(s.start());

}

TEST_CASE("STANDARD DECOMPRESSION TEST MULTIPLE TIMES"){

    System s;

    s.setInputFileName("test-result");
    s.setOutputFileName("test");

    s.setMode(1);
    CHECK(s.getMode() == 1);
    CHECK(!s.getWorkWithBits());
    CHECK_NOTHROW(s.start());
    std::ifstream file("test");
    char c;
    std::string decoded;
    while(file.get(c)){
        decoded.push_back(c);
    }
    file.close();
    CHECK(decoded == "ABRACADABRA");
    CHECK(s.getMode() == -1);
    CHECK_THROWS(s.start());

    s.setMode(1);
    CHECK_NOTHROW(s.start());
    file = std::ifstream("test");
    decoded.clear();
    while(file.get(c)){
        decoded.push_back(c);
    }
    file.close();
    CHECK(decoded == "ABRACADABRA");
    CHECK(s.getMode() == -1);
    CHECK_THROWS(s.start());

    s.setMode(1);
    CHECK_NOTHROW(s.start());
    file = std::ifstream("test");
    decoded.clear();
    while(file.get(c)){
        decoded.push_back(c);
    }
    file.close();
    CHECK(decoded == "ABRACADABRA");
    CHECK(s.getMode() == -1);
    CHECK_THROWS(s.start());

}

TEST_CASE("BITS DECOMPRESSION TEST"){

    System s;

    s.setInputFileName("testbits-result");
    s.setOutputFileName("testbits");

    s.setMode(1);
    s.setWorkWithBits(1);
    CHECK(s.getMode() == 1);
    CHECK(s.getWorkWithBits());
    CHECK_NOTHROW(s.start());
    std::ifstream file("testbits");
    char c;
    std::string decoded;
    while(file.get(c)){
        decoded.push_back(c);
    }
    file.close();
    CHECK(decoded == "ABRACADABRA");
    CHECK(s.getMode() == -1);
    CHECK_THROWS(s.start());

}

TEST_CASE("TEST DEBUG"){

    System s;

    s.setMode(2);
    s.setInputFileName("test");
    CHECK_NOTHROW(s.start());
    CHECK(s.getMode() == -1);
    CHECK_THROWS(s.start());

}

TEST_CASE("TEST DEBUG MULTIPLE TIMES"){

    System s;
    
    CHECK(!s.getWorkWithBits());
    s.setMode(2);
    s.setInputFileName("test");
    CHECK_NOTHROW(s.start());
    CHECK(s.getMode() == -1);
    CHECK_THROWS(s.start());
    s.setMode(2);
    CHECK(!s.getWorkWithBits());
    CHECK(s.getMode() == 2);
    CHECK_NOTHROW(s.start());
    CHECK(s.getMode() == -1);
    s.setMode(2);
    CHECK(s.getMode() == 2);
    CHECK_NOTHROW(s.start());
    CHECK(s.getMode() == -1);
    CHECK(!s.getWorkWithBits());

}

int main(){

    doctest::Context().run();

    return 0;
}