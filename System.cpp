#include "System.h"

// private

// clears the current message and current key table
void System::clearMessageAndTable(){
    message.clear();
    keyTable.clear();
}

// checks if file with given name exists
bool System::doesExist(const std::string& fileName){
    std::ifstream file(fileName);
    bool exists = file.good();
    file.close();
    return exists;
}

// checks if ifstream file is opened successfuly
void System::checkOpenInputFile(std::ifstream& file, const std::string& fileName){
    if(!file.is_open()){
        throw std::runtime_error(fileName + " not opened");
    }
}

// checks if ofstream file is opened successfuly
void System::checkOpenOutputFile(std::ofstream& file, const std::string& fileName){
    if(!file.is_open()){
        throw std::runtime_error(fileName + " not opened");
    }
}

// reads the whole file char by char and adds it to the current message
void System::readFile(std::ifstream& file){
    char c;
    while(file.get(c)){
        message.push_back(c);
    }
}

// reads the key table saved in a file
void System::readKeyTable(std::ifstream& file, std::string& data){
    bool foundEqualSign = false; // default values
    char character = '\n'; // default values
    char c;
    // reading the file char by char
    while(file.get(c)){
        // if '=' ic encountered and equal sign has not been found yet
        if(c == '=' && !foundEqualSign){
            // then foundEqualSign value is changed to true
            foundEqualSign = true;
            continue;
        }
        if(c == '\n'){
            // if it's an end of a line
            if(data.empty()){
                // if data is empty, there is not anything to create key table from
                continue;
            }
            // the foundEqualSign is changed to false again(we are starting new line)
            foundEqualSign = false;
            //adding a new key 'data' with value 'charactet' to the key table
            keyTable[data] = character; // check this
            if(character != '\n'){
                keyTable[data] = character;
            }
            // and clearing the data string
            data.clear();
            continue;
        }
        if(!foundEqualSign){
            // if equal sing has not been found(it means that still encoded part of key table is being read)
            data.push_back(c);
        }
        else{
            // if(character){
            //     delete character;
            // }
            
            // if equal sign has been found(the next character is the character equal to the previous encoded part)
            character = c;
        }
    }
}

void System::writeToFileCompress(){
    if(outputFileName.empty()){
        throw std::invalid_argument("Output txt file name empty");
    }
    std::ofstream file(outputFileName);
    checkOpenOutputFile(file, outputFileName);
    file << encode.encodeMessage(message);
    file.close();
    file = std::ofstream(outputFileName + "table.txt");
    keyTable = encode.getKeyTable();
    checkOpenOutputFile(file, outputFileName + "table.txt");
    for(std::pair<std::string, char> elem : keyTable){
        file << elem.first + "=" + elem.second + '\n';
    }
    file.close();
}

void System::readFromFileCompress(){
    if(inputFileName.empty() || !doesExist(inputFileName)){
        throw std::invalid_argument("Input txt file name empty or does not exist");
    }
    std::ifstream file(inputFileName);
    checkOpenInputFile(file, inputFileName);
    readFile(file);
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
    checkOpenOutputFile(file, outputFileName);
    decode.setKeyTable(keyTable);
    file << decode.decodeMessage(message);
    file.close();
}

void System::readFromFileDecompress(){
    if(inputFileName.empty() || !doesExist(inputFileName) || !doesExist(inputFileName + "table.txt")){
        throw std::invalid_argument("Empty name or Input txt file or table for input txt file does not exist");
    }
    std::ifstream file(inputFileName);
    checkOpenInputFile(file, inputFileName);
    readFile(file);
    file.close();
    file = std::ifstream(inputFileName + "table.txt");
    checkOpenInputFile(file, inputFileName + "table.txt");
    std::string binary = "";
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
    message = encode.encodeMessage(message);
    short size = 0;
    short index = 0;
    short lastBits = 8;
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
    file << lastBits;
    file << '\n';
    keyTable = encode.getKeyTable();
    message.clear();
    for(const std::pair<std::string, char>& elem : keyTable){
        file << elem.first + "=" + elem.second + '\n';
    }
    file.close();
}

void System::readFromBits(){
    if(inputFileName.empty() || !doesExist(inputFileName) || !doesExist(inputFileName + "table.txt")){
        throw std::invalid_argument("Empty name or Input txt file or table for input txt file does not exist");
    }
    std::ifstream file(inputFileName);
    checkOpenInputFile(file, inputFileName);
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
    std::string lastBits = "";
    file >> lastBits;
    readKeyTable(file, data);
    file.close();
    if(message.empty() || keyTable.empty()){
        throw std::invalid_argument("Empty Input txt file or Empty key table txt file");
    }
    if(std::stoi(lastBits) != 8){
        data = message.substr(message.size() - 8, 8);
        message.erase(message.size() - 8, message.size());
        message.append(BitSetHelper().getString(std::stoi(lastBits), std::bitset<8>(data).to_ulong()));
    }
}

void System::printToScreen(){
    std::string encodedMessage = encode.encodeMessage(message);
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
    std::cout << " ->  " << std::endl;
    for(const unsigned long& elem : decimal){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    std::cout << "Original data size : " << message.size() * 8 << std::endl;
    std::cout << "Compressed data size : " << encodedMessage.size() << std::endl;
    std::cout << "Compression level : " << encodedMessage.size() * 100 / (message.size() * 8)  << "% of original : " << message.size() * 8 << std::endl;
}


void System::compress(){
    try{
        assert(message.empty() && keyTable.empty());
        readFromFileCompress();
        assert(!message.empty());
        if(workWithBits){
            writeToBits(); // test
        }
        else{
            writeToFileCompress();
        }
    }
    catch(std::invalid_argument& e){
        std::cout << e.what() << std::endl;
    }
    catch(std::runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    catch(...){
        std::cout << "Compression problem occurred" << std::endl;
    }
    clearMessageAndTable();
}

void System::decompress(){
    try{
        assert(message.empty() && keyTable.empty());
        if(workWithBits){
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
    }
    catch(std::runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    catch(...){
        std::cout << "Decompression problem occurred" << std::endl;
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
    }
    catch(std::runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    catch(...){
        std::cout << "Debug problem occurred" << std::endl;
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
    }
    workMode = -1;
}