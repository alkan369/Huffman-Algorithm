#include "Encoder.h"

void Encoder::constructHistogram(const std::string& message){
    for(char character : message)
        ++occurences[character];
}

void Encoder::constructHuffmanTree(){
    for(std::pair<char, size_t> elem : occurences)
        queue.push(HTree(elem.first, elem.second));
    while(!queue.empty() & queue.size() >= 2){
        HTree first(queue.top());
        queue.pop();
        HTree second(queue.top());
        queue.push(HTree(first, second));
        queue.pop();
    }
    huffmanTree = queue.top();
    queue.pop();
}

Encoder::Encoder() = default;

std::string Encoder::encodeMessage(const std::string &message){
    constructHistogram(message);
    constructHuffmanTree();
    std::string result = "";
    for(char character : message)
        result.append(huffmanTree.getCharacterCode(character));
    occurences.clear();
    return result;
}