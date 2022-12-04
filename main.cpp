#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <set>
#include "HTree.hpp"

class Comparator{
    public:
    bool operator()(const HTree& firstTree, const HTree& secondTree){
        return firstTree.getCnt() > secondTree.getCnt();
    }
    // bool operator()(const std::pair<char, size_t>& firstObject, const std::pair<char, size_t>& secondObject){
    //     return firstObject.second > secondObject.second;
    // }
};

int main(){

    std::string s = "ABRACADABRA";
    std::cout << s.size() << std::endl;
    // std::string s = "BCAADDDCCACACAC";
    // std::string s = "AIIIIPSPPPPPEEIISIIIIPPPPPPPIEEIETETASETAETAEA\nEAAEEEEEAAA";

    std::unordered_map<char, size_t> occurences;
    // std::set<char> occurencesTwo;

    for(auto elem : s){
        ++occurences[elem];
        // if(occurencesTwo.find() != occurencesTwo.end()){

        // }
    }
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
    // queue.top().print();
    // while(!queue.empty()){
    //     queue.top().print();
    //     std::cout << std::endl;
    //     std::cout << std::endl;
    //     queue.pop();
    // }

    HTree result(queue.top());
    queue.pop();
    // result.print();
    result.printByLevels();
    std::string resultString = result.getCharacterCode('A');
    std::cout << "A : " << resultString << " " <<  occurences['A'] * resultString.size() << std::endl;
    resultString = result.getCharacterCode('B');
    std::cout << "B : " << resultString << " " << occurences['B'] * resultString.size() << std::endl;
    resultString =  result.getCharacterCode('C');
    std::cout << "C : " << resultString << " " <<  occurences['C'] * resultString.size() << std::endl;
    resultString = result.getCharacterCode('D');
    std::cout << "D : " << resultString << " " << occurences['D'] * resultString.size() << std::endl;
    resultString = result.getCharacterCode('R');
    std::cout << "R : " << resultString << " " <<  occurences['R'] * resultString.size() << std::endl;
    std::cout << "THE END" << std::endl;
    return 0;
}