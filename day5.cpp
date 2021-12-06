#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

int main(){
    int sea_floor[1000][1000] = {};
    std::ifstream in("inputs/input_day5");
    std::string line;
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    while(std::getline(in, line)){
        std::string line_after_arrow = line.substr(line.find('>') + 1, line.length() - 2);
        x1 = std::stoi(line.substr(0, line.find(',')));
        y1 = std::stoi(line.substr(line.find(',') + 1, line.find('-') - 1));
        x2 = std::stoi(line_after_arrow.substr(0, line_after_arrow.find(',')));
        y2 = std::stoi(line_after_arrow.substr(line_after_arrow.find(',') + 1, line_after_arrow.length() - 2));

        if (x1 == x2){
            if(y1 > y2){
                for(int i = 0; i <= (y1 - y2); i++){
                    sea_floor[x1][y2 + i]++;
                }
            } else if (y2 > y1) {
                for(int i = 0; i <= (y2 - y1); i++){
                    sea_floor[x1][y1 + i]++;
                }
            }
        } else if (y1 == y2){
            if(x1 > x2){
                for(int i = 0; i <= (x1 - x2); i++){
                    sea_floor[x2 + i][y1]++;
                }
            } else if (x2 > x1) {
                for(int i = 0; i <= (x2 - x1); i++){
                    sea_floor[x1 + i][y1]++;
                }
            }
        } else {
            if(x1 == y1 && x2 == y2){
                if(x1 > x2){
                    for(int i = 0; i <= (x1 - x2); i++){
                        sea_floor[x1 - i][y1 - i]++;
                    }
                } else {
                    for(int i = 0; i <= (x2 - x1); i++){
                        sea_floor[x1 + i][y1 + i]++;
                    }
                }
            } else if(x1 > x2){
                if(y1 > y2){
                    for(int i = 0; i <= (x1 - x2); i++){
                        sea_floor[x1 - i][y1 - i]++;
                    }
                } else {
                    for(int i = 0; i <= (x1 - x2); i++){
                        sea_floor[x1 - i][y1 + i]++;
                    }
                }
            } else if(x2 > x1){
                if(y2 > y1){
                    for(int i = 0; i <= (x2 - x1); i++){
                        sea_floor[x1 + i][y1 + i]++;
                    }
                } else {
                    for(int i = 0; i <= (x2 - x1); i++){
                        sea_floor[x1 + i][y1 - i]++;
                    }
                }
            }
        }
    }

    int score = 0;
    for (int i = 0; i < 1000; i++){
        for (int j = 0; j < 1000; j++){
            if (sea_floor[i][j] > 1) {
                score++;
            }
        }
    }
    std::cout << "Score: " << score << "\n";
}
