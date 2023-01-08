#pragma once
#include <fstream>
#include <cassert>
#include "Encoder.h"
#include "Decoder.h"


class System{
    private:
    // bool isCompression;
    // HTree huffmanTree;
    // two classes ?? (Encode and Decode) ?
    Encoder encode;
    Decoder decode;
    std::string inputFileName;
    std::string outputFileName;
    std::string message;
    std::unordered_map<std::string, char> keyTable;
    short workMode = -1;

    // std::string message;

    public:
    System() = default;

    void setMode(short mode);
    int getMode()const;
    void setInputFileName(const std::string& input);
    const std::string& getInputFileName()const;
    void setOutputFileName(const std::string& output);
    const std::string& getOutputFileName()const;


    bool doesExist(const std::string& fileName);
    // read keyTable
    // exception methods
    void writeToFileCompress();
    void readFromFileCompress();
    void writeToFileDecompress();
    void readFromFileDecompress();
    void writeToBits();
    void readFromBits();

    void compress();
    void decompress();
    void debug();
    void start();


    std::string getEncodedMessage(const std::string& message);

    std::unordered_map<std::string, char> getKeyTable();

    std::string getDecodedMessage(const std::string& message, const std::unordered_map<std::string, char>& newKeyTable);
};