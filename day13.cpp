#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <queue>

void drawPaper(std::vector<std::pair<int, int>> dots, int x_size, int y_size){
    std::cout << "Drawing....\n";
    bool matrix[100][100] = { false };
    for (std::pair<int, int> p : dots){
        if (p.first < x_size && p.second < y_size){
            matrix[p.first][p.second] = true;
        }
    }
    for(int y = 0; y < y_size; y++){
        for(int x = 0; x < x_size; x++){
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

void foldPaper(std::vector<std::pair<int, int>>& dots, std::vector<std::pair<char, int>>& fold_queue, int& x_size, int& y_size){
    int fold_line = fold_queue.back().second;
    int newx = 0; int newy = 0;
    if(fold_queue.back().first == 'x'){
        for(int i = 0; i < dots.size(); i++){
            if(dots[i].first > fold_line && dots[i].first <= x_size){ //move dot left of fold line
                newx = abs((fold_line * 2) - dots[i].first);
                dots.push_back(std::make_pair(newx, dots[i].second));
            }
        }
        x_size = x_size / 2;

    } else if (fold_queue.back().first == 'y'){
        for(int i = 0; i < dots.size(); i++){
            if(dots[i].second > fold_line && dots[i].second <= y_size){ //move dots above of fold line
                newy = abs((fold_line * 2) - dots[i].second);
                dots.push_back(std::make_pair(dots[i].first, newy));
            }
        }
        y_size = y_size / 2;
    }
    fold_queue.pop_back();
}

int countDots(std::vector<std::pair<int, int>> dots, int x_size, int y_size){
    int dot = 0;
    bool matrix[100][100] = { false };
    for (std::pair<int, int> p : dots){
        if(p.first < x_size && p.second < y_size){
            matrix[p.first][p.second] = true;
        }
    }
    for(int y = 0; y < y_size + 1; y++){
        for(int x = 0; x < x_size + 1; x++){
            if(matrix[x][y]){
                dot++;
            }
        }
    }
    return dot;
}

int main(){
    int x_size = 0, y_size = 0;
    std::vector<std::pair<int, int>> dots;
    std::vector<std::pair<char, int>> fold_queue;
    std::ifstream in("inputs/input_day13");
    std::string line;

    while (std::getline(in, line)){
        if (line.find(",") != std::string::npos) {
            std::string x_val, y_val;
            x_val = line.substr(0, line.find(','));
            y_val = line.substr(line.find(',') + 1, line.find(' '));
            dots.push_back(std::make_pair(std::stoi(x_val), std::stoi(y_val)));
            if(std::stoi(x_val) > x_size){
                x_size = std::stoi(x_val);
            }
            if(std::stoi(y_val) > y_size){
                y_size = std::stoi(y_val);
            }
        }
        if (line.find("fold") != std::string::npos) {
            std::string fold_direction, fold_index;
            fold_direction = line.substr(line.find('=') - 1, 1);
            fold_index = line.substr(line.find('=') + 1, line.length() - 2);
            fold_queue.insert(fold_queue.begin(), std::make_pair(fold_direction[0], std::stoi(fold_index)));
        }
    }

    while (!fold_queue.empty()){
        foldPaper(dots, fold_queue, x_size, y_size);
    }
    std::cout << "Dots after all folds: " << countDots(dots, x_size, y_size) << "\n";
    drawPaper(dots, x_size, y_size);
    return 0;
}
