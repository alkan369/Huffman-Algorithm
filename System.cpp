#include "System.h"
#include <bitset>

void System::setMode(short mode){
    if(mode > 2 || mode < 0 /* mode < -1*/){
        throw std::invalid_argument("Invalid mode");
        // assert ??
    }
    workMode = mode;
}

int System::getMode()const{
    return workMode;
}

void System::setInputFileName(const std::string& input){
    if(input.empty()){
        throw std::invalid_argument("Input file name empty");
    }
    std::cout << "Input file set" << std::endl;
    inputFileName = input;
}

const std::string& System::getInputFileName() const{
    return inputFileName;
}

void System::setOutputFileName(const std::string& output){
    if(output.empty()){
        throw std::invalid_argument("Output file name empty");
    }
    std::cout << "Output file set" << std::endl;
    outputFileName = output;
}

bool System::doesExist(const std::string& fileName){
    std::ifstream file(fileName);
    bool exists = file.good();
    file.close();
    return exists;
}

void System::writeToFileCompress(){
    std::ofstream file(outputFileName);
    if(!file.is_open()){
        throw std::runtime_error("Output file not opened");
    }
    file << encode.encodeMessage(message);
    file.close();
    file = std::ofstream(outputFileName + "table");
    std::unordered_map<std::string, char> table = encode.getKeyTable();
    std::string tableToString = "";
    if(!file.is_open()){
        throw std::runtime_error("Output file for key table not opened");
    }
    for(std::pair<std::string, char> elem : table){
        tableToString.append(elem.first + " = ");
        tableToString.push_back(elem.second);
        tableToString.push_back('\n');
    }
    file << tableToString;
    file.close();
    message.clear();
}

void System::readFromFileCompress(){
    if(!doesExist(inputFileName)){
        std::cout << "------------" << std::endl;
        std::cout << "INPUT FILE NAME : " << inputFileName << std::endl;
        std::cout << "------------" << std::endl;
        throw std::invalid_argument("Input file does not exist");
    }
    std::ifstream file(inputFileName);
    if(!file.is_open()){
        throw std::runtime_error("Input file not opened");
    }
    char c;
    while(file.get(c)){
        message.push_back(c);
    }
}

void System::writeToFileDecompress(){
    std::ofstream file(outputFileName);
    if(!file.is_open()){
        throw std::runtime_error("Output file not opened");
    }
    decode.setKeyTable(keyTable);
    // std::cout << "KEY TABLE : " << std::endl;
    // for(auto elem : keyTable){
    //     std::cout << elem.first << " = " << elem.second << std::endl;
    // }
    // std::cout << std::endl;
    // std::cout << "INPUT MESSAGE : " << message << std::endl;
    // message = decode.decodeMessage(message);
    // std::cout << "DECODED MESSAGE : " << message << std::endl;
    file << decode.decodeMessage(message);
    file.close();
    message.clear();
}

void System::readFromFileDecompress(){
    if(!doesExist(inputFileName) || !doesExist(inputFileName + "table")){
        throw std::invalid_argument("Input file or table for input file does not exist");
    }
    std::ifstream file(inputFileName);
    if(!file.is_open()){
        std::runtime_error("Input file not opened");
    }
    char c;
    while(file.get(c)){
        message.push_back(c);
    }
    file = std::ifstream(inputFileName + "table");
    if(!file.is_open()){
        std::runtime_error("Table file for Input file not opened");
    }
    short spaceCnt = 0;
    std::string binary = "";
    char character;
    while(file.get(c)){
        if(c == ' '){
            ++spaceCnt;
            continue;
        }
        if(c == '\n'){
            spaceCnt = 0;
            keyTable[binary] = character;
            binary.clear();
            continue;
        }
        else if(spaceCnt == 0){
            binary.push_back(c);
        }
        else if(spaceCnt >= 2){
            character = c;
        }
    }
    file.close();
}

void System::compress(){
    readFromFileCompress();
    writeToFileCompress();
}

void System::decompress(){
    readFromFileDecompress();
    writeToFileDecompress();
}

void System::debug(){
    readFromFileCompress();
}

void System::start(){
    switch (workMode){
        case 0:
            compress();
            break;
        case 1:
            decompress();
            break;
        case 2:
            debug();
            break;
        default:
            throw std::invalid_argument("No mode has been set");
            break;
    }
    workMode = -1;
}


const std::string& System::getOutputFileName() const{
    return outputFileName;
}

std::string System::getEncodedMessage(const std::string& message){
    return encode.encodeMessage(message);
}

std::unordered_map<std::string, char> System::getKeyTable(){
    return encode.getKeyTable();
}

std::string System::getDecodedMessage(const std::string& message, const std::unordered_map<std::string, char>& newKeyTable){
    decode.setKeyTable(newKeyTable);
    return decode.decodeMessage(message);
}