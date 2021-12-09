#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>

bool isLowPoint(int x, int y, int heightmap[][102]){
    if ((heightmap[x][y] >= heightmap[x - 1][y]) || (heightmap[x][y] >= heightmap[x + 1][y]) ||
        (heightmap[x][y] >= heightmap[x][y - 1]) || (heightmap[x][y] >= heightmap[x][y + 1])){
            return false;
    }
    return true;
}

void populateNines (bool visited[][102], int heightmap[][102]){
    for (int i = 0; i < 102; i++){
        for (int j = 0; j < 102; j++) {
            if (heightmap[j][i] == 9){
                visited[j][i] = true;
            }
        }
    }
}

int basinSize(int x, int y, int heightmap[][102]){
    bool visited[102][102] = { false };
    populateNines(visited, heightmap);
    std::vector<std::pair<int, int>> unvisited;
    int size = 0;
    unvisited.push_back(std::make_pair(x, y));
    int x_val = 0, y_val = 0;

    while (unvisited.size() > 0){
        x_val = unvisited.back().first;
        y_val = unvisited.back().second;
        if (!visited[x_val][y_val]){
            visited[x_val][y_val] = true;
            unvisited.push_back(std::make_pair(x_val + 1, y_val));
            unvisited.push_back(std::make_pair(x_val - 1, y_val));
            unvisited.push_back(std::make_pair(x_val, y_val + 1));
            unvisited.push_back(std::make_pair(x_val, y_val - 1));
            size++;
        } else {
            unvisited.pop_back();
        }
    }
    return size;
}

void initMatrixWithValue(int val, int heightmap[][102]){
     for (int i = 0; i < 102; i++){
        for (int j = 0; j < 102; j++) {
            heightmap[j][i] = val;
        }
    }
}

int main(){
    int heightmap[102][102];
    initMatrixWithValue(9, heightmap);
    std::vector<int> basins;
    std::ifstream in("inputs/input_day9");
    std::string line;
    int line_num = 0, total_risk = 0, total_basin;
    while (std::getline(in, line)){
        for(int i = 0; i < line.length(); i++){
            int val = (int)line[i] - 48;
            heightmap[i+1][line_num + 1] = val;
        }
        line_num++;
    }

    int basin_size = 0;
    for (int i = 1; i < 101; i++){
        for (int j = 1; j < 101; j++) {
            if(isLowPoint(j, i, heightmap)){
                total_risk += heightmap[j][i] + 1;
                basin_size = basinSize(j, i, heightmap);
                basins.push_back(basin_size);
            }
        }
    }

    std::sort(basins.begin(), basins.end());
    total_basin = basins.back();
    for(int i = 0; i < 2; i++){
        basins.pop_back();
        total_basin = total_basin * basins.back();
    }
    std::cout << "Basin score: " << total_basin << "\n";
    std::cout << "Total risk is: " << total_risk << "\n";
    return 0;
}
