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
    std::cout << "Should be zero: " << sea_floor[4][6] << "\n";
    while(std::getline(in, line)){
        std::string line_after_arrow = line.substr(line.find('>') + 1, line.length() - 2);
        x1 = std::stoi(line.substr(0, line.find(',')));
        y1 = std::stoi(line.substr(line.find(',') + 1, line.find('-') - 1));
        x2 = std::stoi(line_after_arrow.substr(0, line_after_arrow.find(',')));
        y2 = std::stoi(line_after_arrow.substr(line_after_arrow.find(',') + 1, line_after_arrow.length() - 2));

        //std::cout << x2 << " ";
        //read one row, add 1 to all coordinates in matrix.

        if (x1 == x2){
            if(y1 > y2){
                for(int i = 0; i <= (y1 - y2); i++){
                    sea_floor[y1 + i][x1]++;
                    //std::cout << "sea_floor " << x1 << " " << y2 + i  << " " << sea_floor[x1][y2 + i] << "\n";
                }
            } else if (y2 > y1) {
                for(int i = 0; i <= (y2 - y1); i++){
                    sea_floor[y1 + i][x1]++;
                    //std::cout << "sea_floor " << x1 << " " << y1 + i << " " << sea_floor[x1][y1 + i] << "\n";
                }
            }
        } else if (y1 == y2){
            if(x1 > x2){
                for(int i = 0; i <= (x1 - x2); i++){
                    sea_floor[y1][x2 + i]++;
                    //std::cout << "sea_floor " << y1 << " " << x2 + i << " " << sea_floor[x2 + i][y1] << "\n";
                }
            } else if (x2 > x1) {
                for(int i = 0; i <= (x2 - x1); i++){
                    sea_floor[y1][x1 + i]++;
                    //std::cout << "sea_floor " << y1 << " " << x1 + i << " " << sea_floor[x1 + i][y1] << "\n";
                }
            }
        }
    }
    std::cout << "Finished with reading inputs\n";
    // go throw all matrix and check values > 1
    int score = 0;
    for (int i = 0; i < 1000; i++){
        for (int j = 0; j < 1000; j++){
            if (sea_floor[i][j] > 1) {
                std::cout << sea_floor[i][j];
                std::cout << "Score 2 location " << i << " " << j << "\n";
                score++;
            }
        std::cout << "\n";
        }
    }
    std::cout << "Score: " << score << "\n";
}
