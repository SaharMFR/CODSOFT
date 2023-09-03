//
// Created by Sahar Mohamed on 29/08/2023.
//

#include "XO_AI.h"

//////////////////////////////////////////////////////////////////////
///                             Board                             ///
/////////////////////////////////////////////////////////////////////


void Board::displayBoard() {
    cout << "\n-------------------------------------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "|             |             |             |\n";
        cout << "|      ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << "      |      ";
        }
        cout << "\n|             |             |             |";
        cout << "\n-------------------------------------------\n";
    }

}

void Board::updateBoard(int x, int y, char symbol) {
    board[x][y] = symbol;
}

int Board::winner() {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])) {
            if (board[i][0] == p1.symbol)
                return 1;
            else if (board[i][0] == p2.symbol)
                return 2;
        }
        else if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == p1.symbol)
                return 1;
            else if (board[0][i] == p2.symbol)
                return 2;
        }
        else if ( board[1][1] != ' ' && ( board[0][0] == board[1][1] && board[1][1] == board[2][2] ) || ( board[0][2] == board[1][1] && board[1][1] == board[2][0] )) {
            if (board[1][1] == p1.symbol)
                return 1;
            else if (board[1][1] == p2.symbol)
                return 2;
        }
    }
    return 0;
}


bool Board::isFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}


//////////////////////////////////////////////////////////////////////
///                           AI_player                           ///
/////////////////////////////////////////////////////////////////////

int AI_player::minimax(Board B, int nMoves, bool AI_turn) {
    if (B.winner() == pNum)
        return 10;
    if (B.winner() && B.winner() != pNum)
        return -10;

    if (B.isFull())
        return 0;

    if (AI_turn) {
        int bestMove = -10000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (B.board[i][j] == ' ') {
                    B.updateBoard(i, j, symbol);
                    bestMove = max(bestMove, minimax(B, nMoves + 1, !AI_turn));
                    B.updateBoard(i, j, ' ');
                }
            }
        }
        return bestMove;
    } else {
        int bestMove = 10000;

        for (int i = 0; i < 3; i++) {
            for ( int j = 0; j < 3; j++) {
                if (B.board[i][j] == ' ') {
                    if (symbol == 'X')
                        B.updateBoard(i, j, 'O');
                    else
                        B.updateBoard(i, j, 'X');

                    bestMove = min(bestMove, minimax(B, nMoves + 1, !AI_turn));
                    B.updateBoard(i, j, ' ');
                }
            }
        }
        return bestMove;
    }
}

void AI_player::getMove(Board B) {
    int bestMove = -10000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (B.board[i][j] == ' ') {
                B.updateBoard(i, j, symbol);
                int moveValue = minimax(B, 0, false);
                B.updateBoard(i, j, ' ');
                if (bestMove < moveValue) {
                    row = i;
                    column = j;
                    bestMove = moveValue;
                }
            }
        }
    }
}


//////////////////////////////////////////////////////////////////////
///                          GameManager                          ///
/////////////////////////////////////////////////////////////////////


