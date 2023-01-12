#include "System.h"

// private

void System::clearMessageAndTable(){
    message.clear();
    keyTable.clear();
}

bool System::doesExist(const std::string& fileName){
    std::ifstream file(fileName);
    bool exists = file.good();
    file.close();
    return exists;
}

void System::checkOpenInputFile(std::ifstream& file, const std::string& fileName){
    if(!file.is_open()){
        throw std::runtime_error(fileName + " not opened");
    }
}

void System::checkOpenOutputFile(std::ofstream& file, const std::string& fileName){
    if(!file.is_open()){
        throw std::runtime_error(fileName + " not opened");
    }
}

void System::readLine(std::ifstream& file){
    char c;
    while(file.get(c)){
        message.push_back(c);
    }
}

void System::readKeyTable(std::ifstream& file, std::string& data){
bool foundEqualSign = false;
    char* character = nullptr;
    char c;
    while(file.get(c)){
        if(c == '=' && !foundEqualSign){
            foundEqualSign = true;
            continue;
        }
        if(c == '\n'){
            // spaceCnt = 0;
            if(data.empty()){
                continue;
            }
            foundEqualSign = false;
            keyTable[data] = '\n';
            if(character){
                keyTable[data] = *character;
                // foundEqualSign = false;
            }
            data.clear();
            continue;
        }
        if(!foundEqualSign){
            data.push_back(c);
        }
        else{
            if(character){
                delete character;
            }
            character = new char(c);
        }
    }
}


void System::writeToFileCompress(){
    if(outputFileName.empty()){
        throw std::invalid_argument("Output txt file name empty");
    }
    std::ofstream file(outputFileName);
    // if(!file.is_open()){
    //     throw std::runtime_error("Output txt file not opened");
    // }
    checkOpenOutputFile(file, outputFileName);
    // auto result = encode.encodeMessage(message);
    // file.write(result.c_str(), result.size());
    //assert(!message.empty())
    file << encode.encodeMessage(message);
    file.close();
    file = std::ofstream(outputFileName + "table.txt");
    keyTable = encode.getKeyTable();
    // std::string tableToString = "";
    message.clear();
    // if(!file.is_open()){
    //     throw std::runtime_error("Output txt file for key table not opened");
    // }
    checkOpenOutputFile(file, outputFileName + "table.txt");
    for(std::pair<std::string, char> elem : keyTable){
        message.append(elem.first + "=" + elem.second + '\n');
        // std::cout << elem.first << " = " << elem.second << std::endl;
        // message.push_back(elem.second);
        // message.push_back('\n');
    }
    // std::cout << std::endl;
    file << message;
    file.close();
    // clearMessageAndTable();
    // message.clear();
    // keyTable.clear();
}

void System::readFromFileCompress(){
    if(inputFileName.empty() || !doesExist(inputFileName)){
        throw std::invalid_argument("Input txt file name empty or does not exist");
    }
    std::ifstream file(inputFileName);
    // if(!file.is_open()){
    //     throw std::runtime_error("Input txt file not opened");
    // }
    checkOpenInputFile(file, inputFileName);
    readLine(file);
    // char c;
    // while(file.get(c)){
    //     message.push_back(c);
    // }
    file.close();
    if(message.empty()){
        throw std::invalid_argument("Empty Input txt file content");
    }
}

void System::writeToFileDecompress(){
    if(outputFileName.empty()){
        throw std::invalid_argument("Empty Output file name");
    }
    std::ofstream file(outputFileName);
    // if(!file.is_open()){
    //     throw std::runtime_error("Output txt file not opened");
    // }
    checkOpenOutputFile(file, outputFileName);
    decode.setKeyTable(keyTable);
    file << decode.decodeMessage(message);
    file.close();
    // clearMessageAndTable();
    // message.clear();
    // keyTable.clear();
}

