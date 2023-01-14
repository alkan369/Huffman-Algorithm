#include "Encoder.h"

// private

void Encoder::constructHistogram(const std::string& message){
    for(char character : message){
        // incrementing the data in character index in the array
        ++occurences[character];
    }
}

void Encoder::clearHistogram(){
    for(short i = 0; i < 128; i++){
        // clearing the histogram after using it
        occurences[i] = 0;
    }
}

void Encoder::constructHuffmanTree(){
    for(short i = 0; i < 128; i++){
        if(occurences[i] != 0){
            // constructing Huffman tree of every character with its occurence
            // and pushing it to a minHeap
            queue.push(HTree(char(i), occurences[i]));
        }
    }
    while(!queue.empty() & queue.size() >= 2){
        // taking the first two Huffman trees with smallest occurence
        // and removing them from the heap
        HTree first(queue.top());
        queue.pop();
        HTree second(queue.top());
        queue.pop();
        // constructing new Huffman tree from the previous two Huffman trees
        // and pushing it in the minHeap again
        queue.push(HTree(first, second));
    }
    // the last element in the minHeap is our final constructed Huffman tree
    huffmanTree = queue.top();
    queue.pop();
    // making sure that there is not any other left Huffman tree in the queue
    assert(queue.empty());
}

void Encoder::constructKeyTable(){
    keyTable.clear(); // clearing the key table
    for(short i = 0; i < 128; i++){
        if(occurences[i] != 0){
            // adding the code of the character as the key of key table
            // and the character itself as the value
            keyTable[huffmanTree.getCharacterCode(char(i))] = char(i);
        }
    }
}

// public

std::string Encoder::encodeMessage(const std::string& message){
    if(message.empty()){
        return "";
    }
    constructHistogram(message); // constructing histogram
    constructHuffmanTree(); // and the huffman tree before encoding the message
    std::string result = "";
    // iterating through the given message
    for(char character : message){
        // appending the encoding of the given character
        result.append(huffmanTree.getCharacterCode(character));
    }
    constructKeyTable(); // constructing the key table after getting the encoded message
    clearHistogram(); // clearing the histogram after the encoding
    return result;
}

std::unordered_map<std::string, char> Encoder::getKeyTable(){
    return keyTable;
}