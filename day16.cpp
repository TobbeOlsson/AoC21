#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>

std::string hexToBin(char c)
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
    std::string string_ver = binstring.substr(bin_read_pos, 3);
    bin_read_pos += 3;
    return std::stoi(string_ver, nullptr, 2);
}

int getPacketTypeID(std::string binstring, int& bin_read_pos){
    std::string string_type = binstring.substr(bin_read_pos, 3);
    bin_read_pos += 3;
    return std::stoi(string_type, nullptr, 2);
    
}

int getLengthTypeID(std::string binstring, int& bin_read_pos){
    std::string bit_str = binstring.substr(bin_read_pos, 1);
    bin_read_pos += 1;
    return std::stoi(bit_str, nullptr, 2);
}

int getSubpacketLength(std::string binstring, int& bin_read_pos){
    std::string bit_str = binstring.substr(bin_read_pos, 15);
    bin_read_pos += 15;
    return std::stoi(bit_str, nullptr, 2);
}

int getStartValueBit(std::string binstring, int& bin_read_pos){
    std::string bit_str = binstring.substr(bin_read_pos, 1);
    bin_read_pos += 1;
    return std::stoi(bit_str, nullptr, 2);
}

long getValue(std::string binstring, int& bin_read_pos){
    std::string valuestr;
    while (getStartValueBit(binstring, bin_read_pos) > 0) {
        valuestr.append(binstring.substr(bin_read_pos, 4));
        bin_read_pos += 4;
    }
    valuestr.append(binstring.substr(bin_read_pos, 4));
    bin_read_pos += 4;
    return std::stol(valuestr, nullptr, 2);
}

int getNumberOfSubpackets(std::string binstring, int& bin_read_pos){
   std::string bit_str = binstring.substr(bin_read_pos, 11);
    bin_read_pos += 11;
    return std::stoi(bit_str, nullptr, 2);
}

void calcNextOp(std::vector<long>& val_list, std::vector<int>& op, int num_packs){
    std::cout << "Enter calc\n";
    std::cout << "op " << op.back() << "\n";
    std::cout << "numpacks " << num_packs << "\n";
    long first_sub = 0;
    long second_sub = 0;
    std::vector<long> temp_vals;
    int val = 0;
    switch (op.back()){
        case 0:
            if(num_packs == 1){
                break;
            }
            for(int i = 0; i < num_packs; i++){
                val += val_list.back();
                val_list.pop_back();
            }
            val_list.push_back(val);
            break;
        case 1:
            if(num_packs == 1){
                break;
            }
            val = 1;
            for(int i = 0; i < num_packs; i++){
                val = val * val_list.back();
                val_list.pop_back();
            }
            val_list.push_back(val);
            break;
        case 2:
            for(int i = 0; i < num_packs; i++){
                temp_vals.push_back(val_list.back());
                val_list.pop_back();
            }
            std::sort(temp_vals.begin(), temp_vals.end());
            val_list.push_back(temp_vals[0]);
            break;
        case 3:
            for(int i = 0; i < num_packs; i++){
                temp_vals.push_back(val_list.back());
                val_list.pop_back();
            }
            std::sort(temp_vals.begin(), temp_vals.end());
            val_list.push_back(temp_vals[temp_vals.size()-1]);
            break;
        case 5:
            second_sub = val_list.back();
            val_list.pop_back();
            first_sub = val_list.back();
            val_list.pop_back();
            if(first_sub > second_sub){
                val_list.push_back(1);
            } else {
                val_list.push_back(0);
            }
            break;
        case 6:
            second_sub = val_list.back();
            val_list.pop_back();
            first_sub = val_list.back();
            val_list.pop_back();
            std::cout << "secind " << second_sub << "\n"; 
            std::cout << "first " << first_sub << "\n"; 
            if(second_sub > first_sub){
                val_list.push_back(1);
            } else {
                val_list.push_back(0);
            }
            break;
        case 7:
            second_sub = val_list.back();
            val_list.pop_back();
            first_sub = val_list.back();
            val_list.pop_back();
             std::cout << "secind " << second_sub << "\n"; 
            std::cout << "first " << first_sub << "\n"; 
            if(second_sub == first_sub){
                val_list.push_back(1);
            } else {
                val_list.push_back(0);
            }
            break;
        default:
            break;
    }
    op.pop_back();
}



//note, initial plan is to use funcs above to get values and move read_pos when I do
int main(){
    std::ifstream in("inputs/input_day16");
    std::string line, binstring;
    int bin_read_pos = 0;
    while (std::getline(in, line)){
        std::cout << line << "\n";
        for (int i = 0; i < line.length(); i++){
            binstring.append(hexToBin(line[i]));
        }
        std::cout << binstring << "\n";
    }

    std::string expr_string;
    int versionSum = 0;
    int packetVersion = 0, typeID = 0;
    long value = 0, lengthTypeID = 0;
    int subpacketLength = 0, sub_start = 0;
    int numberOfSubPacks = 0, packsCounter = 0;
    bool subPacksCount = false;
    int lastOpID = 0;
    std::vector<long> val_list;
    std::vector<int> op;
    std::vector<int> subPacksLen_list;
    std::vector<int> numberOfSubPack_list;
    subPacksLen_list.push_back(100000); //dummy val
    numberOfSubPack_list.push_back(100000); //dummy val

    while(bin_read_pos < binstring.length()){
        packsCounter++;
        packetVersion = getPacketVersion(binstring, bin_read_pos);
        versionSum += packetVersion;
        typeID = getPacketTypeID(binstring, bin_read_pos);

        if(typeID == 4){ //litteral value
            value = getValue(binstring, bin_read_pos);
            val_list.push_back(value);
        } else { //operator
            op.push_back(typeID);
            lengthTypeID = getLengthTypeID(binstring, bin_read_pos);
            if(lengthTypeID == 0){
                subpacketLength = getSubpacketLength(binstring, bin_read_pos);
                subPacksLen_list.push_back(subpacketLength + bin_read_pos);
                //sub_start = bin_read_pos;
                //packsCounter = 0;
            } else {
                numberOfSubPacks = getNumberOfSubpackets(binstring, bin_read_pos);
                numberOfSubPack_list.push_back(numberOfSubPacks);
                subPacksCount = true;
                packsCounter = 0;
            }
        }
        if(bin_read_pos == subPacksLen_list.back()){
            std::cout << "calc sublen\n";
            calcNextOp(val_list, op, packsCounter);
            //packsCounter = 0;
            subPacksLen_list.pop_back();

        }
        if(subPacksCount && (packsCounter >= numberOfSubPack_list.back())){
            std::cout << "calc num of packs\n";
            calcNextOp(val_list, op, packsCounter);
            subPacksCount = true;
            packsCounter = 0;
            numberOfSubPack_list.pop_back();
        }



        if( bin_read_pos - sub_start >= subpacketLength &&  ((binstring.length() - bin_read_pos) <= 10)){
            break;
        }
         if( subPacksCount && (packsCounter >= numberOfSubPacks) &&  ((binstring.length() - bin_read_pos) <= 10)){
            break;
        }
        if((binstring.length() - bin_read_pos) <= 3){
            calcNextOp(val_list, op, packsCounter);
            break;
        }
    }


    std::cout << "Packet version sum: " << versionSum << "\n";

    std::cout << "pack len list size" << subPacksLen_list.size() << "\n";
    std::cout << "pack count list size" << numberOfSubPack_list.size() << "\n";
    std::cout << "Val list size " << val_list.size() << "\n";
    std::cout << "op list size " << op.size() << "\n";
    std::cout << "Result: " << val_list[0] << "\n";

    return 0;
}
