#pragma once
#include "Encoder.h"

class System{
    private:
    // bool isCompression;
    // HTree huffmanTree;
    // two classes ?? (Encode and Decode) ?
    Encoder encode;
    public:
    System() = default;

    std::string getEncodedMessage(const std::string& message){
        return encode.encodeMessage(message);
    }
};