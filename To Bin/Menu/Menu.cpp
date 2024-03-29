#include "Menu.h"

void Menu::loadCommands(){
    commandNames[0] = "c";
    commandNames[1] = "d";
    commandNames[2] = "debug";
    commandNames[3] = "i";
    commandNames[4] = "o";
    commandNames[5] = "m";
    commandNames[6] = "start";
    commandNames[7] = "files";
    commandNames[8] = "help";
    commandNames[9] = "exit";
    commandExplanations[0] = "[ompress] - parameter showing that the program will work in compression mode";
    commandExplanations[1] = "[ecompress] - parameter showing that the program will work in decompression mode";
    commandExplanations[2] = " - parameter showing that the program will work in debug mode(prints the result)";
    commandExplanations[3] = " <filename> - parameter showing the input file name the program will work with";
    commandExplanations[4] = " <filename> - parameter showing the output file name the program will work with";
    commandExplanations[5] = "[ode] - prints the current working mode of the program";
    commandExplanations[6] = " - starts the program with current mode and input and output files";
    commandExplanations[7] = " - prints the input file name and output file the that the program is working with";
    commandExplanations[8] = " - prints again all commands";
    commandExplanations[9] = " - ends the program";
}

void Menu::printCommands(){
    std::cout << "Supported commands : " << std::endl;
    for(short i = 0; i < 10; i++)
        std::cout << commandNames[i] << commandExplanations[i] << std::endl;
}

void Menu::validateCommand(short& choice, std::string& keyWord, std::string& secondPart){
    bool foundSpace = false;
    for(char c : currentCommand){
        if(c == ' '){
            foundSpace = true;
            continue;
        }
        if(!foundSpace){
            keyWord.push_back(c);
        }
        else{
            secondPart.push_back(c);
        }
    }
    for(short i = 0; i < 10; i++){
        if(keyWord == commandNames[i]){
            choice = i;
        }
    }
}

void Menu::commandCases(){
    short choice = -1;
    std::string keyWord;
    std::string secondPart;
    validateCommand(choice, keyWord, secondPart);
    switch (choice){
        case 0:
            std::cout << "Mode : Compression mode" << std::endl;
            setCompressionMode();
            break;
        case 1:
            std::cout << "Mode : Decompression mode" << std::endl;
            setDecompressionMode();
            break;
        case 2:
            std::cout << "Mode : Debug mode" << std::endl;
            setDebugMode();
            break;
        case 3:
            setInputFile(secondPart);
            break;
        case 4:
            setOutputFile(secondPart);
            break;
        case 5:
            mode();
            break;
        case 6:
            start();
            break;
        case 7:
            files();
            break;
        case 8:
            printCommands();
            break;
        case 9:
            std::cout << "Exitting" << std::endl;
            break;
        default:
            // exception ??? no
            std::cout << "Invalid command" << std::endl;
            break;
    }
}

void Menu::setCompressionMode(){
    system.setMode(0);
}

void Menu::setDecompressionMode(){
    system.setMode(1);
}

void Menu::setDebugMode(){
    system.setMode(2);
}

void Menu::setInputFile(const std::string& input){
    // try catch? no
    system.setInputFileName(input);
}

void Menu::setOutputFile(const std::string& output){
    // try catch? no
    system.setOutputFileName(output);
}

void Menu::mode(){
    switch (system.getMode()){
        case 0:
            std::cout << "Mode : Compression mode" << std::endl;
            break;
        case 1:
            std::cout << "Mode : Decompression mode" << std::endl;
            break;
        case 2:
            std::cout << "Mode : Debug mode" << std::endl;
            break;
        default:
            // exception ? no
            std::cout << "Mode : no mode set" << std::endl;
            break;
    }
}

void Menu::start(){
    system.start();
}

void Menu::files(){
    std::cout << "Input file : " << system.getInputFileName() << std::endl;
    std::cout << "Output file : " << system.getOutputFileName() << std::endl;
}

void Menu::run(){
    loadCommands();
    printCommands();
    do{
        std::cout << "Enter command : ";
        std::getline(std::cin, currentCommand);
        commandCases();
        // std::cin.ignore();
    }while(currentCommand != "exit");

}