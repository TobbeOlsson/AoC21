#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

void mark_board(int num, int board[][5]){
    for (size_t i = 0; i < 500; i++){
        for (size_t j = 0; j < 5; j++){
            if (board[i][j] == num){
                board[i][j] += 1000;
            }
        }      
    }
    return;
}

/* Returns first winning board or -1 */
int find_winner(int board[][5]){
    int board_index = 0;
    bool winner_found = false;
    while (!winner_found && board_index < 500){
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

/* Returns number of winning boards and updates number_of_wins[] for all winning boards */ 
int num_of_winners(int board[][5], int number_of_wins[]){
    int board_index = 0;
    int winners_found = 0;
    while (board_index < 500){
        for (size_t i = 0; i <= 4; i++){
            if (board[board_index + i][0] + board[board_index + i][1] + 
            board[board_index + i][2] + board[board_index + i][3] + board[board_index + i][4] > 5000) {
                winners_found++;
                number_of_wins[board_index / 5]++;
                break;
            }
            if (board[board_index + 0][i] + board[board_index + 1][i] + 
            board[board_index + 2][i] + board[board_index + 3][i] + board[board_index + 4][i] > 5000){
                winners_found++;
                number_of_wins[board_index / 5]++;
                break;
            } 
        }
        board_index += 5;
    }
    return winners_found;
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

int main(){
    std::vector<int> drawn_nums;
    std::ifstream in("inputs/input_day4");
    int board[500][5];
    std::string line;
    int i = 0, winner = -1, score = 0;
    while(std::getline(in, line)){
        std::istringstream ss(line);
        if (drawn_nums.size() == 0){
            std::string s;
            while (std::getline(ss, s, ',')){
                drawn_nums.push_back(std::stoi(s));
            }
        } else {  //read boards
            std::string s;
            while (in >> board[i][0] >> board[i][1] >> board[i][2] >> board[i][3] >> board[i][4]){
                i++;
            }     
        }
    }

    int number_of_wins[100] = { };
    int winning_boards = 0;
    for(int num : drawn_nums){
        mark_board(num, board);
        winning_boards = num_of_winners(board, number_of_wins);
        /* Find index of winning board in number_of_wins[] */
        if (winning_boards >= 100){
            int winner_index = 0;
            for (size_t i = 0; i < 100; i++){
                if (number_of_wins[i] <= number_of_wins[winner_index]) {
                    winner_index = i;
                }
            }
            std::cout << "Last winner: " << winner_index + 1 << "\n";
            score = calculate_score(winner_index + 1, num, board);
            break;
        }     
    }
    std::cout << "Score: " << score << "\n";
    return 0;
}
