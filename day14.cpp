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
    std::string start_string, current_string;
    std::ifstream in("inputs/input_ex14");
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
        }
        line_num++;
    }
    current_string = start_string;
    for(int days = 0; days < 20; days++){
        start_string = current_string;
        std::string this_day;
        for(int i = 0; i < start_string.length() - 1; i++){
            std::string pair;
            char insert_char;
            pair.push_back(start_string[i]); 
            pair.push_back(start_string[i + 1]);
            insert_char = insertion_table.at(pair);

            this_day.push_back(pair[0]);
            this_day.push_back(insert_char);

        }
        this_day.push_back(start_string[start_string.length() - 1]);
        current_string = std::move(this_day);

    }

    std::vector<int> letter_amounts;
    std::sort(current_string.begin(), current_string.end());
    int letter_count = 0;
    for(int i = 0; i < current_string.length() - 1; i++){
        if(current_string[i] == current_string[i + 1]){
            letter_count++;
        } else {
            letter_count++;
            letter_amounts.push_back(letter_count);
            letter_count = 0;
        }
    }
    std::sort(letter_amounts.begin(), letter_amounts.end());
    std::cout << "Small " << letter_amounts[0] << " Big " << letter_amounts[letter_amounts.size() - 1] << "\n";
    std::cout << "Result: " << letter_amounts[letter_amounts.size() - 1] - letter_amounts[0] << "\n";

}
