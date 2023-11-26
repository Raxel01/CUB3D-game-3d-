
#include "./HEADER/Parsing.h"
#define ROWS 14
#define COLS 40

// Function to perform depth-first search (DFS)
void dfs(char map[ROWS][COLS], int row, int col) {
    // Check if the current position is within the map boundaries
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        // If the current position is an open space, mark it as visited
        if (map[row][col] == '0') {
            map[row][col] = '2';  // Mark visited
            // Recursively explore neighboring positions
            dfs(map, row + 1, col);
            dfs(map, row - 1, col);
            dfs(map, row, col + 1);
            dfs(map, row, col - 1);
        }
    }
}

// Function to check if the map is enclosed by walls
int is_map_enclosed(char map[ROWS][COLS]) {
    // Start DFS from the top and bottom boundaries
    for (int col = 0; col < COLS; col++) {
        dfs(map, 0, col);
        dfs(map, ROWS - 1, col);
    }

    // Start DFS from the left and right boundaries
    for (int row = 0; row < ROWS; row++) {
        dfs(map, row, 0);
        dfs(map, row, COLS - 1);
    }

    // Check if there are any unvisited open spaces inside the boundary
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (map[row][col] == '0') {
                return 0;  // Map is not completely surrounded
            }
        }
    }

    return 1;  // Map is completely surrounded
}

int main() {
    char game_map[ROWS][COLS] = {
        "1111111111111111111111111",
        "1000000000110000000000001",
        "1011000001110000000000001",
        "1001000000000000000000001",
        "1111111110110000011100001",
        "100000000011000001110111111111111",
        "111101111111110111000000100011",
        "111101111111110111010100100011",
        "110000001101010111000000100011",
        "100000000000000011000000100011",
        "1000000000000000110101001000111",
        "110000011101010111110111101110111",
        "11110111111101011110111011101101",
        "11111111111111111111111111111111"
    };

    // Check if the map is enclosed by walls
    int result = is_map_enclosed(game_map);
    
    // Display the result
    if (result) {
        printf("The map is enclosed by walls.\n");
    } else {
        printf("The map is not enclosed by walls.\n");
    }

    return 0;
}