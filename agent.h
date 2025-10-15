#include <stdbool.h>

#define EMPTY_CELL ' '
#define AGENT_SYMBOL 'O'
#define HUMAN_SYMBOL 'X'

typedef struct {
    int row;
    int col;
} Move;

typedef struct {
    char board[3][3];
} State;

typedef struct {
    char player_symbol;
} Player;

Move get_agent_move(State state);

int get_actions(Move actions[], State state);

State get_resulting_state(State state, Move action, Player player);

int minimax(State state, Player player);

bool check_win(State state, Player player);

bool check_draw(State state);