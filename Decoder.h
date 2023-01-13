#pragma once
#include <unordered_map>
#include <string>

class Decoder{
    private:
    std::unordered_map<std::string, char> keyTable;

    public:
    Decoder() = default;

    void setKeyTable(const std::unordered_map<std::string, char>& newKeyTable){
        if(newKeyTable.empty()){
            // if empty key table is given, exception is thrown
            throw std::invalid_argument("Empty Key Table");
        }
        keyTable = newKeyTable;
    }

    std::string decodeMessage(const std::string& message){
        if(message.empty()){
            return "";
        }
        std::string result = "";
        std::string code = "";
        // iterating through the given message
        for(char character : message){
            // adding the current character to a string
            code.push_back(character);
            if(keyTable.find(code) != keyTable.end()){ // if the code is found in the key table
                result.push_back(keyTable[code]); // the result char is added to the string
                code.clear();
            }
        }
        return result;
    }
};