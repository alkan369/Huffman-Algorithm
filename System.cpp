#include "System.h"

void System::setMode(short mode){
    if(mode > 1 || mode < 0){
        throw std::invalid_argument("Invalid mode");
    }
    workMode = mode;
}

int System::getMode()const{
    return workMode;
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