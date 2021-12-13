#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <queue>

void drawPaper(std::vector<std::pair<int, int>> dots){
    //should not be static size 15, should be biggest x, 11 biggest y?
    bool matrix[11][15] = { false };
    for (std::pair<int, int> p : dots){
        matrix[p.first][p.second] = true;
    }
    for(int y = 0; y < 15; y++){
        for(int x = 0; x < 11; x++){
            if(matrix[x][y]){
                std::cout << "# ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void foldPaper(std::vector<std::pair<int, int>>& dots, std::queue<std::pair<char, int>>& fold_queue){
    int fold_line = fold_queue.front().second;
    if(fold_queue.front().first == 'x'){
        for(std::pair<int, int> p : dots){
            if(p.first > fold_line){ //move dot left of fold line
                p.first = (p.first / 2 )- 1;
            }
        }

    } else if (fold_queue.front().first == 'y'){
        for(std::pair<int, int> p : dots){
            if(p.second > fold_line){ //move dot left of fold line
                p.second = (p.second / 2 )- 1;
            }
        }
    }
    fold_queue.pop();
}

int countDots(std::vector<std::pair<int, int>> dots){
    return 0;
}

int main(){
    std::vector<std::pair<int, int>> dots;
    std::queue<std::pair<char, int>> fold_queue;
    std::ifstream in("inputs/input_ex13");
    std::string line;

    while (std::getline(in, line)){
        if (line.find(",") != std::string::npos) {
            std::string x_val, y_val;
            x_val = line.substr(0, line.find(','));
            y_val = line.substr(line.find(',') + 1, line.find(' '));
            dots.push_back(std::make_pair(std::stoi(x_val), std::stoi(y_val)));
        }
        if (line.find("fold") != std::string::npos) {
            std::string fold_direction, fold_index;
            fold_direction = line.substr(line.find('=') - 1, 1);
            fold_index = line.substr(line.find('=') + 1, line.length() - 2);
            fold_queue.push(std::make_pair(fold_direction[0], std::stoi(fold_index)));
        }
    }
    drawPaper(dots);
    foldPaper(dots, fold_queue);
    drawPaper(dots);
    return 0;
}
