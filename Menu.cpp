#include "Menu.h"

// private

void Menu::loadCommands(){
    // loading  the supported commands and their explanations
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
    // printing the commands
    std::cout << "Supported commands : " << std::endl;
    for(short i = 0; i < 10; i++)
        std::cout << commandNames[i] << commandExplanations[i] << std::endl;
}

void Menu::validateCommand(short& choice, std::string& keyWord, std::string& secondPart){
    // bool variable in case we find space
    bool foundSpace = false;
    // iterating through the entered command
    for(char c : currentCommand){
        // if space is found the bool variable is changed to true
        if(c == ' '){
            foundSpace = true;
            continue;
        }
        if(!foundSpace){
            // if space is not found, then, it means that the key word is being constructed
            keyWord.push_back(c);
        }
        else{
            // if space is found, then the second part of the command is being constructed
            secondPart.push_back(c);
        }
    }
    for(short i = 0; i < 10; i++){
        // iterating through the commands
        if(keyWord == commandNames[i]){
            // changing the value of the variable to 'i' if the command is found(is valid)
            choice = i;
        }
    }
}

void Menu::commandCases(){
    // default value for choice is -1
    short choice = -1;
    std::string keyWord;
    std::string secondPart;
    validateCommand(choice, keyWord, secondPart);
    // entering in switch case to determine which method to call
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
            try{
                // throws exception if the second part is empty
                // and this command is called
                setInputFile(secondPart);
            }
            catch(std::invalid_argument& e){
                std::cout << e.what() << std::endl;
                return;
            }
            break;
        case 4:
            try{
                // throws exception if the second part is empty
                // and this command is called
                setOutputFile(secondPart);
            }
            catch(std::invalid_argument& e){
                std::cout << e.what() << std::endl;
                return;
            }
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
            // if this case is entered, it means that the entered command is invalid
            std::cout << "Invalid command" << std::endl;
            break;
    }
}

// setting the working modes
void Menu::setCompressionMode(){
    system.setMode(0); // to compression
}

void Menu::setDecompressionMode(){
    system.setMode(1); // to decompression
}

void Menu::setDebugMode(){
    system.setMode(2); // to debug
}

// setting the file names that the program will work with
void Menu::setInputFile(const std::string& input){
    system.setInputFileName(input); // setting input file name
}

void Menu::setOutputFile(const std::string& output){
    system.setOutputFileName(output); // setting output file name
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
            // default value is -1, it means that no mode has been set
            std::cout << "Mode : no mode set" << std::endl;
            break;
    }
}

void Menu::start(){
    try{
        // throws exception if no work mode has been set(if workmode is -1)
        system.start();
    }
    catch(std::invalid_argument& e){
        std::cout << e.what() << std::endl;
    }
}

// prints the files the program currently works with
void Menu::files(){
    std::cout << "Input file : " << system.getInputFileName() << std::endl;
    std::cout << "Output file : " << system.getOutputFileName() << std::endl;
}

// public

void Menu::run(){
    loadCommands(); // the commands are loaded
    printCommands(); // and printed one time
    do{
        std::cout << "Enter command : ";
        std::getline(std::cin, currentCommand); // entering a command
        commandCases(); // checking what to do with the program after the input
    }while(currentCommand != "exit"); // the program continues until "exit" is entered

}