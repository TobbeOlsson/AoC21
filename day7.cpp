#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>

int main(){
    std::ifstream in("inputs/input_day7");
    std::string line;
    /* Biggest number in input is 1924 */
    int fuel_use[1924] = {};
    
    while (std::getline(in, line)){
        std::istringstream ss(line);
        std::string s;
        while (std::getline(ss, s, ',')){
            int fuel_calc = 0, distance = 0;
            for (int i = 0; i < 1924; i++){
                distance = std::abs(std::stoi(s) - i);
                fuel_calc = distance * (distance + 1) / 2;
                fuel_use[i] += fuel_calc;
            }
        }
    }
    
    int least_fuel_index = 0;
    for (int i = 0; i < 1924; i++){
        if (fuel_use[i] <= fuel_use[least_fuel_index]) {
            least_fuel_index = i;
        }
    }
    
    std::cout << "Least fuel index: " << least_fuel_index << "\n";
    std::cout << "Fuel used: " << fuel_use[least_fuel_index] << "\n"; 
    return 0;
}