void XO_GameManager::run() {
    cout << "\n<< Welcome to Tic-Tac-Toe Game >>\n";
    int choice = 0;
    while (choice != 3) {
        cout << "\n\n 1 - One player .\n 2 - Two players .\n 3 - Quit the game .\n\nPlease , enter your choice : ";
        cin >> choice;
        if (choice == 1) {
            cout << "\nPlayer 1 starts ..\n\n";

            int pNum;
            cout << "Do you want to be player ( 1 ) or ( 2 ) ? ";
            cin >> pNum;

            string name;
            cout << "\n\nEnter your name : ";
            cin >> name;

            char symbol;
            while (true) {
                cout << "Symbol (X / O) : ";
                cin >> symbol;
                if (symbol >= 97 && symbol <= 122)
                    symbol -= 32;
                if (symbol != 'X' && symbol != 'O') {
                    cout << "\nInvalid symbol :(\nPlease , try again ..\n\n";
                } else {
                    cout << "\nYou have registered successfully ..\n\n";
                    break;
                }
            }

            Player player(name, symbol, pNum);


            int comPN;
            char comSym;

            if (symbol == 'X')
                comSym = 'O';
            else
                comSym = 'X';

            if (pNum == 1)
                comPN = 2;
            else
                comPN = 1;

            AI_player computer("Computer", comSym, comPN);


            cout << "\nYou should enter the 2 indices of the cell you want to play in separated by space ..\n\n";
            cout << "\n-------------------------------------------\n";
            for (int i = 0; i < 3; i++) {
                cout << "|             |             |             |\n";
                cout << "|  ";
                for (int j = 0; j < 3; j++) {
                    cout << "( " << i << " , " << j << " )" << "  |  ";
                }
                cout << "\n|             |             |             |";
                cout << "\n-------------------------------------------\n";
            }

            cout << "\n\nLet's start the game ..\n";

            Board myBoard(player, computer);


            if (pNum == 2) {
                computer.getMove(myBoard);
                myBoard.updateBoard(computer.row, computer.column, comSym);
            }

            myBoard.displayBoard();

            while (true) {
                int x, y;
                bool valid_indices = false;
                while (!valid_indices) {
                    cout << endl << name << " (player " << pNum << ") , enter the indices : ";
                    cin >> x >> y;
                    if (x >= 0 && x <= 2 && y >= 0 && y <= 2) {
                        if (myBoard.board[x][y] == ' ') {
                            myBoard.updateBoard(x, y, player.symbol);
//                            nEmptyCells--;
                            valid_indices = true;
                        } else {
                            cout << "\nThis cell is already taken ..\nPlease , choose another one ..\n";
                        }
                    } else {
                        cout << "\nInvalid indices :(\nEach index should be from 0 to 2 .\nPlease , try again .. \n";
                    }
                }
                myBoard.displayBoard();
                if (myBoard.winner() == pNum) {
                    cout << "\n\nCongratulations " << name << " (player " << pNum << ") !\nYou won ..\n\n";
                    break;
                }

                if (myBoard.isFull() && !myBoard.winner()) {
                    cout << "\n\nDraw !\n\n";
                    break;
                }

                computer.getMove(myBoard);
                myBoard.updateBoard(computer.row, computer.column, comSym);

                myBoard.displayBoard();
                if (myBoard.winner() == comPN) {
                    cout << "Hard luck " << name << " (player " << pNum << ") ..\nComputer won ..\n";
                    break;
                }

                if (myBoard.isFull() && !myBoard.winner()) {
                    cout << "\n\nDraw !\n\n";
                    break;
                }

            }


        } else if (choice == 2) {
            cout << "\nPlayer 1 starts ..\n\n";

            string name1;
            char symbol1;

            cout << "\nPlayer 1 ..\n\n";
            cout << "Enter your name : ";
            cin >> name1;
            while (true) {
                cout << "Symbol (X / O) : ";
                cin >> symbol1;
                if (symbol1 >= 97 && symbol1 <= 122)
                    symbol1 -= 32;
                if (symbol1 != 'X' && symbol1 != 'O') {
                    cout << "\nInvalid symbol :(\nPlease , try again ..\n\n";
                } else {
                    cout << "\nPlayer 1 has registered successfully ..\n\n";
                    break;
                }
            }

            Player player1(name1, symbol1, 1);

            string name2;
            char symbol2;
            if (symbol1 == 'X')
                symbol2 = 'O';
            else
                symbol2 = 'X';

            cout << "\nPlayer 2 ..\n\n";
            cout << "Enter your name : ";
            cin >> name2;
            cout << "Your symbol is " << symbol2 << endl;
            cout << "\nPlayer 2 has registered successfully ..\n\n";


            Player player2(name2, symbol2, 2);


            cout << "\nEach player should enter the 2 indices of the cell he want to play in separated by space ..\n\n";
            cout << "\n-------------------------------------------\n";
            for (int i = 0; i < 3; i++) {
                cout << "|             |             |             |\n";
                cout << "|  ";
                for (int j = 0; j < 3; j++) {
                    cout << "( " << i << " , " << j << " )" << "  |  ";
                }
                cout << "\n|             |             |             |";
                cout << "\n-------------------------------------------\n";
            }

            cout << "\n\nLet's start the game ..\n";

            Board myBoard(player1, player2);

            myBoard.displayBoard();

            while (true) {
                int x , y;
                bool valid_indices = false;
                while (!valid_indices) {
                    cout << endl << name1 << " (player 1) , enter the indices : ";
                    cin >> x >> y;
                    if (x >= 0 && x <= 2 && y >= 0 && y <= 2) {
                        if (myBoard.board[x][y] == ' ') {
                            myBoard.updateBoard(x, y, player1.symbol);
                            valid_indices = true;
                        } else {
                            cout << "\nThis cell is already taken ..\nPlease , choose another one ..\n";
                        }
                    } else {
                        cout << "\nInvalid indices :(\nEach index should be from 0 to 2 .\nPlease , try again .. \n";
                    }
                }
                myBoard.displayBoard();
                if (myBoard.winner() == 1) {
                    cout << "\n\nCongratulations " << name1 << " (player 1) !\nYou won ..\n\n";
                    cout << "Hard luck " << name2 << " (player 2) ..\n\n";
                    break;
                }

                if (myBoard.isFull() && !myBoard.winner()) {
                    cout << "\n\nDraw !\n\n";
                    break;
                }

                valid_indices = false;
                while (!valid_indices) {
                    cout << endl << name2 << " (player 2) , enter the indices : ";
                    cin >> x >> y;
                    if (x >= 0 && x <= 2 && y >= 0 && y <= 2) {
                        if (myBoard.board[x][y] == ' ') {
                            myBoard.updateBoard(x, y, player2.symbol);
                            valid_indices = true;
                        } else {
                            cout << "\nThis cell is already taken ..\nPlease , choose another one ..\n";
                        }
                    } else {
                        cout << "\nInvalid indices :(\nEach index should be from 0 to 2 .\nPlease , try again .. \n";
                    }
                }
                myBoard.displayBoard();
                if (myBoard.winner() == 2) {
                    cout << "\n\nCongratulations " << name2 << " (player 2) !\nYou won ..\n\n";
                    cout << "Hard luck " << name1 << " (player 1) ..\n\n";
                    break;
                }

                if (myBoard.isFull() && !myBoard.winner()) {
                    cout << "\n\nDraw !\n\n";
                    break;
                }
            }

        } else if (choice == 3) {
            cout << "\nThank you for playing my Game :)\nI hope this is not the last time .. Bye ..\n\n";
        } else {
            cout << "Invalid choice :(\nPlease , try again ..\n\n";
        }
    }
}