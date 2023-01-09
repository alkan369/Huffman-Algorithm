#include "Encoder.h"

void Encoder::constructHistogram(const std::string& message){
    for(char character : message){
        ++occurences[character];
    }
}

void Encoder::constructHuffmanTree(){
    for(std::pair<char, size_t> elem : occurences){
        queue.push(HTree(elem.first, elem.second));
    }
    while(!queue.empty() & queue.size() >= 2){
        HTree first(queue.top());
        queue.pop();
        HTree second(queue.top());
        queue.push(HTree(first, second));
        queue.pop();
    }
    huffmanTree = queue.top();
    queue.pop();
    assert(queue.empty());
}

void Encoder::constructKeyTable(){
    keyTable.clear();
    for(const std::pair<char, size_t>& elem : occurences){
        keyTable[huffmanTree.getCharacterCode(elem.first)] = elem.first;
    }
}

std::string Encoder::encodeMessage(const std::string& message){
    // assert(huffmanTree.getCnt() == 0);
    std::cout << "CNT TREE : " << huffmanTree.getCnt() << std::endl;
    // huffmanTree.printByLevels();
    constructHistogram(message);
    std::cout << "HISTOGRAM SIZE : " << occurences.size() << std::endl;
    constructHuffmanTree();
    std::cout << "CNT TREE AFTER CONSTRUCTION: " << huffmanTree.getCnt() << std::endl;
    std::string result = "";
    std::cout << "TREE by levels : ";
    huffmanTree.printByLevels();
    for(char character : message){
        result.append(huffmanTree.getCharacterCode(character));
        // std::cout << huffmanTree.getCharacterCode(character) << std::endl;
    }
    std::cout << std::endl;
    constructKeyTable();
    std::cout << "KEY TABLE SIZE : " << occurences.size() << std::endl;
    occurences.clear();
    huffmanTree.clearTree();
    return result;
}

std::unordered_map<std::string, char> Encoder::getKeyTable(){
    return keyTable;
}
