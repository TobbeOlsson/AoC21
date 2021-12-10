#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

int main(){
    std::string start_chars = "([{<";
    std::string end_chars = ")]}>";
    std::ifstream in("inputs/input_day10");
    std::string line;
    int score = 0;
    std::vector<long long> autocomplete_points;
    
    while (std::getline(in, line)){
        std::vector<char> next_end_char;

        for(int i = 0; i < line.length(); i++){
            if(start_chars.find(line[i]) != std::string::npos){
                switch (line[i]){
                    case '(':
                        next_end_char.push_back(')');
                        break;
                    case '[':
                        next_end_char.push_back(']');
                        break;
                    case '{':
                        next_end_char.push_back('}');
                        break;
                    case '<':
                        next_end_char.push_back('>');
                        break;
                    default:
                        break;
                }
            } else if (end_chars.find(line[i]) != std::string::npos){
                if(next_end_char.back() == line[i]){
                    next_end_char.pop_back();
                } else { //line corrupt
                    switch (line[i]){
                        case ')':
                            score += 3;
                            break;
                        case ']':
                            score += 57;
                            break;
                        case '}':
                            score += 1197;
                            break;
                        case '>':
                            score += 25137;
                            break;
                        default:
                            break;
                    }
                    break; 
                }
            } 

            if (i == line.length() - 1){
                long long tmp_score = 0;
                while (next_end_char.size() > 0){
                    tmp_score = tmp_score * 5;

                    switch (next_end_char.back()){
                        case ')':
                            tmp_score += 1;
                            break;
                        case ']':
                            tmp_score += 2;
                            break;
                        case '}':
                            tmp_score += 3;
                            break;
                        case '>':
                            tmp_score += 4;
                            break;
                        default:
                            break;
                        }
                    next_end_char.pop_back();
                }
                autocomplete_points.push_back(tmp_score);
            }
        }
    }
    std::sort(autocomplete_points.begin(), autocomplete_points.end());
    auto auto_points = autocomplete_points[autocomplete_points.size() / 2]; 
    std::cout << "Points first task: " << score << "\n";
    std::cout << "Points second task: " << auto_points << "\n";

    return 0;
}
