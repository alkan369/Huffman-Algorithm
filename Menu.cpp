#include "Menu.h"

void Menu::loadCommands(){
    commandNames[0] = "c";
    commandNames[1] = "d";
    commandNames[2] = "i";
    commandNames[3] = "o";
    commandNames[4] = "m";
    commandNames[5] = "start";
    commandNames[6] = "files";
    commandNames[7] = "help";
    commandNames[8] = "exit";
    commandExplanations[0] = "[ompress] - parameter showing that the program will work in compression mode";
    commandExplanations[1] = "[ecompress] - parameter showing that the program will work in decompression mode";
    commandExplanations[2] = " <filename> - parameter showing the input file name the program will work with";
    commandExplanations[3] = " <filename> - parameter showing the output file name the program will work with";
    commandExplanations[4] = "[ode] - prints the current working mode of the program";
    commandExplanations[5] = " - starts the program with current mode and input and output files";
    commandExplanations[6] = " - prints the input file name and output file the that the program is working with";
    commandExplanations[7] = " - prints again all commands";
    commandExplanations[8] = " - ends the programs";
}

void Menu::printCommands(){
    std::cout << "Supported commands : " << std::endl;
    for(short i = 0; i < 9; i++)
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
    for(short i = 0; i < 9; i++){
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
    switch (choice)
    {
    case 0:
        std::cout << "Mode : Compression mode" << std::endl;
        setCompressionMode();
        break;
    case 1:
        std::cout << "Mode : Decompression mode" << std::endl;
        setDecompressionMode();
        break;
    default:
        break;
    }
}

void Menu::setCompressionMode(){
    system.setMode(0);
}

void Menu::setDecompressionMode(){
    system.setMode(1);
}

void Menu::start(){
    do{
        loadCommands();
        printCommands();
        std::getline(std::cin, currentCommand);

        //std::cin.ignore()?
    }while(currentCommand != "exit");

}