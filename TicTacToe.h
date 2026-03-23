#ifndef TICTACTOE_H
#define TICTACTOE_H

class TicTacToe {
    private:
        char** board;
        char turn;
        bool gameOver;
    public:
        TicTacToe();
        ~TicTacToe();

        void reset();
        bool makeMove(int); // modifies the object by making move on grid
        bool checkWin() const;
        bool checkDraw() const;

        // to read gamestate by graphics
        bool isGameOver() const;
        char getTurn() const;
        char getCell(int, int) const;
};

#endif