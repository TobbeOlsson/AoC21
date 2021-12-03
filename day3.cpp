#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>

int main(){
    std::vector<std::string> binary;
    std::string gamma_rate;
    std::string epsilon_rate;
    binary = fileLinesToStringVector(std::string("inputs/input_day3"));
    
    int zeroes = 0, ones = 0;
    for(int i = 0; i < binary[0].length(); i++){
        for (int j = 0; j < binary.size(); j++){
            switch (binary[i][j])
            {
            case '0':  zeroes++;  break;
            case '1':  ones++;  break;
            default:  break;
            }
        }
        if(zeroes > ones){
            gamma_rate.push_back('0');
            epsilon_rate.push_back('1');
        } else if(zeroes < ones) {
            gamma_rate.push_back('1');
            epsilon_rate.push_back('0');
        } else {
            //no most common bit, maybe never happens?
        }


        zeroes = 0;
        ones = 0;
    }
    
    return 0;
}
