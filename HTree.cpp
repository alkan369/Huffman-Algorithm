#include "HTree.hpp"
#include <queue>

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

bool HTree::getCharacterCodeHelper(Node * current, char searched, std::string& encode){
    // std::cout << "LINE 38" << std::endl;
    if(isLeaf(current)){
        if(current->data == searched)
            return true;
        encode.pop_back();
    // std::cout << "LINE 43" << std::endl;
        return false;
    }
    // std::cout << "LINE 46" << std::endl;
    encode.push_back('0');
    if(getCharacterCodeHelper(current->left, searched, encode))
        return true;
    // encode.pop_back();
    // std::cout << "LINE 51" << std::endl;
    encode.push_back('1');
    // std::cout << "LINE 53" << std::endl;
    return getCharacterCodeHelper(current->right, searched, encode);
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

std::string HTree::getCharacterCode(char searched){
    std::string result = "";
    if(getCharacterCodeHelper(root, searched, result));
        return result;
    return "";
}

void HTree::print() const{
    printHelper(root);
}

void HTree::printByLevels() const{
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
