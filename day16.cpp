#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>

std::string hexTobin(char c)
{
    switch(c)
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
}

int getPacketVersion(std::string binstring, int& bin_read_pos){

}

int getPacketTypeID(std::string binstring, int& bin_read_pos){
    
}

int getLengthTypeID(std::string binstring, int& bin_read_pos){
    
}

int getSubpacketLength(std::string binstring, int& bin_read_pos){
    
}

int getValue(std::string binstring, int& bin_read_pos){
    
}

//note, initial plan is to use funcs above to get values and move read_pos when I do
int main(){
    std::ifstream in("inputs/input_ex16");
    std::string line, binstring;
    int bin_read_pos;
    while (std::getline(in, line)){
        std::cout << line << "\n";
        for (int i = 0; i < line.length(); i++){
            binstring.append(hexTobin(line[i]));
        }
        std::cout << binstring << "\n";
    }


    return 0;
}
