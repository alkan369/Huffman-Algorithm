#include "HTree.h"
#include <queue>

void HTree::copy(Node*& current, Node* other){
    if(!other){
        current = nullptr;
        return;
    }
    current = new Node(other->data, other->cnt);
    copy(current->left, other->left);
    copy(current->right, other->right);
}

void HTree::clear(Node *current){
    if(!current)
        return;
    clear(current->left);
    clear(current->right);
    delete current;
    current = nullptr;
}

bool HTree::isLeaf(Node *current)const{
    return !current->left && !current->right;
}

bool HTree::getCharacterCodeHelper(Node* current, char searched, std::string& encode){
    if(isLeaf(current)){
        if(current->data == searched){
            return true;
        }
        encode.pop_back();
        return false;
    }
    encode.push_back('0');
    if(getCharacterCodeHelper(current->left, searched, encode)){
        return true;
    }
    // encode.pop_back();
    encode.push_back('1');
    return getCharacterCodeHelper(current->right, searched, encode);
}

void HTree::printHelper(Node *current)const{
    if(!current){
        return;
    }
    printHelper(current->left);
    if(isLeaf(current)){
        std::cout << "DATA : " << current->data << " ";
    }
    std::cout << "CNT : " << current->cnt << std::endl;
    printHelper(current->right);
}

HTree::HTree() : root(nullptr) {}

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

void HTree::clearTree(){
    clear(root);
    root = nullptr;
}

size_t HTree::getCnt() const{
    return root ? root->cnt : 0;
}

std::string HTree::getCharacterCode(char searched){
    std::string result = "";
    if(getCharacterCodeHelper(root, searched, result))
        return result;
    return "";
}

void HTree::print() const{
    printHelper(root);
}

void HTree::printByLevels() const{
    if(!root){
        return;
    }
    std::queue<Node*> queue;
    queue.push(root);
    while(!queue.empty()){
        int size = queue.size();
        while(size){
            if(isLeaf(queue.front()))
                std::cout << "DATA : " << queue.front()->data << " ";
            std::cout << "CNT : " << queue.front()->cnt << std::endl;
            if(queue.front()->left)
                queue.push(queue.front()->left);
            if(queue.front()->right)
                queue.push(queue.front()->right);
            queue.pop();
            --size;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}
