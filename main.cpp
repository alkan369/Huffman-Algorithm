#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include "HTree.h"
#include "Comparator.h"
#include "System.h"
#include "Menu.h"
#include <bitset>


void func(std::fstream& file, const std::string& line){

    std::cout << "Alkan" << std::endl;
    std::cout << "is" << std::endl;
    std::cout << "the" << std::endl;
    throw std::invalid_argument("Problem");
    std::cout << "best" << std::endl;
    std::cout << "programmer" << std::endl;

}

int main(){

    // std::string s = "ABRACADABRA";
    // std::cout << s.size() << std::endl;
    // // std::string s = "BCAADDDCCACACAC";
    // // std::string s = "AIIIIPSPPPPPEEIISIIIIPPPPPPPIEEIETETASETAETAEA\nEAAEEEEEAAA";

    // std::unordered_map<char, size_t> occurences;

    // for(auto elem : s){
    //     ++occurences[elem];
    // }
    // for(auto elem : occurences)
    //     std::cout << elem.first << " " << elem.second << std::endl;
    // std::cout << std::endl;
    // std::priority_queue<HTree, std::vector<HTree>, Comparator> queue;
    // for(auto elem : occurences){
    //     queue.push(HTree(elem.first, elem.second));
    // }

    // while(!queue.empty() && queue.size() >= 2){
    //     HTree first(queue.top());
    //     queue.pop();
    //     HTree second(queue.top());
    //     queue.push(HTree(first, second));
    //     queue.pop();
    // }

    // HTree result(queue.top());
    // queue.pop();
    // // result.print();
    // result.printByLevels();
    // std::string resultString = result.getCharacterCode('A');
    // std::cout << "A : " << resultString << " OCCURENCE : " <<  occurences['A'] << " BYTES : " << occurences['A'] * resultString.size() << std::endl;
    // resultString = result.getCharacterCode('B');
    // std::cout << "B : " << resultString << " OCCURENCE : " << occurences['B'] << " BYTES : " << occurences['B'] * resultString.size() << std::endl;
    // resultString =  result.getCharacterCode('C');
    // std::cout << "C : " << resultString << " OCCURENCE : " <<  occurences['C'] << " BYTES : " << occurences['C'] * resultString.size() << std::endl;
    // resultString = result.getCharacterCode('D');
    // std::cout << "D : " << resultString << " OCCURENCE : " << occurences['D'] << " BYTES : " << occurences['D'] * resultString.size() << std::endl;
    // resultString = result.getCharacterCode('R');
    // std::cout << "R : " << resultString << " OCCURENCE : " <<  occurences['R'] << " BYTES : " << occurences['R'] * resultString.size() << std::endl;
    // std::cout << "P : " << result.getCharacterCode('P') << std::endl;
    // std::cout << "Q : " << result.getCharacterCode('Q') << std::endl;
    // resultString = "";
    // for(auto elem : s)
    //     resultString.append(result.getCharacterCode(elem));
    // std::cout << "ENCODED : " << resultString << std::endl;
    // System system;
    // std::cout << "ENCODED : " << system.getEncodedMessage(s) << std::endl;
    // std::cout << std::boolalpha << resultString.compare(system.getEncodedMessage(s)) << std::endl;
    // std::cout << resultString.size() << " " << system.getEncodedMessage(s).size() << std::endl;
    // std::cout << system.getEncodedMessage(s) << std::endl;
    // std::unordered_map<std::string, char> keyTable;
    // for(auto elem : occurences){
    //     keyTable[result.getCharacterCode(elem.first)] = elem.first;
    // }
    // std::cout << "KEY TABLE : " << std::endl;
    // for(auto elem : keyTable)
    //     std::cout << elem.second << " = " << elem.first << std::endl;

    // keyTable = system.getKeyTable();
    // std::cout << "NEW KEY TABLE : " << std::endl;
    // for(auto elem : keyTable)
    //     std::cout << elem.second << " = " << elem.first << std::endl;
    // std::cout << "RESULT : " << std::endl;
    // std::cout << system.getDecodedMessage(system.getEncodedMessage(s), keyTable) << std::endl;
    // Menu menu;
    // menu.run();
    // std::cout << "THE END" << std::endl;
    // std::ofstream file("try");
    // std::string compressed = "01011001110011110101100";
    // std::string binString = "";
    // int size = 0;
    // for(char c : compressed){
    //     if(size == 8){
    //         size = 0;
    //         file << std::bitset<8>(binString).to_ulong();
    //         file << ' ';
    //         binString.clear();
    //     }
    //     binString.push_back(c);
    //     ++size;
    // }
    // // file << 5;
    // if(!binString.empty()){
    //     file << std::bitset<8>(binString).to_ulong();
    // }
    // file.close();
    // std::bitset<8> bits(std::stoi("23"));
    // std::cout << bits << std::endl;
    // std::cout << bits.to_string() << std::endl;
    // std::cout << bits.to_ulong() << std::endl;
    Menu menu;
    menu.run();
    // std::string l = "AMinaKoyem";
    // std::cout << l.substr(0,4) << std::endl;
    // std::cout << l.substr(4,4) << std::endl;
    // std::cout << l.substr(8,4) << std::endl;
    // std::cout << l.substr(12,4) << std::endl;
    // try{
    //     std::fstream file("test-file");
    //     func(file, "String");
    // }
    // catch(std::invalid_argument& e){
    //     std::cout << e.what() << std::endl;
    //     std::cout << "Invalid argument has ocurred" << std::endl;
    // }
    // catch(...){
    //     std::cout << "Any exception" << std::endl;
    //     std::cout << "the" << std::endl;
    //     std::cout << "greatest" << std::endl;
    //     std::cout << "programmer" << std::endl;
    // }
    std::cout << "END" << std::endl;
    return 0;
}