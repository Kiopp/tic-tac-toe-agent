#include <stdio.h>
#include <stdbool.h>
#include "agent.h"

// Constants for board size and player symbols
#define BOARD_SIZE 3
#define EMPTY_CELL ' '
#define MAX_MOVES 9

// Global game board
State board;

bool valid_move(State state, Move move) {
    // Check for out-of-bounds input
    if (move.row < 0 || move.row >= BOARD_SIZE || move.col < 0 || move.col >= BOARD_SIZE) {
        printf("Invalid move. Row and column must be between 1 and %d.\n", BOARD_SIZE);
        return false;
    }
    
    // Check if the cell is already occupied
    if (state.board[move.row][move.col] != EMPTY_CELL) {
        printf("Invalid move. That cell is already taken.\n");
        return false;
    }

    return true;
}

/**
 * @brief Initializes the game board by setting all cells to EMPTY_CELL.
 */
void initialize_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board.board[i][j] = EMPTY_CELL;
        }
    }
}

/**
 * @brief Prints the current state of the game board to the console.
 */
void print_state(State state) {
    printf("\n  1 2 3\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c", state.board[i][j]);
            if (j < BOARD_SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < BOARD_SIZE - 1) {
            printf("  -----\n");
        }
    }
    printf("\n");
}

/**
 * @brief Main function to run the Tic-Tac-Toe game loop.
 */
int main() {
    Player current_player = { HUMAN_SYMBOL };
    int row, col;
    bool game_over = false;

    printf("Welcome to Tic-Tac-Toe!\n");

    initialize_board();

    while (!game_over) {
        if (current_player.player_symbol == AGENT_SYMBOL){
            // AGENT MOVE
            printf("Agent's turn...\n");
            Move agent_move = get_agent_move(board);

            if (valid_move(board, agent_move) == true){
                // Make the move
                board.board[agent_move.row][agent_move.col] = AGENT_SYMBOL;
            } 

        } else {
            // HUMAN MOVE
            print_state(board);
            printf("Human's turn. Enter row and column (e.g., 1 2): ");

            // Input validation loop
            int result = scanf("%d %d", &row, &col);

            // Check for non-numeric input (e.g., pressing enter without input)
            if (result != 2) {
                printf("Invalid input. Please enter two numbers for row and column.\n");
                // Clear input buffer to prevent infinite loop
                while (getchar() != '\n'); 
                continue;
            }

            // Adjust to 0-based indexing
            row--; 
            col--;
            Move human_move = { row, col };

            if (valid_move(board, human_move) == true){
                // Make the move
                board.board[row][col] = HUMAN_SYMBOL;
            } else {
                continue;
            }
        }

        // Check for win
        if (check_win(board, current_player)) {
            print_state(board);
            printf("🎉 **Player %c wins!** Congratulations! 🎉\n", current_player.player_symbol);
            game_over = true;
        } 
        // Check for draw
        else if (check_draw(board)) {
            print_state(board);
            printf("🤝 **It's a draw!** Game over. 🤝\n");
            game_over = true;
        } 
        // Switch player
        else {
        current_player.player_symbol = (current_player.player_symbol == HUMAN_SYMBOL) ? AGENT_SYMBOL : HUMAN_SYMBOL;
        }
    }

    return 0;
}