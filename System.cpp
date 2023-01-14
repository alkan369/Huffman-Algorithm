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
        // if '=' is encountered and equal sign has not been found yet
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
            //adding a new key 'data' with value 'character' to the key table
            keyTable[data] = character;
            // and clearing the data string
            data.clear();
            continue;
        }
        if(!foundEqualSign){
            // if equal sing has not been found(it means that still encoded part of the key table is being read)
            data.push_back(c);
        }
        else{
            // if equal sign has been found(the next character is the character equal to the previous encoded part)
            character = c;
        }
    }
}

void System::writeToFileCompress(){
    // if no output file name is given -> exception
    if(outputFileName.empty()){
        throw std::invalid_argument("Output txt file name empty");
    }
    std::ofstream file(outputFileName);
    checkOpenOutputFile(file, outputFileName); // checking if the file has been successfuly opened
    // else writing the encoded string to ofstream file
    file << encode.encodeMessage(message);
    file.close();
    file = std::ofstream(outputFileName + "table.txt");
    keyTable = encode.getKeyTable();
    checkOpenOutputFile(file, outputFileName + "table.txt"); // checking if the file has been successfuly opened
    // also writing the key table to another file (output file name + table.txt)
    for(std::pair<std::string, char> elem : keyTable){
        file << elem.first + "=" + elem.second + '\n';
    }
    file.close();
}

void System::readFromFileCompress(){
    // if no input file name is given or if file with such name doesn't exist -> exception
    if(inputFileName.empty() || !doesExist(inputFileName)){
        throw std::invalid_argument("Input txt file name empty or does not exist");
    }
    std::ifstream file(inputFileName);
    checkOpenInputFile(file, inputFileName); // checking if the file has been successfuly opened
    readFile(file);
    file.close();
    // if it's an empty file -> exception
    if(message.empty()){
        throw std::invalid_argument("Empty Input txt file content");
    }
}

void System::writeToFileDecompress(){
    // if no output file name is given -> exception
    if(outputFileName.empty()){
        throw std::invalid_argument("Empty Output file name");
    }
    std::ofstream file(outputFileName);
    checkOpenOutputFile(file, outputFileName); // checking if the file has been successfuly opened
    // setting the current key table to the decoder
    decode.setKeyTable(keyTable);
    // and writing the decoded string to the file
    file << decode.decodeMessage(message);
    file.close();
}

void System::readFromFileDecompress(){
    // if no input file name is given or file with such name exists or
    // file with the name + "table.txt" does not exist(there is no table for that file) -> exception
    if(inputFileName.empty() || !doesExist(inputFileName) || !doesExist(inputFileName + "table.txt")){
        throw std::invalid_argument("Empty name or Input txt file or table for input txt file does not exist");
    }
    std::ifstream file(inputFileName);
    checkOpenInputFile(file, inputFileName); // checking if the file has been successfuly opened
    readFile(file); // reading the file with the encoded message
    file.close();
    file = std::ifstream(inputFileName + "table.txt");
    checkOpenInputFile(file, inputFileName + "table.txt");
    std::string binary = "";
    readKeyTable(file, binary); // reading the key table of the encoded message
    file.close();
    // if message or key table is empty(there is no content in any of the two files) -> exception
    if(message.empty() || keyTable.empty()){
        throw std::invalid_argument("Empty Input txt file or Empty key table txt file");
    }
}

void System::writeToBits(){
    // if no output file name is given -> exception
    if(outputFileName.empty()){
        throw std::invalid_argument("Empty Output txt file name");
    }
    std::ofstream file(outputFileName);
    checkOpenOutputFile(file, outputFileName); // checking if the file has been successfuly opened
    message = encode.encodeMessage(message); // getting the encoded message
    short size = message.size();
    short index = 0;
    short lastBits = 8;
    while(index < size){
        if(index + 8 > size){
            // if the last bits are less than 8, the size of the bits is saved
            lastBits = size - index;
        }
        // writing the decimal number of binary substring with size 8
        file << std::bitset<8>(message.substr(index, 8)).to_ulong();
        file << ' ';
        index += 8; // iterating through the string with step 8
    }
    file.close();
    file = std::ofstream(outputFileName + "table.txt");
    checkOpenOutputFile(file, outputFileName + "table.txt"); // checking if the file has been successfuly opened
    // writing the size of the last bits
    file << lastBits;
    file << '\n';
    keyTable = encode.getKeyTable();
    for(const std::pair<std::string, char>& elem : keyTable){
        // writing the key table values to the file
        file << elem.first + "=" + elem.second + '\n';
    }
    file.close();
}

void System::readFromBits(){
    // if no input file name is given or file with such name exists or
    // file with the name + "table.txt" does not exist(there is no table for that file) -> exception
    if(inputFileName.empty() || !doesExist(inputFileName) || !doesExist(inputFileName + "table.txt")){
        throw std::invalid_argument("Empty name or Input txt file or table for input txt file does not exist");
    }
    std::ifstream file(inputFileName);
    checkOpenInputFile(file, inputFileName); // checking if the file has been successfuly opened
    std::string data = "";
    char c;
    // reading the file character by character
    while(file.get(c)){
        if(c == ' ' || c == '\0' || c == '\n'){
            if(!data.empty()){
                // if the data string is not empty, converting the decimal number
                // into its binary form with size 8
                message.append(std::bitset<8>(std::stoi(data)).to_string());
                data.clear();
            }
            continue;
        }
        data.push_back(c);
    }
    file.close();
    file = std::ifstream(inputFileName + "table.txt");
    checkOpenInputFile(file, inputFileName + "table.txt"); // checking if the file has been successfuly opened
    std::string lastBits = "";
    // getting the first line for the bits size of the last number
    file >> lastBits;
    readKeyTable(file, data); // reading the key table from the rest of the file
    file.close();
    // if message or the key table is empty(there is no content in any of the two files) -> exception
    if(message.empty() || keyTable.empty()){
        throw std::invalid_argument("Empty Input txt file or Empty key table txt file");
    }
    // if the size of the last number is not 8
    if(std::stoi(lastBits) != 8){
        // saving the last 8 bits from the string
        data = message.substr(message.size() - 8, 8);
        // and removing them
        message.erase(message.size() - 8, message.size());
        // and appending the same bits, but with the actual size(which is lastBits)
        // the BitSetHelper class is used here
        message.append(BitSetHelper().getString(std::stoi(lastBits), std::bitset<8>(data).to_ulong()));
    }
}

