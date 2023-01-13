#pragma once
#include <iostream>
#include <queue>


struct Node{
    char data;
    size_t cnt;
    Node* left;
    Node* right;
    Node(char newData, size_t newCnt) : data(newData), cnt(newCnt), left(nullptr), right(nullptr) {}
};

class HTree{
    private:
    Node* root;

    void copy(Node*& current, Node* other); // used in copy constructors and operator=
    void clear(Node* current); // used in destructor
    bool isLeaf(Node* current)const; // checks if current node is leaf
    std::string getCharacterCodeHelper(Node* current, char searched, std::string encode); // gets the coding of entered character

    public:
    HTree();
    HTree(char newData, size_t newCnt);
    HTree(const HTree& first, const HTree& second);
    HTree(const HTree& other);
    HTree operator=(const HTree& other);
    ~HTree();

    size_t getCnt()const;

    std::string getCharacterCode(char searched);

    void printByLevels()const;
};