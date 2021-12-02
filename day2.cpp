#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>

int main(){
    std::vector<std::pair<std::string, int>> planned_course;
    planned_course = fileLinesToPairVector(std::string("inputs/input_day2"));
    int answer = 0;
    int x = 0, y = 0, aim = 0;

    for(std::pair<std::string, int> p : planned_course){
        if (p.first == "forward"){
            x = x + p.second;
            y = y + (p.second * aim);

        } else if (p.first == "up"){
            aim = aim - p.second; 

        } else if (p.first == "down"){
            aim = aim + p.second;

        } else {
            std::cout << "unexpected input\n";
            exit(0);
        }
    }
    answer = x * y;
    std::cout << "Answer is: " << answer << "\n";
    return 0;
}
