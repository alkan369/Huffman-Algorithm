#pragma once
#include <fstream>
#include <cassert>
#include <bitset>
#include "Encoder.h"
#include "Decoder.h"
#include "BitSetHelper.h"


class System{
    private:
    Encoder encode;
    Decoder decode;
    std::string inputFileName;
    std::string outputFileName;
    std::string message;
    std::unordered_map<std::string, char> keyTable;
    short workMode = -1;
    bool workWithBits = false;

    void clearMessageAndTable();
    bool doesExist(const std::string& fileName);
    void checkOpenInputFile(std::ifstream& file, const std::string& fileName);
    void checkOpenOutputFile(std::ofstream& file, const std::string& fileName);
    void readLine(std::ifstream& file);
    void readKeyTable(std::ifstream& file, std::string& data);
    void writeToFileCompress();
    void readFromFileCompress();
    void writeToFileDecompress();
    void readFromFileDecompress();
    void writeToBits();
    void readFromBits();
    void printToScreen();

    void compress();
    void decompress();
    void debug();

    public:
    System() = default;

    void setWorkWithBits(bool bitsMode);
    bool getWorkWithBits()const;
    void setMode(short mode);
    int getMode()const;
    void setInputFileName(const std::string& input);
    const std::string& getInputFileName()const;
    void setOutputFileName(const std::string& output);
    const std::string& getOutputFileName()const;

    void start();

    // for tests

    std::string getEncodedMessage(const std::string& message);

    std::unordered_map<std::string, char> getKeyTable();

    std::string getDecodedMessage(const std::string& message, const std::unordered_map<std::string, char>& newKeyTable);
};