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
    std::cout << "drawing\n";
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

void foldPaper(std::vector<std::pair<int, int>>& dots, std::vector<std::pair<char, int>>& fold_queue){
    int fold_line = fold_queue.back().second;
    int newx = 0; int newy = 0;
    if(fold_queue.back().first == 'x'){
        for(int i = 0; i < dots.size(); i++){
            if(dots[i].first > fold_line){ //move dot left of fold line
                newx = (fold_line * 2) - dots[i].first;
                dots.push_back(std::make_pair(newx, dots[i].second));
                std::cout << "xxxx\n"; 
            }
        }

    } else if (fold_queue.back().first == 'y'){
        std::cout << "yyyy\n";
        for(int i = 0; i < dots.size(); i++){
            if(dots[i].second > fold_line){ //move dots above of fold line
                newy = (fold_line * 2) - dots[i].second;
                dots.push_back(std::make_pair(dots[i].first, newy));
            }
        }
    }
    std::cout << "after\n"; 
    fold_queue.pop_back();
}

int countDots(std::vector<std::pair<int, int>> dots){
    int dot = 0;
    bool matrix[11][15] = { false };
    for (std::pair<int, int> p : dots){
        matrix[p.first][p.second] = true;
    }
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 11; x++){
            if(matrix[x][y]){
                dot++;
            }
        }
    }
    return dot;
}

int main(){
    std::vector<std::pair<int, int>> dots;
    std::vector<std::pair<char, int>> fold_queue;
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
            fold_queue.insert(fold_queue.begin(), std::make_pair(fold_direction[0], std::stoi(fold_index)));
        }
    }

    //In most funcs I need to keep track of the current size of our paper
    //therefore not working with bigger input atm. Example working

    drawPaper(dots);
    foldPaper(dots, fold_queue);
    std::cout << "num of dots " << countDots(dots) << "\n";
    drawPaper(dots);
    foldPaper(dots, fold_queue);
    drawPaper(dots);
    return 0;
}
