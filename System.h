#pragma once
#include "Encoder.h"
#include "Decoder.h"

class System{
    private:
    // bool isCompression;
    // HTree huffmanTree;
    // two classes ?? (Encode and Decode) ?
    Encoder encode;
    Decoder decode;
    //int iscompression
    public:
    System() = default;

    std::string getEncodedMessage(const std::string& message){
        return encode.encodeMessage(message);
    }

    std::unordered_map<std::string, char> getKeyTable(){
        return encode.getKeyTable();
    }

    std::string getDecodedMessage(const std::string& message, const std::unordered_map<std::string, char>& newKeyTable){
        decode.setKeyTable(newKeyTable);
        return decode.decodeMessage(message);
    }
};