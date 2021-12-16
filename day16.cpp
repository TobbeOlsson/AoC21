#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>

int main(){
    std::ifstream in("inputs/input_ex16");
    std::string line;
    while (std::getline(in, line)){
        std::cout << line << "\n";


    }


    return 0;
}
