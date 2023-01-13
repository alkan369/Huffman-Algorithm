#include "HTree.h"

// private

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

bool HTree::isLeaf(Node* current)const{
    return current && !current->left && !current->right;
}

std::string HTree::getCharacterCodeHelper(Node* current, char searched, std::string encode){
    if(!current){
        return "";
    }
    if(isLeaf(current)){
        // if the current node is leaf and is the searched character
        // return the current encoding
        if(current->data == searched){
            return encode;
        }
        // else return empty string
        return "";
    }
    std::string result = getCharacterCodeHelper(current->left, searched, encode + '0');
    if(!result.empty()){
        return result;
    }
    // if the result in the left subtree is empty string
    // right subtree is searched
    return getCharacterCodeHelper(current->right, searched, encode + '1');
}

// public

HTree::HTree() : root(nullptr) {}

HTree::HTree(char newData, size_t newCnt) : root(new Node(newData, newCnt)) {}

HTree::HTree(const HTree& first, const HTree& second){
    root = new Node('\0', first.root->cnt + second.root->cnt);
    copy(root->left, first.root);
    copy(root->right, second.root);
}

HTree::HTree(const HTree& other){
    copy(root, other.root);
}

HTree HTree::operator=(const HTree& other){
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
    return root ? root->cnt : 0;
}

std::string HTree::getCharacterCode(char searched){
    return getCharacterCodeHelper(root, searched, ""); // test with &
}

void HTree::printByLevels() const{
    // bfs
    if(!root){
        return;
    }
    std::queue<Node*> queue;
    queue.push(root);
    while(!queue.empty()){
        int size = queue.size();
        while(size){
            if(isLeaf(queue.front())){
                // if the front node is leaf, then the character of the leaf is also printed
                std::cout << "DATA : " << queue.front()->data << " ";
            }
            // the cnt of the current node is printed
            std::cout << "CNT : " << queue.front()->cnt << std::endl;
            if(queue.front()->left){
                // if there is left node of the current node, it is added to the queue
                queue.push(queue.front()->left);
            }
            if(queue.front()->right){
                // if there is right node of the current node, it is added to the queue
                queue.push(queue.front()->right);
            }
            // then the front node is removed from the queue
            queue.pop();
            --size;
        }
        std::cout << std::endl;
    }
}