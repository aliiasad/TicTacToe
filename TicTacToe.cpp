# include "TicTacToe.h"

// costructor
TicTacToe :: TicTacToe()    {
    // allocating space
    board = new char* [3];
    for (int i = 0; i < 3; i++) {
        board[i] = new char [3];
    }

    // plotting reference numbers
    int cell = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '0' + cell++;
        }
    }

    // initializing game variables
    turn = 'X';
    gameOver = false;
}

void TicTacToe :: reset()   {
    int cell = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '0' + cell++;
        }
    }
    turn = 'X';
    gameOver = false;
}

bool TicTacToe :: checkWin() const    {
    // lock rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
    }
    // lock cols
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }
    // check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
    return false;
}

bool TicTacToe :: checkDraw() const   {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') return false;
        }
    }
    return true;
}

bool TicTacToe :: makeMove(int move) {
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;

    if (move < 1 || move > 9 || board[row][col] == 'X' || board[row][col] == 'O')   {
        return false;
    }
    else {
        board[row][col] = turn;
    }

     if (checkWin() || checkDraw()) {
        gameOver = true;
    } else {
        turn = (turn == 'X') ? 'O' : 'X';
    }
    return true;
}

// destructor
TicTacToe :: ~TicTacToe()   {
    for (int i = 0; i < 3; i++) {
        delete[] board[i];
    }
    delete[] board;
}

bool TicTacToe :: isGameOver() const {
    return gameOver;
}

char TicTacToe :: getTurn() const    {
    return turn;
}

char TicTacToe :: getCell(int row, int col) const    {
    return board[row][col];
}