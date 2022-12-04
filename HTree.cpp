#include "HTree.hpp"

void HTree::copy(Node*& current, Node* other){
    // std::cout << "LINE 4" << std::endl;
    if(!other){
        current = nullptr;
        return;
    }
    // std::cout << "LINE 9" << std::endl;
    current = new Node(other->data, other->cnt);
    // std::cout << "CNT : " << current->cnt << std::endl;
    // std::cout << "LINE 11" << std::endl;
    copy(current->left, other->left);
    // std::cout << "LINE 13" << std::endl;
    copy(current->right, other->right);
    // std::cout << "LINE 14" << std::endl;
}

void HTree::clear(Node *current){
    // std::cout << "LINE 4" << std::endl;
    if(!current)
        return;
    // std::cout << "LINE 7" << std::endl;
    clear(current->left);
    clear(current->right);
    // std::cout << "LINE 10" << std::endl;
    delete current;
    current = nullptr;
    // std::cout << "LINE 13" << std::endl;
}

bool HTree::isLeaf(Node *current)const{
    return !current->left && !current->right;
}

void HTree::printHelper(Node *current)const {
    if(!current)
        return;
    printHelper(current->left);
    if(isLeaf(current))
        std::cout << "DATA : " << current->data << " ";
    std::cout << "CNT : " << current->cnt << std::endl;
    printHelper(current->right);
}

HTree::HTree(char newData, size_t newCnt) : root(new Node(newData, newCnt)) {}

HTree::HTree(const HTree &first, const HTree &second){
    root = new Node('\0', first.root->cnt + second.root->cnt);
    copy(root->left, first.root);
    copy(root->right, second.root);
}

HTree::HTree(const HTree &other){
    copy(root, other.root);
}

HTree HTree::operator=(const HTree &other){
    if(this != &other){
        clear(root);
        copy(root, other.root);
    }
    return *this;
}

HTree::~HTree(){
    clear(root);
}

size_t HTree::getCnt() const{
    return root->cnt;
}

void HTree::print() const{
    printHelper(root);
}