void System::readFromFileDecompress(){
    if(inputFileName.empty() || !doesExist(inputFileName) || !doesExist(inputFileName + "table.txt")){
        throw std::invalid_argument("Empty name or Input txt file or table for input txt file does not exist");
    }
    std::ifstream file(inputFileName);
    // if(!file.is_open()){
    //     throw std::runtime_error("Input file not opened");
    // }
    checkOpenInputFile(file, inputFileName);
    readLine(file);
    // char c;
    // while(file.get(c)){
    //     message.push_back(c);
    // }
    file.close();
    file = std::ifstream(inputFileName + "table.txt");
    // if(!file.is_open()){
    //     std::runtime_error("Table txt file for Input file not opened");
    // }
    checkOpenInputFile(file, inputFileName + "table.txt");
    std::string binary = "";
    // bool foundEqualSign = false;
    // char* character = nullptr;
    // while(file.get(c)){
    //     if(c == '=' && !foundEqualSign){
    //         foundEqualSign = true;
    //         continue;
    //     }
    //     if(c == '\n'){
    //         // spaceCnt = 0;
    //         if(binary.empty()){
    //             continue;
    //         }
    //         foundEqualSign = false;
    //         keyTable[binary] = '\n';
    //         if(character){
    //             keyTable[binary] = *character;
    //             // foundEqualSign = false;
    //         }
    //         binary.clear();
    //         continue;
    //     }
    //     if(!foundEqualSign){
    //         binary.push_back(c);
    //     }
    //     else{
    //         if(character){
    //             delete character;
    //         }
    //         character = new char(c);
    //     }
    // }
    readKeyTable(file, binary);
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
    checkOpenOutputFile(file, outputFileName);
    // if(!file.is_open()){
    //     throw std::runtime_error("File not opened");
    // }
    // try
    message = encode.encodeMessage(message);
    short size = 0;
    short index = 0;
    short lastBits = 8;
    // 01001101 01001011 0100110
    while(index < message.size()){
        if(index + 8 > message.size()){
            lastBits = message.size() - index;
        }
        file << std::bitset<8>(message.substr(index, 8)).to_ulong(); // try
        file << ' ';
        index += 8;
    }
    file.close();
    file = std::ofstream(outputFileName + "table.txt");
    checkOpenOutputFile(file, outputFileName + "table.txt");
    // if(!file.is_open()){
    //     throw std::runtime_error("Table file not opened");
    // }
    file << lastBits;
    file << '\n';
    keyTable = encode.getKeyTable();
    message.clear();
    for(const std::pair<std::string, char>& elem : keyTable){
        std::cout << elem.first << " = " << elem.second << std::endl; // -> remove this
        message.append(elem.first + "=" + elem.second + '\n');
        // message.push_back(elem.second);
        // message.push_back('\n');
    }
    file << message;
    file.close();
    // clearMessageAndTable();
    // message.clear();
    // keyTable.clear();
}

