#pragma once
#include <string>
#include <bitset>

class BitSetHelper{
    public:
    // used only in one method in System class
    // because the bitset<size> must be known in compilation time
    // and in our case the maxium size is 8 bits
    std::string getString(int enteredNum, unsigned long number){
        switch (enteredNum){
            case 1:
                return std::bitset<1>(number).to_string();
            case 2:
                return std::bitset<2>(number).to_string();
            case 3:
                return std::bitset<3>(number).to_string();
            case 4:
                return std::bitset<4>(number).to_string();
            case 5:
                return std::bitset<5>(number).to_string();
            case 6:
                return std::bitset<6>(number).to_string();
            case 7:
                return std::bitset<7>(number).to_string();
            default:
                return std::bitset<8>(number).to_string();
        }
    }
};