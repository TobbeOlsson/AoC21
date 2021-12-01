#include "readInput.h"
#include <fstream>
#include <string>
#include <iostream>

std::vector<int> fileLinesToVector(std::string file_path){
    std::vector<int> input;
    std::ifstream in(file_path);
    
    if (!in){
        std::cout << "Could not find input file: " << file_path << "\n";
        exit(0);
    }
    
    std::string line;
    while(std::getline(in, line)){
        input.push_back(std::stoi(line));
    }

    in.close();
    return input;
}