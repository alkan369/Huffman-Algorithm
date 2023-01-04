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
    short workMode = -1;

    public:
    System() = default;

    void setMode(short mode);

    int getMode()const;

    std::string getEncodedMessage(const std::string& message);

    std::unordered_map<std::string, char> getKeyTable();

    std::string getDecodedMessage(const std::string& message, const std::unordered_map<std::string, char>& newKeyTable);
};