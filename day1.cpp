#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>

int main(){
    int depth_increases = 0;
    std::vector<int> depth_measurement;
    depth_measurement = fileLinesToVector(std::string("inputs/input_day1"));

    int prev_prev_depth = 0, prev_depth = 0;
    int prev_window = 0, curr_window = 0;

    /*Assuming in both if-statements that depth will never reach 0 (again?),
    because submarines live below the surface */
    for(int depth : depth_measurement){
        if(!(prev_prev_depth == 0)){
            curr_window = prev_prev_depth + prev_depth + depth;
            
            if(prev_window < curr_window && !(prev_window == 0)){
                depth_increases++;
            }
        }
        prev_window = curr_window;
        prev_prev_depth = prev_depth;
        prev_depth = depth;
    }

    std::cout << "Number of depth increases: " << depth_increases << "\n";
    
    return 0;
}
