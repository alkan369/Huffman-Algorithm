#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include "HTree.h"
#include "Comparator.h"

int main(){

    std::string s = "ABRACADABRA";
    std::cout << s.size() << std::endl;
    // std::string s = "BCAADDDCCACACAC";
    // std::string s = "AIIIIPSPPPPPEEIISIIIIPPPPPPPIEEIETETASETAETAEA\nEAAEEEEEAAA";

    std::unordered_map<char, size_t> occurences;

    for(auto elem : s){
        ++occurences[elem];
    }
    for(auto elem : occurences)
        std::cout << elem.first << " " << elem.second << std::endl;
    std::cout << std::endl;
    std::priority_queue<HTree, std::vector<HTree>, Comparator> queue;
    for(auto elem : occurences){
        queue.push(HTree(elem.first, elem.second));
    }

    while(!queue.empty() && queue.size() >= 2){
        HTree first(queue.top());
        queue.pop();
        HTree second(queue.top());
        queue.push(HTree(first, second));
        queue.pop();
    }

    HTree result(queue.top());
    queue.pop();
    // result.print();
    result.printByLevels();
    std::string resultString = result.getCharacterCode('A');
    std::cout << "A : " << resultString << " OCCURENCE : " <<  occurences['A'] << " BYTES : " << occurences['A'] * resultString.size() << std::endl;
    resultString = result.getCharacterCode('B');
    std::cout << "B : " << resultString << " OCCURENCE : " << occurences['B'] << " BYTES : " << occurences['B'] * resultString.size() << std::endl;
    resultString =  result.getCharacterCode('C');
    std::cout << "C : " << resultString << " OCCURENCE : " <<  occurences['C'] << " BYTES : " << occurences['C'] * resultString.size() << std::endl;
    resultString = result.getCharacterCode('D');
    std::cout << "D : " << resultString << " OCCURENCE : " << occurences['D'] << " BYTES : " << occurences['D'] * resultString.size() << std::endl;
    resultString = result.getCharacterCode('R');
    std::cout << "R : " << resultString << " OCCURENCE : " <<  occurences['R'] << " BYTES : " << occurences['R'] * resultString.size() << std::endl;
    std::cout << "THE END" << std::endl;
    return 0;
}