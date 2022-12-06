#pragma once
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include "HTree.h"
#include "Comparator.h"

class Encoder{
    private:
    std::unordered_map<char, size_t> occurences;
    std::priority_queue<HTree, std::vector<HTree>, Comparator> queue;
    HTree huffmanTree;

    void constructHistogram(const std::string& message);
    void constructHuffmanTree();

    public:
    Encoder();

    std::string encodeMessage(const std::string& message);
};