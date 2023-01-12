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
        // std::cout << "ENTERED MESSAGE : " << message << std::endl;
        for(char character : message){
            code.push_back(character);
            if(keyTable.find(code) != keyTable.end()){
                // std::cout << "CODE : " << code << " = " << "CHAR : "<< keyTable[code] << std::endl;
                result.push_back(keyTable[code]);
                code.clear();
            }
        }
        return result;
    }
};