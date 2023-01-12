#include "Encoder.h"

void Encoder::constructHistogram(const std::string& message){
    for(char character : message){
        ++occurences[character];
        // std::cout << "CHARACTER : " << character << " OCCURENCE : " << occurences[character] << std::endl;
    }
}

void Encoder::clearHistogram(){
    for(short i = 0; i < 128; i++){
        occurences[i] = 0;
    }
}

void Encoder::constructHuffmanTree(){
    // std::cout << "----------------" << std::endl;
    // for(short i = 0; i < 128; i++){
    //     std::cout << "ELEM : " << char(i) << " = " << occurences[i] << std::endl;
    // }
    // std::cout << "----------------" << std::endl;
    // int size = 0;
    for(short i = 0; i < 128; i++){
        if(occurences[i] != 0){
            // std::cout << "CHARACTER : " << char(i) << " OCCURENCE : " << occurences[i] << std::endl;
            queue.push(HTree(char(i), occurences[i]));
            // ++size;
        }
    }
    // assert(queue.size() == size);
    while(!queue.empty() & queue.size() >= 2){
        HTree first(queue.top());
        // std::cout << "FIRST CNT : " << first.getCnt() << std::endl;
        queue.pop();
        HTree second(queue.top());
        // std::cout << "SECOND CNT : " << second.getCnt() << std::endl;
        queue.pop(); // check this 
        queue.push(HTree(first, second));
    }
    huffmanTree = queue.top();
    // std::cout << " BY LEVELS : " << std::endl;
    // huffmanTree.printByLevels();
    queue.pop();
    assert(queue.empty());
}

void Encoder::constructKeyTable(){
    keyTable.clear();
    for(short i = 0; i < 128; i++){
        if(occurences[i] != 0){
            // keyTable.insert(huffmanTree.getCharacterCode(i), occurences[i]);
            // std::cout << "CHAR : " << char(i) << std::endl;
            keyTable[huffmanTree.getCharacterCode(char(i))] = char(i);
            // std::cout << char(i) << " === " << char(i) << std::endl;
            // keyTable.insert({huffmanTree.getCharacterCode(char(i)), char(i)});
            // keyTable.insert(std::make_pair(huffmanTree.getCharacterCode(char(i)), char(i)));
            // std::cout << elem.first <<  " = " << huffmanTree.getCharacterCode(elem.first) << std::endl;
            // std::cout << "CODE : " << huffmanTree.getCharacterCode(char(i)) << " = " << keyTable[huffmanTree.getCharacterCode(char(i))] << " = " << i << " = " << char(i) << std::endl;
            // std::cout << "Size : " <<keyTable.size() << std::endl;
        }
    }
    // std::cout << "------------" << std::endl;
    //         std::cout << "Size : " <<keyTable.size() << std::endl;
    // for(const std::pair<std::string, char>& elem : keyTable){
    //     std::cout << elem.first << " = " << elem.second << std::endl;
    // }
    // std::cout << "------------" << std::endl;
}

std::string Encoder::encodeMessage(const std::string& message){
    if(message.empty()){
        return "";
    }
    // assert(huffmanTree.getCnt() == 0);
    // std::cout << "CNT TREE : " << huffmanTree.getCnt() << std::endl;
    // huffmanTree.printByLevels();
    constructHistogram(message);
    // std::cout << "HISTOGRAM SIZE : " << occurences.size() << std::endl;
    constructHuffmanTree();
    // std::cout << "Queue size : " << queue.size() << std::endl;
    // std::cout << "CNT TREE AFTER CONSTRUCTION: " << huffmanTree.getCnt() << std::endl;
    std::string result = "";
    // std::cout << "TREE by levels : ";
    // huffmanTree.printByLevels();
    for(char character : message){
        result.append(huffmanTree.getCharacterCode(character));
        // std::cout << "CHARACTER : " << character << " = " << huffmanTree.getCharacterCode(character) << std::endl;
    }
    // std::cout << std::endl;
    constructKeyTable();
    // std::cout << "KEY TABLE SIZE : " << occurences.size() << std::endl;
    clearHistogram();
    // huffmanTree.clearTree(); 
    return result;
}

std::unordered_map<std::string, char> Encoder::getKeyTable(){
    return keyTable;
}
