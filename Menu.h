#pragma once
#include "System.h"


class Menu{
    private:
    System system;
    std::string currentCommand;
    std::string inputFileName;
    std::string outputFileName;
    std::string commandNames[9];
    std::string commandExplanations[9];

    void loadCommands();
    void printCommands();
    void validateCommand(short& choice, std::string& keyWord, std::string& secondPart);
    void commandCases();
    
    void setCompressionMode();
    void setDecompressionMode();
    // input file
    // output file
    // start
    // files
    // help 
    // exit
    
    public:
    Menu() = default;


    void start();
};