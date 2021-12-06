#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>

int main(){
    std::ifstream in("inputs/input_day6");
    std::string line;
    long long fish[10] = {};
    while (std::getline(in, line)){
        std::istringstream ss(line);
        std::string s;
        while (std::getline(ss, s, ',')){
            switch (std::stoi(s)){
            case 0: fish[0]++; break;
            case 1: fish[1]++; break;
            case 2: fish[2]++; break;
            case 3: fish[3]++; break;
            case 4: fish[4]++; break;
            case 5: fish[5]++; break;
            case 6: fish[6]++; break;
            case 7: fish[7]++; break;
            case 8: fish[8]++; break;
            default: break;
            }
        }
    }

    for (size_t days = 0; days < 256; days++){
        long long spawns = fish[0];
        for (int j = 1; j < 9; j++){
            fish[j - 1] = fish[j];
        }
        fish[6] += spawns;
        fish[8] = spawns;
    }
    std::cout << "Fish: " << std::accumulate(std::begin(fish), std::end(fish), 0ull, std::plus<long long>()) << "\n";
    return 0;
}
