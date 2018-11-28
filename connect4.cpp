/*

Final Connect 4 Project Core. 
 Connect4_84_repository
Description: A simple terminal based game where you can play connect 4 with a friend.
 the game also features the save and load, where you can save a game or load a game.
 
 Team: 
 Firstname: Unique name
 Briana: bristagg
 Cameron: aylerc
 Weixiang Zhang: noxwei
 Kayla: kaylawi
 
 */

#include "connect4.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char *argv[])
{
    
    
    int selection;
    string garbage;
    
    cout << "Press 1 for terminal and 2 for graphics: ";
    while (!(cin >> selection))
    {
        cin.clear();
        getline(cin, garbage);
        cout << "Press 1 for terminal and 2 for graphics: ";
    }
    if (selection == 1)
    {
        terminalPlay();
    } else {
        cout << "Under construction..." << endl;

    }
    return 0;
    
}

void terminalPlay()
{
    string userPlayerOne;
    string userPlayerTwo;
    int playerCol;
    char playerInput;
    
    Board pickBoard;
    Result playerMove = NoResult;
    pickBoard = getBoard(userPlayerOne, userPlayerTwo);
    
    while ((playerInput != 'q') && ((playerMove == IllegalMove) || playerMove == NoResult))
    {
               pickBoard.prettyPrintBoard(cout);
        cout << endl << "Enter: the column to move, q to quit, s to save" << endl;
               if (pickBoard.toMove() == 1)
               {
                   cout <<  userPlayerOne << " enter your move: ";
               }
               else if (pickBoard.toMove() == 2)
               {
                   cout <<  userPlayerTwo << " enter your move: ";
               }
               cin >> playerCol;
               if (cin.fail()) {
                   cin.clear();
                   cin >> playerInput;
                   playerInput = tolower(playerInput);
                   if (playerInput == 's')
                   {
                       saveBoard(userPlayerOne, userPlayerTwo, pickBoard);
                   }
                   else if (playerInput == 'q')
                   {
                       break;
                   }
                   else
                   {
                       cout << "ILLEGAL MOVE: Try again" << endl;
                   }
               }

               else {
                   playerMove = pickBoard.makeMove(playerCol - 1);
                   if (playerMove == IllegalMove) {
                       cout << "ILLEGAL MOVE: Try again" << endl;
                   }
               }
           }
    if (playerInput == 'q')
    {
        cout << "Thanks for playing!"<< endl;
    }
    else if (playerMove == Win)
    {
        if (pickBoard.toMove() == 1)
        {
            cout << "Congratulations " << userPlayerTwo;
            cout << "! You won!" << endl;
        }
        else if (pickBoard.toMove() == 2)
        {
            cout << "Congratulations " << userPlayerOne;
            cout << "! You won!" << endl;
        }
        pickBoard.prettyPrintBoard(cout);
    }
    else if (playerMove == Draw)
    {
        cout << "Draw!" << endl;
        pickBoard.prettyPrintBoard(cout);
    }
}

Board getBoard(string &p1, string &p2)
{

    cout << "Enter L to load a game, or P to play: " << flush;
    string playerInput;
    string fen;
    Board playBoard;
    cin >> playerInput;
    if (playerInput == "p" || playerInput == "P"){
        cout << "Player 1, enter your name: " << flush;
        getline(cin, p1);
        getline(cin, p1);
        
        cout << endl << "Player 2, enter your name: " << flush;
        getline(cin, p2);
        playBoard = Board();
    }
    else{
        cout << "Enter the filename: " << flush;
        string fileName;
        cin >> fileName;
        ifstream fin;
        fin.open(fileName.c_str());
        getline(fin, p1);
        getline(fin, p2);
        getline(fin, fen);
        playBoard = Board(fen);
    }
    return playBoard;
}

void saveBoard(string p1, string p2, const Board &board)
{
    
    cout << "Enter the filename: " << flush;
    string fileName;
    cin >> fileName;
    ofstream fin;
    fin.open(fileName.c_str());
    fin << p1 << endl;
    fin << p2 << endl;
    board.printBoard_as_FENstring(fin);

    
}