#pragma once
#include <iostream>

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

    void copy(Node*& current, Node* other);
    void clear(Node* current);
    bool isLeaf(Node* current)const;
    bool getCharacterCodeHelper(Node* current, char searched, std::string& encode);
    void printHelper(Node* current)const;

    public:
    HTree(char newData, size_t newCnt);
    HTree(const HTree& first, const HTree& second);
    HTree(const HTree& other);
    HTree operator=(const HTree& other);
    ~HTree();

    size_t getCnt()const;

    std::string getCharacterCode(char searched);

    void print()const;

    void printByLevels()const;
};