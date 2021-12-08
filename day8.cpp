#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <algorithm>

struct compare {
    inline bool operator()(const std::string& first,
            const std::string& second) const
    {
        return first.length() < second.length();
    }
};

int overlapping (std::string& s1, std::string& s2){
    int overlap = 0;
    for (size_t i = 0; i < s2.length(); i++){
        if (s1.find(s2[i]) != std::string::npos){
            overlap++;
        }
    }
    return overlap;
}

int main(){
    std::ifstream in("inputs/input_day8");
    std::string line;
    compare c;
    int final_score = 0;
    std::string detucted_signals[10];

    while (std::getline(in, line)){
        std::istringstream ss(line);
        std::vector<std::string> row_of_input;
        std::vector<std::string> row_of_output;
        std::string s, score;
        std::string detucted_signals[10];
        bool input_end = false;

        while (std::getline(ss, s, ' ')){
            if (s == "|"){
                input_end = true;
                continue;
            }
            if (!input_end){
                row_of_input.push_back(s);
            } else {
                row_of_output.push_back(s);
            }
        }
        sort(row_of_input.begin(), row_of_input.end(), c);

        /* Deduct from input */
        for(std::string signal : row_of_input){
            std::sort(signal.begin(), signal.end());
            /* 2, 3 or 5 */
            if(signal.length() == 5){
                if(overlapping(detucted_signals[7], signal) == 3){ // 3 overlaps in 3 the places with '7'
                    detucted_signals[3] = signal;
                } else if (overlapping(detucted_signals[4], signal) == 3){ // 5 overlaps in 3 places with '4'
                    detucted_signals[5] = signal;
                } else {                                                // else it's a 2
                    detucted_signals[2] = signal;
                }
            } else if (signal.length() == 6){ // 0, 6 or 9
                if (overlapping(detucted_signals[4], signal) == 4){ //9 overlaps 4 with '4'
                    detucted_signals[9] = signal;
                } else if (overlapping(detucted_signals[1], signal) == 2) { //0 overlaps 2 with '1'
                    detucted_signals[0] = signal;
                } else {                                            // else it's a 6
                    detucted_signals[6] = signal;
                }
            } else {  // 1, 4, 7 or 8
                switch (signal.length()){
                case 2: detucted_signals[1] = signal; break;
                case 3: detucted_signals[7] = signal; break;
                case 4: detucted_signals[4] = signal; break;
                case 7: detucted_signals[8] = signal; break;
                default: break;
                }
            }
        }

        /* Compare outputs with deducted numbers to get score */
        for (std::string out_sign : row_of_output) {
            std::sort(out_sign.begin(), out_sign.end());
            for (int i = 0; i < 10; i++){
                if(out_sign == detucted_signals[i]){
                    score.push_back(i + '0');
                }
            }
        }

        final_score += std::stoi(score);
    }
    
    std::cout << "Sum of all output numbers " << final_score << "\n";
    return 0;
}
