#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <map>

int main(){
    std::map<std::string, char> insertion_table;
    std::map<std::string, long> number_of_pairs;
    std::map<char, long> letter_count;
    std::string start_string, current_string;
    std::ifstream in("inputs/input_day14");
    std::string line;
    int line_num = 0;
    while (std::getline(in, line)){
        if(line_num == 0){
            start_string = line;
        } else if (line_num > 1){
            std::string letter_pair, insert;
            letter_pair = line.substr(0, 2);
            insert = line.substr(line.find('>') + 2, 1);
            insertion_table.insert(std::make_pair(letter_pair, insert[0]));
            number_of_pairs.insert(std::make_pair(letter_pair, 0));
            if(!(letter_count.find(letter_pair[0]) != letter_count.end())){
                letter_count.insert(std::make_pair(letter_pair[0], 0));
                std::cout << "ADDED LETTER " << letter_pair[0] << "\n";
            }
            if(!(letter_count.find(letter_pair[1]) != letter_count.end())){
                letter_count.insert(std::make_pair(letter_pair[1], 0));
                std::cout << "ADDED LETTER " << letter_pair[1] << "\n";
            }
        }
        line_num++;
    }

    for(int i = 0; i < start_string.length() - 1; i++){
        std::string char_pair;
        char_pair = start_string.substr(i + 0 , 2);
        letter_count.at(char_pair[0])++;
        letter_count.at(char_pair[1])++;
        number_of_pairs.at(char_pair)++;
    }

    //iterate over days
    for(int days = 0; days < 40; days++){
        std::map<std::string, long> current_day;
        for(std::pair<std::string, long> p : number_of_pairs){
            std::string first_new, second_new;
            first_new = p.first[0];
            first_new += insertion_table.at(p.first);

            second_new = insertion_table.at(p.first);
            second_new += p.first[1];

            if (!(current_day.find(first_new) != current_day.end())){
                current_day.insert(std::make_pair(first_new, p.second));
            } else {
                current_day.at(first_new) += p.second;
            }

             if (!(current_day.find(second_new) != current_day.end())){
                current_day.insert(std::make_pair(second_new, p.second));
            } else {
                current_day.at(second_new) += p.second;
            }

            letter_count.at(insertion_table.at(p.first)) += p.second;
        }
        number_of_pairs = std::move(current_day);
    }

    std::vector<long> number_of_letters;
    for(std::map<char, long>::iterator it = letter_count.begin(); it != letter_count.end(); ++it){
        number_of_letters.push_back( it->second );
    }
    std::sort(number_of_letters.begin(), number_of_letters.end());
    std::cout << "Small " << number_of_letters[0] << " Big " << number_of_letters[number_of_letters.size() - 1] << "\n";
    std::cout << "Result: " << number_of_letters[number_of_letters.size() - 1] - number_of_letters[0] << "\n";
    return 0;
}
