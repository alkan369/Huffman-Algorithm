#include "System.h"
#include <bitset>

void System::setMode(short mode){
    assert(mode >= 0 || mode <= 2);
    // if(mode > 2 || mode < 0 /* mode < -1*/){
    //     throw std::invalid_argument("Invalid mode");
    //     // assert ??
    // }
    workMode = mode;
}

int System::getMode()const{
    return workMode;
}

void System::setInputFileName(const std::string& input){
    if(input.empty()){
        std::cout << "Input file name empty" << std::endl;
        return;
    }
    std::cout << "Input file set" << std::endl;
    inputFileName = input;
}

const std::string& System::getInputFileName() const{
    return inputFileName;
}

void System::setOutputFileName(const std::string& output){
    if(output.empty()){
        std::cout << "Output file name empty" << std::endl;
        return;
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
    if(outputFileName.empty()){
        throw std::invalid_argument("Output txt file name empty");
    }
    std::ofstream file(outputFileName);
    if(!file.is_open()){
        throw std::runtime_error("Output txt file not opened");
    }
    // auto result = encode.encodeMessage(message);
    // file.write(result.c_str(), result.size());
    //assert(!message.empty())
    file << encode.encodeMessage(message);
    file.close();
    file = std::ofstream(outputFileName + "table.txt");
    keyTable = encode.getKeyTable();
    // std::string tableToString = "";
    message.clear();
    if(!file.is_open()){
        throw std::runtime_error("Output txt file for key table not opened");
    }
    for(std::pair<std::string, char> elem : keyTable){
        message.append(elem.first + " = " + elem.second + '\n');
        // tableToString.push_back(elem.second);
        // tableToString.push_back('\n');
    }
    file << message;
    file.close();
    message.clear();
    keyTable.clear();
}

void System::readFromFileCompress(){
    if(inputFileName.empty() || !doesExist(inputFileName)){
        throw std::invalid_argument("Input txt file name empty or does not exist");
    }
    std::ifstream file(inputFileName);
    if(!file.is_open()){
        throw std::runtime_error("Input txt file not opened");
    }
    char c;
    while(file.get(c)){
        message.push_back(c);
    }
    file.close();
    if(message.empty()){
        throw std::invalid_argument("Empty Input txt file");
    }
}

void System::writeToFileDecompress(){
    if(outputFileName.empty()){
        throw std::invalid_argument("Empty Output file name");
    }
    std::ofstream file(outputFileName);
    if(!file.is_open()){
        throw std::runtime_error("Output txt file not opened");
    }
    decode.setKeyTable(keyTable);
    file << decode.decodeMessage(message);
    file.close();
    message.clear();
    keyTable.clear();
}

void System::readFromFileDecompress(){
    if(inputFileName.empty() || !doesExist(inputFileName) || !doesExist(inputFileName + "table.txt")){
        throw std::invalid_argument("Empty name or Input txt file or table for input txt file does not exist");
    }
    std::ifstream file(inputFileName);
    if(!file.is_open()){
        throw std::runtime_error("Input file not opened");
    }
    char c;
    while(file.get(c)){
        message.push_back(c);
    }
    file.close();
    file = std::ifstream(inputFileName + "table.txt");
    if(!file.is_open()){
        std::runtime_error("Table txt file for Input file not opened");
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
    if(message.empty() || keyTable.empty()){
        throw std::invalid_argument("Empty Input txt file or Empty key table txt file");
    }
}

void System::writeToBits(){
    if(outputFileName.empty()){
        throw std::invalid_argument("Empty Output txt file name");
    }
    std::ofstream file(outputFileName);
    if(!file.is_open()){
        throw std::runtime_error("File not opened");
    }
    // try
    message = encode.encodeMessage(message);
    short size = 0;

    for(char elem : message){
        if(size = 8){
            size = 0;

        }
    }
    short index = 0;
    while(index < message.size()){
        file << std::bitset<8>(message.substr(index, 8)).to_ulong(); // try
        file << ' ';
        index += 8;
    }
    file.close();
    file = std::ofstream(outputFileName + "table.txt");
    if(!file.is_open()){
        throw std::runtime_error("Table file not opened");
    }
    keyTable = encode.getKeyTable();
    message.clear();
    for(const std::pair<std::string, char>& elem : keyTable){
        message.append(elem.first + " = " + elem.second + '\n');
        // message.push_back(elem.second);
    }
    file << message;
    file.close();
    message.clear();
    keyTable.clear();
}

void System::readFromBits(){
    if(inputFileName.empty() || !doesExist(inputFileName) || !doesExist(inputFileName + "table.txt")){
        throw std::invalid_argument("Empty name or Input txt file or table for input txt file does not exist");
    }
    std::ifstream file(inputFileName);
    if(!file.is_open()){
        throw std::runtime_error("File not opened");
    }
    std::string data = "";
    char c;
    while(file.get(c)){
        if(c == ' ' || c == '\0'){
            if(!data.empty()){
                message.append(std::bitset<8>(std::stoi(data)).to_string()); // try
                data.clear();
            }
            continue;
        }
        data.push_back(c);
    }
    file.close();
    file = std::ifstream(inputFileName + "table.txt");
    if(!file.is_open()){
        throw std::runtime_error("Table file not opened");
    }
    short spaceCnt = 0;
    char character;
    while(file.get(c)){
        if(c == ' '){
            ++spaceCnt;
            continue;
        }
        else if(c == '\n'){
            spaceCnt = 0;
            keyTable[data] = character;
            data.clear();
            continue;
        }
        else if(spaceCnt == 0){
            data.push_back(c);
        }
        else if(spaceCnt == 2){
            character = c;
        }
    }
    file.close();
    if(message.empty() || keyTable.empty()){
        throw std::invalid_argument("Empty Input txt file or Empty key table txt file");
    }
    std::cout << "---------------" << std::endl;
    std::cout << "MESSAGE : " << message << std::endl;
    std::cout << "---------------" << std::endl;
}


void System::compress(){
    readFromFileCompress();
    //assert(meesage ! empty)
    // writeToFileCompress();
    writeToBits(); // test
}

void System::decompress(){
    // readFromFileDecompress();
    readFromBits(); // test
    // assert(message ! empty)
    writeToFileDecompress(); // how many bits last one && bool flag
}

void System::debug(){
    readFromFileCompress();
    // assert(message ! empty)
    message = encode.encodeMessage(message);
    std::string binary = "";
    std::vector<std::string> binaryNum;
    std::vector<unsigned long> decimal;
    short size = 0;
    for(char c : message){
        if(size == 8){
            size = 0;
            binaryNum.push_back(binary);
            decimal.push_back(std::bitset<8>(binary).to_ulong()); // try catch 
            binary.clear();
        }
        binary.push_back(c);
        ++size;
    }
    if(!binary.empty()){
        binaryNum.push_back(binary);
        decimal.push_back(std::bitset<8>(binary).to_ulong());//try
    }
    assert(binaryNum.size() == decimal.size());
    for(const std::string& elem : binaryNum){
        std::cout << elem << " ";
    }
    std::cout << " -> " << std::endl;
    for(const unsigned long& elem : decimal){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
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
            std::cout << "No mode has been set" << std::endl;
            return;
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