void System::printToScreen(){
    // getting the encoded message
    std::string encodedMessage = encode.encodeMessage(message);
    std::vector<std::string> binaryNum;
    std::vector<unsigned long> decimal;
    short size = encodedMessage.size();
    short index = 0;
    while(index < size){
            // saving the binary form of the substring with step 8
            binaryNum.push_back(encodedMessage.substr(index, 8));
            // and saving the decimal form of the same substring
            decimal.push_back(std::bitset<8>(encodedMessage.substr(index, 8)).to_ulong());
        // iterating through the string with step 8
        index += 8;
    }
    // making sure that the binary vector and decimal vector are same size
    assert(binaryNum.size() == decimal.size());
    // printing the binary form
    for(const std::string& elem : binaryNum){
        std::cout << elem << " ";
    }
    std::cout << " ->  " << std::endl;
    // printing the decimal form
    for(const unsigned long& elem : decimal){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    std::cout << "Original data size : " << message.size() * 8 << std::endl;
    std::cout << "Compressed data size : " << encodedMessage.size() << std::endl;
    // printing the level of compression
    std::cout << "Compression level : " << encodedMessage.size() * 100 / (message.size() * 8)  << "% of original : " << message.size() * 8 << std::endl;
}


void System::compress(){
    try{
        // making sure that the message and key table are empty before working with them
        assert(message.empty() && keyTable.empty());
        readFromFileCompress(); // reading a file in compression mode
        // making sure that the message is not empty
        assert(!message.empty()); // making sure the message is not empty(there is content in the file)
        if(workWithBits){
            writeToBits(); // used only in doctest
        }
        else{
            writeToFileCompress(); // writing to file in compression mode
        }
    }
    catch(std::invalid_argument& e){
        std::cout << e.what() << std::endl;
    }
    catch(std::runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    catch(...){
        // if any other unexpected exception is thrown
        std::cout << "Compression problem occurred" << std::endl;
    }
    // clearing the current message and current key table after working with them
    // or after exception is thrown
    clearMessageAndTable();
}

void System::decompress(){
    try{
        // making sure that the message and key table are empty before working with them
        assert(message.empty() && keyTable.empty());
        if(workWithBits){
            readFromBits(); // used only in doctest
        }
        else{
            readFromFileDecompress(); // reading from file in decompression mode
        }
        assert(!message.empty()); // making sure the message is not empty(there is content in the file)
        writeToFileDecompress(); // writing to file in decompression mode
    }
    catch(std::invalid_argument& e){
        std::cout << e.what() << std::endl;
    }
    catch(std::runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    catch(...){
        // if any other unexpected exception is thrown
        std::cout << "Decompression problem occurred" << std::endl;
    }
    // clearing the current message and current key table after working with them
    // or after exception is thrown
    clearMessageAndTable();
}

void System::debug(){
    try{
        // making sure that the message and key table are empty before working with them
        assert(message.empty() && keyTable.empty());
        readFromFileCompress(); // reading from file in compression mode
        assert(!message.empty());  // making sure the message is not empty(there is content in the file)
        printToScreen(); // printing the encoded message and level of conpression to the screen
    }
    catch(std::invalid_argument& e){
        std::cout << e.what() << std::endl;
    }
    catch(std::runtime_error& e){
        std::cout << e.what() << std::endl;
    }
    catch(...){
        // if any other unexpected exception is thrown
        std::cout << "Debug problem occurred" << std::endl;
    }
    // clearing the current message after working with it(or after exception is thrown)
    // here the key table has not been modified
    message.clear();
}

// public

void System::setWorkWithBits(bool bitsMode){
    // used only in doctest
    workWithBits = bitsMode;
}

bool System::getWorkWithBits()const{
    // used only in doctest
    return workWithBits;
}

void System::setMode(short mode){
    // making sure that only valid modes are given
    assert(mode >= 0 || mode <= 2);
    workMode = mode;
}

int System::getMode()const{
    // getting the current working mode
    return workMode;
}

void System::setInputFileName(const std::string& input){
    // if input file name is empty -> exception
    if(input.empty()){
        throw std::invalid_argument("Input file name empty");
    }
    std::cout << "Input file set" << std::endl;
    inputFileName = input;
}

const std::string& System::getInputFileName() const{
    // getting the current input file name
    return inputFileName;
}

void System::setOutputFileName(const std::string& output){
    // if output file name is empty -> exception
    if(output.empty()){
        throw std::invalid_argument("Output file name empty");
    }
    std::cout << "Output file set" << std::endl;
    outputFileName = output;
}

const std::string& System::getOutputFileName() const{
    // getting the current output file name
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
            // if the program is started and no workmode has been set -> exception
            throw std::invalid_argument("No mode has been set");
    }
    // after the program is done, the workmode is set back to -1("no work mode has been set")
    workMode = -1;
}