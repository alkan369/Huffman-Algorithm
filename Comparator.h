#pragma once
#include "HTree.h"

class Comparator{
    public:
    // needed to construct minHeap with Huffman trees
    bool operator()(const HTree& firstTree, const HTree& secondTree){
        return firstTree.getCnt() > secondTree.getCnt();
    }
};