#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>

int main(){
    int size_x = 10, size_y = 10;
    int matrix[size_x][size_y];
    std::ifstream in("inputs/input_ex15");
    std::string line;
    int line_num = 0;
    while (std::getline(in, line)){
        for(int i = 0; i < line.length(); i++){
            int val = (int)line[i] - 48;
            matrix[i][line_num] = val;
            std::cout << matrix[i][line_num] << " ";
        }
        std::cout << "\n";
        line_num++;
    }

    









    return 0;
}
