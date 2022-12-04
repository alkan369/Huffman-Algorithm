#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include "HTree.hpp"

class Comparator{
    public:
    bool operator()(const HTree& firstTree, const HTree& secondTree){
        return firstTree.getCnt() > secondTree.getCnt();
    }
};

int main(){

    std::string s = "ABRACADABRA";
    std::unordered_map<char, size_t> occurences;
    for(auto elem : s)
        ++occurences[elem];
    for(auto elem : occurences)
        std::cout << elem.first << " " << elem.second << std::endl;
    std::cout << std::endl;
    std::priority_queue<HTree, std::vector<HTree>, Comparator> queue;
    for(auto elem : occurences)
        queue.push(HTree(elem.first, elem.second));

    while(!queue.empty() && queue.size() >= 2){
        HTree first(queue.top());
        // first.print();
        // std::cout << std::endl;
        queue.pop();
        HTree second(queue.top());
        // second.print();
        // std::cout << std::endl;
        // HTree(first,second).print();
        // std::cout << queue.size() << std::endl;
        queue.push(HTree(first, second));
        queue.pop();
    }
    queue.top().print();
    // while(!queue.empty()){
    //     queue.top().print();
    //     std::cout << std::endl;
    //     std::cout << std::endl;
    //     queue.pop();
    // }

    std::cout << "THE END" << std::endl;
    return 0;
}