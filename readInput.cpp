#include "readInput.h"
#include <fstream>
#include <string>

std::vector<int> fileLinesToVector(std::string file_name){
    std::vector<int> input;
    std::ifstream in(file_name);
    
    if (!in){
        //print error and exit?
    }
    
    std::string line;
    while(std::getline(in, line)){
        input.push_back(std::stoi(line));
    }

    in.close();
    return input;
}