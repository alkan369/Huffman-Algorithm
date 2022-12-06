#pragma once
#include <unordered_map>
#include <string>

class Decoder{
    private:
    std::unordered_map<std::string, char> keyTable;

    public:
    Decoder() = default;

    std::string decodeMessage(const std::string& message){
        std::string result = "";
        std::string code = "";
        for(char character : message){
            code.push_back(character);
            if(keyTable.find(code) != keyTable.end()){
                result.push_back(keyTable[code]);
                code.clear();
            }
        }
        return result;
    }
};