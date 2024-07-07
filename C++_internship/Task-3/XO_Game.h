//
// Created by Sahar Mohamed on 06/07/2024.
//

#ifndef XO_GAME_H
#define XO_GAME_H

#include <iostream>

using namespace std;

class Player {
public:
    string name;
    char symbol;
    int pNum;

    Player(){}
    Player(string n, char sym, int pn) {
        name = n;
        symbol = sym;
        pNum = pn;
    }
};

class Board {
public:
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    Player p1;
    Player p2;

    Board(){}
    Board(Player player1, Player player2) {
        p1 = player1;
        p2 = player2;
    }
    void displayInstructionBoard();
    void displayBoard();
    void updateBoard(int x, int y, char symbol);
    int winner();
    bool isFull();
};

class AI_player : public Player {
public:
    int row = -1 , column = -1;
    AI_player(string n, char sym, int pn): Player(n, sym, pn){}
    int minimax(Board board, int nMoves, bool isMax);
    void getMove(Board board);
};

class XO_GameManager {
public:
    void run();
};

#endif