void System::readFromBits(){
    if(inputFileName.empty() || !doesExist(inputFileName) || !doesExist(inputFileName + "table.txt")){
        throw std::invalid_argument("Empty name or Input txt file or table for input txt file does not exist");
    }
    // std::cout << "---------------" << std::endl;
    // std::cout << "MESSAGE : " << message << std::endl;
    // std::cout << "---------------" << std::endl;
    std::ifstream file(inputFileName);
    checkOpenInputFile(file, inputFileName);
    // if(!file.is_open()){
    //     throw std::runtime_error("File not opened");
    // }
    std::string data = "";
    char c;
    while(file.get(c)){
        if(c == ' ' || c == '\0' || c == '\n'){
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
    checkOpenInputFile(file, inputFileName + "table.txt");
    // if(!file.is_open()){
    //     throw std::runtime_error("Table file not opened");
    // }
    std::string lastBits = "";
    file >> lastBits;
    // bool foundEqualSign = false;
    // char* character = nullptr;
    // while(file.get(c)){
    //     if(c == '=' && !foundEqualSign){
    //         foundEqualSign = true;
    //         continue;
    //     }
    //     if(c == '\n'){
    //         // convert to ptr
    //         // spaceCnt = 0;
    //         if(data.empty()){
    //             continue;
    //         }
    //         foundEqualSign = false;
    //         keyTable[data] = '\n';
    //         if(character){
    //             keyTable[data] = *character;
    //             // foundEqualSign = false;
    //         }
    //         data.clear();
    //         continue;
    //     }
    //     if(!foundEqualSign){
    //         data.push_back(c);
    //     }
    //     else{
    //         if(character){
    //             delete character;
    //         }
    //         character = new char(c);
    //     }
    // }
    readKeyTable(file, data);
    file.close();
    // std::cout << "KEY TABLE" << std::endl;
    // for(auto elem : keyTable){
    //     if(elem.first.empty()){
    //         std::cout << "EMPTYYY !!!!!!!!" << std::endl;
    //     }
    //     std::cout << elem.first << " = " << elem.second << std::endl;
    // }
    // std::cout << std::endl;
    if(message.empty() || keyTable.empty()){
        throw std::invalid_argument("Empty Input txt file or Empty key table txt file");
    }
    // std::cout << "---------------" << std::endl;
    // std::cout << "MESSAGE : " << message << std::endl;
    // std::cout << "---------------" << std::endl;
    if(std::stoi(lastBits) != 8){
        data = message.substr(message.size() - 8, 8);
        message.erase(message.size() - 8, message.size());
        message.append(BitSetHelper().getString(std::stoi(lastBits), std::bitset<8>(data).to_ulong()));
    }
    // std::cout << "---------------" << std::endl;
    // std::cout << "MESSAGE : " << message << std::endl;
    // std::cout << "---------------" << std::endl;
}

void System::printToScreen(){
    // std::cout << "---------------" << std::endl;
    // std::cout << "MESSAGE : " << message << std::endl;
    // std::cout << "---------------" << std::endl;
    std::string encodedMessage = encode.encodeMessage(message);
    // std::cout << "---------------" << std::endl;
    // std::cout << "ENCODED MESSAGE : " << encodedMessage << std::endl;
    // std::cout << "ENCODED MESSAGE size : " << encodedMessage.size() << std::endl;
    // std::cout << "---------------" << std::endl;
    std::string binary = "";
    std::vector<std::string> binaryNum;
    std::vector<unsigned long> decimal;
    short size = 0;
    for(char c : encodedMessage){
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
    std::cout << "Original data size : " << message.size() * 8 << std::endl;
    std::cout << "Compressed data size : " << encodedMessage.size() << std::endl;
    std::cout << "Compression level : " << encodedMessage.size() * 100 / (message.size() * 8)  << "% of original : " << message.size() * 8 << std::endl;
    // assert(keyTable.empty());
    // message.clear();
}


void System::compress(){
    try{
        assert(message.empty() && keyTable.empty());
        readFromFileCompress();
        assert(!message.empty());
        if(workWithBits){
            // std::cout << "WORKING WITH BITS COMPRESS" << std::endl;
            writeToBits(); // test
        }
        else{
            writeToFileCompress();
        }
    }
    catch(std::invalid_argument& e){
        std::cout << e.what() << std::endl;
        // clearMessageAndTable();
        // message.clear();
        // keyTable.clear();
    }
    catch(std::runtime_error& e){
        std::cout << e.what() << std::endl;
        // clearMessageAndTable();
        // message.clear();
        // keyTable.clear();
    }
    catch(...){
        std::cout << "Compression problem occurred" << std::endl;
        // clearMessageAndTable();
        // message.clear();
        // keyTable.clear();
    }
    // assert(!message.empty() && !keyTable.empty());
    clearMessageAndTable();
}

void System::decompress(){
    try{
        assert(message.empty() && keyTable.empty());
        if(workWithBits){
            // std::cout << "WORKING WITH BITS DECOMPRESS" << std::endl;
            readFromBits(); // test
        }
        else{
            readFromFileDecompress();
        }
        assert(!message.empty());
        writeToFileDecompress(); // how many bits last one && bool flag
    }
    catch(std::invalid_argument& e){
        std::cout << e.what() << std::endl;
        // clearMessageAndTable();
        // message.clear();
        // keyTable.clear();
    }
    catch(std::runtime_error& e){
        std::cout << e.what() << std::endl;
        // clearMessageAndTable();
        // message.clear();
        // keyTable.clear();
    }
    catch(...){
        std::cout << "Decompression problem occurred" << std::endl;
        // message.clear();
        // keyTable.clear();
    }
    clearMessageAndTable();
}

void System::debug(){
    try{
        assert(message.empty() && keyTable.empty());
        readFromFileCompress();
        assert(!message.empty());
        printToScreen();
    }
    catch(std::invalid_argument& e){
        std::cout << e.what() << std::endl;
        // clearMessageAndTable();
        // message.clear();
        // keyTable.clear();
    }
    catch(std::runtime_error& e){
        std::cout << e.what() << std::endl;
        // clearMessageAndTable();
        // message.clear();
        // keyTable.clear();
    }
    catch(...){
        std::cout << "Debug problem occurred" << std::endl;
        // clearMessageAndTable();
        // message.clear();
        // keyTable.clear();
    }
    message.clear();
}

// public

void System::setWorkWithBits(bool bitsMode){
    workWithBits = bitsMode;
}

bool System::getWorkWithBits()const{
    return workWithBits;
}

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

const std::string& System::getOutputFileName() const{
    return outputFileName;
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
            // std::cout << "No mode has been set" << std::endl;
            // return
            // break;
    }
    workMode = -1;
}

std::string System::getEncodedMessage(const std::string& message){
    return encode.encodeMessage(message);
}

std::unordered_map<std::string, char> System::getKeyTable(){
    return getKeyTable();
}

std::string System::getDecodedMessage(const std::string& message, const std::unordered_map<std::string, char>& newKeyTable){
    decode.setKeyTable(newKeyTable);
    return decode.decodeMessage(message);
}