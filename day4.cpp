#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

void mark_board(int num, int board[][5]){
    for (size_t i = 0; i < 15; i++){
        for (size_t j = 0; j < 5; j++){
            if (board[i][j] == num){
                board[i][j] += 1000;
            }
        }      
    }
    return;
}

int find_winner(int board[][5]){
    int board_index = 0;
    bool winner_found = false;
    while (!winner_found && board_index < 495){
        for (size_t i = 0; i < 4; i++){
            if (board[board_index + i][0] + board[board_index + i][1] + 
            board[board_index + i][2] + board[board_index + i][3] + board[board_index + i][4] > 5000) {
                winner_found = true;
            }
            if (board[board_index + 0][i] + board[board_index + 1][i] + 
            board[board_index + 2][i] + board[board_index + 3][i] + board[board_index + 4][i] > 5000){
                winner_found = true;
            } 
        }
        board_index += 5;
    }
    if (winner_found){
        return board_index / 5;
    }
    return -1;
}

int calculate_score(int winner, int last_drawn, int board[][5]){
   int board_index = winner * 5 - 5;
   int sum = 0;
   for (size_t i = 0; i < 5; i++){
       for (size_t j = 0; j < 5; j++) {
           if(board[i + board_index][j] < 1000){
               sum += board[i + board_index][j];
           }
       }
    }
    return sum * last_drawn;
}

int find_last_winner(int board[][5], int (&won)[3]){
    int board_index = 0;
    int last_won = -1;
    int num_winners = 0;
    bool winner_found = false;
    while (!winner_found && board_index < 15){
        for (size_t i = 0; i < 4; i++){
            if (board[board_index + i][0] + board[board_index + i][1] + 
            board[board_index + i][2] + board[board_index + i][3] + board[board_index + i][4] > 5000) {
                std::cout << "WINNER WINNER: " << board_index /5 << "\n";
                std::cout << "SCORE SCORE: " << calculate_score(2, 24, board) << "\n";
                won[board_index / 5] = 1;
            }
            if (board[board_index + 0][i] + board[board_index + 1][i] + 
            board[board_index + 2][i] + board[board_index + 3][i] + board[board_index + 4][i] > 5000){
                std::cout << "WINNER WINNER2: " << board_index /5 << "\n";
                std::cout << "SCORE SCORE2: " << calculate_score(2, 24, board) << "\n";
                won[board_index / 5] = 1;
            } 
        }
        board_index += 5;
    }
    for(int i = 0; i < 3; i++){
        if(won[i] == 1){
            num_winners++;
            last_won = i;
        } else{
            //do nothing
        }
    }
    std::cout << "Num of winners: " << num_winners;
    if (num_winners > 2){
        return last_won;
    }
    return last_won;
}



int main(){
    std::vector<int> drawn_nums;
    std::ifstream in("inputs/input_ex");
    std::vector<int> winners;
    int board[15][5];
    std::string line;
    int i = 0, winner = -1, score = 0;
    while(std::getline(in, line)){
        std::istringstream ss(line);
        if (drawn_nums.size() == 0){
            std::string s;
            while (std::getline(ss, s, ',')){
                drawn_nums.push_back(std::stoi(s));
            }
        } else {  //read bingo boards
            std::string s;
            while (in >> board[i][0] >> board[i][1] >> board[i][2] >> board[i][3] >> board[i][4]){
                i++;
            }     
        }
    }

    int won[3] = { };
    for(int num : drawn_nums){
        mark_board(num, board);
        std::cout << "Marked " << num << "\n"; 
        if(winners.size() < 3){
            winner = find_last_winner(board, won);
            if (winner != -1){
                std::cout << "Winner: " << winner << "\n";
                //winners.push_back(winner);
                score = calculate_score(winner, num, board);
                std::cout << "Score: " << score << "\n";
            }
            //if(winners.size() == 100){
                //score = calculate_score(winner, num, board);
                //break;
            //}
        }
        // winner = find_last_winner(board, winners);
        // if(winner != -1){
        //     score = calculate_score(winner, num, board);
        //     break;
        // }
        
    }
    std::cout << "Winner is board: " << winner << "\n";
    std::cout << "Score: " << score << "\n";
    return 0;
}
