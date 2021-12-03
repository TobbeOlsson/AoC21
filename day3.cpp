#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>

int most_common(std::vector<std::string> vect, int position){
    int most_common = 0, zeroes = 0, ones = 0;
    for (int j = 0; j < vect.size(); j++){
        switch (vect[j][position]){
            case '0':  zeroes++;  ; break;
            case '1':  ones++;  ; break;
            default:  break;
        }
    }
    if(zeroes > ones){
        most_common = 0;
    } else if(zeroes < ones){
        most_common = 1;
    } else if (zeroes == ones){
        most_common = -1;
    }
    return most_common;
}

int least_common(std::vector<std::string> vect, int position){
    int least_common = 0, zeroes = 0, ones = 0;
    for (int j = 0; j < vect.size(); j++){
        switch (vect[j][position]){
            case '0':  zeroes++;  ; break;
            case '1':  ones++;  ; break;
            default:  break;
        }
    }
    if(zeroes > ones){
        least_common = 1;
    } else if(zeroes < ones){
        least_common = 0;
    } else if (zeroes == ones){
        least_common = -1;
    }
    return least_common;
}

int main(){
    std::vector<std::string> binary;
    std::string gamma_rate, epsilon_rate;
    std::string co2_rate, oxy_rate;
    binary = fileLinesToStringVector(std::string("inputs/input_day3"));
    std::vector<std::string> oxygen = binary;
    std::vector<std::string> co2 = binary;
    bool oxy_rate_found = false, co2_rate_found = false;
    
    int zeroes = 0, ones = 0, oxy_common = 0, co2_common = 0;
    for(int i = 0; i < binary[0].size(); i++){
        for (int j = 0; j < binary.size(); j++){
            switch (binary[j][i]){
                case '0':  zeroes++;  ; break;
                case '1':  ones++;  ; break;
                default:  break;
            }
        }
        if(zeroes > ones){
            gamma_rate.push_back('0');
            epsilon_rate.push_back('1');
            oxy_common = 0;
            co2_common = 1;
        } else if(zeroes < ones){
            gamma_rate.push_back('1');
            epsilon_rate.push_back('0');
            oxy_common = 1;
            co2_common = 0;
        } else if (zeroes == ones){
            oxy_common = 1;
            co2_common = 0;
        }
        if (!oxy_rate_found){
            int cnt = 0;
            int com = most_common(oxygen,i);
            for (std::vector<std::string>::iterator it = oxygen.begin(); it != oxygen.end(); cnt++){
                if(oxygen.size() == 1){
                    oxy_rate = *it;
                    oxy_rate_found = true;
                    break;
                } else if(com == -1){
                    if ((*it)[i] - '0' == 1){
                        oxy_rate = *it;
                        it++;
                    } else {
                        it = oxygen.erase(it);
                    }
                    oxy_rate = *it;
                    it++;
                } else if (!((*it)[i] - '0' == com)){
                    it = oxygen.erase(it);
                } else {
                    oxy_rate = *it;
                    it++;                   
                }
            }
        }
        if (!co2_rate_found){
            int cnt = 0;
            int com = least_common(co2,i);
            for (std::vector<std::string>::iterator it = co2.begin(); it != co2.end(); cnt++){
                if(co2.size() == 1){
                    co2_rate = *it;
                    co2_rate_found = true;
                    break;
                } else if(com == -1){
                    if ((*it)[i] - '0' == 0){
                        oxy_rate = *it;
                        it++;
                    } else {
                        it = co2.erase(it);
                    }
                } else if (!((*it)[i] - '0' == com)){
                    it = co2.erase(it);
                } else {
                    co2_rate = *it;
                    it++;                  
                }
            }
        }
        zeroes = 0;
        ones = 0;
    }
    std::cout << "Gamma rate: " << std::stoi(gamma_rate, nullptr, 2) << "   Epsilon rate: " << std::stoi(epsilon_rate, nullptr, 2) <<"\n";
    std::cout << "Answer: " << std::stoi(gamma_rate, nullptr, 2) * std::stoi(epsilon_rate, nullptr, 2) << "\n";
    std::cout << "Oxygen generator rating: " << oxy_rate << "\n";
    std::cout << "Oxygen generator rating: " << std::stoi(oxy_rate, nullptr, 2) << "\n";
    std::cout << "CO2 scrubber rating: " << std::stoi(co2_rate, nullptr, 2) << "\n";
    std::cout << "Answer: " << std::stoi(oxy_rate, nullptr, 2) * std::stoi(co2_rate, nullptr, 2) << "\n";

    return 0;
}
