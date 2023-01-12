#pragma once
#include "System.h"


class Menu{
    private:
    System system;
    std::string currentCommand;
    std::string commandNames[10];
    std::string commandExplanations[10];

    void loadCommands();
    void printCommands();
    void validateCommand(short& choice, std::string& keyWord, std::string& secondPart);
    void commandCases();
    
    void setCompressionMode();
    void setDecompressionMode();
    void setDebugMode();
    void setInputFile(const std::string& input);
    void setOutputFile(const std::string& output);
    void mode();
    void start();
    void files();
    
    public:
    Menu() = default;

    void run();
};