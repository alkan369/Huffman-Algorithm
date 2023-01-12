#pragma once
#include "../HTree/HTree.h"

class Comparator{
    public:
    bool operator()(const HTree& firstTree, const HTree& secondTree){
        return firstTree.getCnt() > secondTree.getCnt();
    }
    // bool operator()(const std::pair<char, size_t>& firstObject, const std::pair<char, size_t>& secondObject){
    //     return firstObject.second >= secondObject.second;
    // }
};