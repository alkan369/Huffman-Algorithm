#pragma once
#include <string>
#include <unordered_map>
#include <queue>
#include <utility>
#include <vector>
#include <cassert>
#include "HTree.h"
#include "Comparator.h"

class Encoder{
    private:
    size_t occurences[128] = {0}; // 0 - 127 codes for every ASCII char
    std::priority_queue<HTree, std::vector<HTree>, Comparator> queue;
    HTree huffmanTree;
    std::unordered_map<std::string, char> keyTable;

    void constructHistogram(const std::string& message);
    void clearHistogram();
    void constructHuffmanTree();
    void constructKeyTable();

    public:
    Encoder() = default;

    std::string encodeMessage(const std::string& message);
    std::unordered_map<std::string, char> getKeyTable();
};