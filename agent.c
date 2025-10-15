#include "agent.h"
#include <stdio.h>

Move get_agent_move(State state){
    // Initialize
    Player self = { AGENT_SYMBOL };
    Player human = { HUMAN_SYMBOL };
    Move next_actions[9];
    int action_utilities[9];
    int action_count = get_actions(next_actions, state);
    int max_utility = -2;
    int max_utility_index = 0;

    // Calculate utility values for each possible action
    for (int i = 0; i < action_count; i++) {
        action_utilities[i] = minimax(get_resulting_state(state, next_actions[i], self), human);

        // Keep track of highest utility found
        if (action_utilities[i] > max_utility) {
            max_utility = action_utilities[i];
            max_utility_index = i;
        }

        // Log
        //printf("Move %d %d utility: %d\n", next_actions[i].row+1, next_actions[i].col+1, action_utilities[i]);
    }

    // Make a greedy decision with best utility
    return next_actions[max_utility_index];
}

int minimax(State state, Player player){
    Player agent = { AGENT_SYMBOL };
    Player human = { HUMAN_SYMBOL };
    // Base case
    if (check_win(state, agent) == true) {
        return 1;
    }
    else if (check_win(state, human) == true) {
        return -1;
    }
    else if (check_draw(state) == true) {
        return 0;
    }

    if (player.player_symbol == AGENT_SYMBOL) {
        // MAXIMIZE UTILITY
        int max_utility = -2;
        Move next_actions[9];
        int next_action_utilities[9];
        int next_action_count = get_actions(next_actions, state);
        for (int i = 0; i < next_action_count; i++) {
            next_action_utilities[i] = minimax(get_resulting_state(state, next_actions[i], player), human);

            if (next_action_utilities[i] > max_utility) max_utility = next_action_utilities[i];
        }
        return max_utility;
    } else if (player.player_symbol == HUMAN_SYMBOL){
        // MINIMIZE UTILITY
        int min_utility = 2;
        Move next_actions[9];
        int next_action_utilities[9];
        int next_action_count = get_actions(next_actions, state);
        for (int i = 0; i < next_action_count; i++) {
            next_action_utilities[i] = minimax(get_resulting_state(state, next_actions[i], player), agent);

            if (next_action_utilities[i] < min_utility) min_utility = next_action_utilities[i];
        }
        return min_utility;
    }

    return -999;
}

State get_resulting_state(State state, Move action, Player player) {
    // Copy previous state
    State result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.board[i][j] = state.board[i][j];
        }
    }

    // Simple validation
    if (result.board[action.row][action.col] == EMPTY_CELL) {
        result.board[action.row][action.col] = player.player_symbol;
    } else {
        printf("FATAL ERROR! Attempting to generate a state from faulty move!\n");
    }

    return result;
}

int get_actions(Move actions[], State state) {
    int move_count = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state.board[i][j] == EMPTY_CELL) {
                // Store the 0-indexed row and column
                actions[move_count].row = i;
                actions[move_count].col = j;
                move_count++;
            }
        }
    }
    
    return move_count;
}

bool check_win(State state, Player player) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        // Check row i
        if (state.board[i][0] == player.player_symbol && state.board[i][1] == player.player_symbol && state.board[i][2] == player.player_symbol) {
            return true;
        }
        // Check column i
        if (state.board[0][i] == player.player_symbol && state.board[1][i] == player.player_symbol && state.board[2][i] == player.player_symbol) {
            return true;
        }
    }

    // Check main diagonal (top-left to bottom-right)
    if (state.board[0][0] == player.player_symbol && state.board[1][1] == player.player_symbol && state.board[2][2] == player.player_symbol) {
        return true;
    }

    // Check anti-diagonal (top-right to bottom-left)
    if (state.board[0][2] == player.player_symbol && state.board[1][1] == player.player_symbol && state.board[2][0] == player.player_symbol) {
        return true;
    }

    return false;
}

bool check_draw(State state) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state.board[i][j] == EMPTY_CELL) {
                return false; // Found an empty cell
            }
        }
    }
    return true; // All cells are filled
}
