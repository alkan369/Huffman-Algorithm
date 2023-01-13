#pragma once
#include "System.h"


class Menu{
    private:
    System system;
    std::string currentCommand;
    std::string commandNames[10]; // static array of strings for
    std::string commandExplanations[10]; // the supported 10 commands with their explanations

    void loadCommands(); // loads the commandNames array and the commandExplanations array
    void printCommands(); // print the supported commands with their explanations
    // validating the entered command
    void validateCommand(short& choice, std::string& keyWord, std::string& secondPart);
    // and entering the command cases to determine which command to call
    void commandCases();
    
    // setting the current working mode
    void setCompressionMode();
    void setDecompressionMode();
    void setDebugMode();
    // setting the current files to work with
    void setInputFile(const std::string& input);
    void setOutputFile(const std::string& output);
    // getting the current working mode
    void mode();
    // starting the program
    void start();
    // getting the current files the problem works with
    void files();
    
    public:
    Menu() = default;

    // starts the whole program
    void run();
};