#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <stack>

void addAllOctoToStack(int octopus[][10], std::stack<std::pair<int, int>>& next_octo){
    for(int i = 9; i >= 0; --i){
        for(int j = 9; j >= 0; --j){
            next_octo.push(std::make_pair(j, i));
        }
    }
}

void incrementAllNodes(int octopus[][10]){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            octopus[j][i]++;
        }
    }
}

bool checkCoords(int x, int y){
    if (x < 0 || x > 9){
        return false;
    }
    
    if (y < 0 || y > 9){
        return false;
    }
    return true;
}

void setAllFlashedToZero(int octopus[][10], bool flashed[][10]){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(flashed[j][i]){
                octopus[j][i] = 0;
            }
        }
    }
}

void printOcto(int octopus[][10]){
    std::cout << "Printing octo matrix\n";
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            std::cout << octopus[j][i];
        }
        std::cout << "\n";
    }
}

bool allFlashing(int octopus[][10]){
    int sum = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            sum += octopus[j][i];
        }
    }
    if (sum == 0){
        return true;
    }
    return false;
}

int main(){
    int octopus[10][10];
    std::ifstream in("inputs/input_day11");
    std::string line;
    int line_num = 0, flashes = 0;
    while (std::getline(in, line)){
        for(int i = 0; i < line.length(); i++){
            int val = (int)line[i] - 48;
            octopus[i][line_num] = val;
        }
        line_num ++;
    }

    /* Assuming we will find synchronization before 100000 steps */
    for (int i = 0; i < 100000; i++){
        bool flashed[10][10] = { false };
        incrementAllNodes(octopus);
        std::stack<std::pair<int, int>> next_octo;
        addAllOctoToStack(octopus, next_octo);

        while(!next_octo.empty()){
            int x = next_octo.top().first;
            int y = next_octo.top().second;
            if(octopus[x][y] > 9){
                if(!flashed[x][y]){
                    flashed[x][y] = true;
                    flashes++;

                    if (checkCoords(x, y - 1)){
                        octopus[x][y - 1]++;
                        next_octo.push(std::make_pair(x, y - 1));
                    }
                    if (checkCoords(x, y + 1)){
                        octopus[x][y + 1]++;
                        next_octo.push(std::make_pair(x, y + 1));
                    }
                    if (checkCoords(x - 1, y)){
                        octopus[x - 1][y]++;
                        next_octo.push(std::make_pair(x - 1, y));
                    }
                    if (checkCoords(x + 1, y)){
                        octopus[x + 1][y]++;
                        next_octo.push(std::make_pair(x + 1, y));
                    }
                    if (checkCoords(x + 1, y + 1)){
                        octopus[x + 1][y + 1]++;
                        next_octo.push(std::make_pair(x + 1, y + 1));
                    }
                    if (checkCoords(x - 1, y - 1)){
                        octopus[x - 1][y - 1]++;
                        next_octo.push(std::make_pair(x - 1, y - 1));
                    }
                    if (checkCoords(x + 1, y - 1)){
                        octopus[x + 1][y - 1]++;
                        next_octo.push(std::make_pair(x + 1, y - 1));
                    }
                    if (checkCoords(x - 1, y + 1)){
                        octopus[x - 1][y + 1]++;
                        next_octo.push(std::make_pair(x - 1, y + 1));
                    }
                } else {
                    next_octo.pop();
                }
            } else {

                next_octo.pop();
            }
        }
        //printOcto(octopus);
        setAllFlashedToZero(octopus, flashed);

        if(i == 99){
            std::cout << "Number of flashes at " << i + 1 << " steps: " << flashes << "\n";
        }

        if(allFlashing(octopus)){
            std::cout << "Found sync at: " << i + 1 << "\n";
            break;
        }
    }
    return 0;
}