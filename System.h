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
    short workMode = -1; // default value for work mode
    bool workWithBits = false; // default value to work with bits

    void clearMessageAndTable(); // clears the current message and the current key table
    bool doesExist(const std::string& fileName); // check if a given file name exists
    void checkOpenInputFile(std::ifstream& file, const std::string& fileName); // check if given ifstream file is opened successfuly
    void checkOpenOutputFile(std::ofstream& file, const std::string& fileName); // check if given ofstream file is opened successfuly
    void readFile(std::ifstream& file); // reads the whole file of the given ifstream file (the file is opened successfuly)
    void readKeyTable(std::ifstream& file, std::string& data); // reads the key table from a given key table, with the help of additional string
    void writeToFileCompress(); // writing to file in compression mode(standard compression)
    void readFromFileCompress(); // reading from file in compression mode
    void writeToFileDecompress(); // writing to file in decompression mode(standard decompression)
    void readFromFileDecompress(); // reading from file in decompression mode
    void writeToBits(); // writing to file in compression mode(in bits mode)(used only in doctest)
    void readFromBits(); // reading from file in decompression mode(in bits mode)(used only in doctes)
    void printToScreen(); // priting the compressed(encoded) message to the screen(also in bits mode)

    void compress(); // starting the compression mode
    void decompress(); // starting the decompression mode
    void debug(); // staring the debug mode(prints the result to screen)

    public:
    System() = default;

    void setWorkWithBits(bool bitsMode); // setting if the program should work in bits mode
    bool getWorkWithBits()const; // getting if the program works in bits mode
    void setMode(short mode); // setting the workmode of the program(compression, decompression, debug)
    int getMode()const; // getting the current workmode
    void setInputFileName(const std::string& input); // setting the input file name
    const std::string& getInputFileName()const; // getting the input file name
    void setOutputFileName(const std::string& output); // setting the output file name
    const std::string& getOutputFileName()const; // getting the output file name

    void start(); // starting the program(throws exception if no work mode is set)
};