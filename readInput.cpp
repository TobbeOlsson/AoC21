#include "readInput.h"
#include <fstream>
#include <string>
#include <iostream>
#include <utility>

std::vector<int> fileLinesToIntVector(std::string file_path){
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

std::vector<std::string> fileLinesToStringVector(std::string file_path){
    std::vector<std::string> input;
    std::ifstream in(file_path);
    
    if (!in){
        std::cout << "Could not find input file: " << file_path << "\n";
        exit(0);
    }
    
    std::string line;
    while(std::getline(in, line)){
        input.push_back(line);
    }

    in.close();
    return input;
}

std::vector<std::pair<std::string, int>> fileLinesToPairVector(std::string file_path){
    std::vector<std::pair<std::string, int>> input;
    std::ifstream in(file_path);
    std::string s;
    int i;
    
    if (!in){
        std::cout << "Could not find input file: " << file_path << "\n";
        exit(0);
    }
    
    std::string line;
    while(in >> s >> i){
        input.push_back(std::make_pair(s, i));
    }

    in.close();
    return input;
}