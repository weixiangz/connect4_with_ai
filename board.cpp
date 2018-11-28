
#include "board.h"

    //done
Board::Board()
{
    
    nextPlayer_to_move = Player1;
    
    for (int x = 0; x < NUM_ROWS; x++)
    {
        for ( int y = 0; y < NUM_COLS; y++)
        {
            data[x][y] = Empty;
        }
    }
    
}

    //done
Board::Board(const string &fen)
{
    int playerRow = 0;
    int playerCol = 0;
    
    for (int chip = 0; chip < fen.length()-2; chip++)
    {
        if (fen[chip] == PLAYER1_TOKEN)
        {
            data[playerRow][playerCol]=Player1;
            playerCol++;
        }
        else if (fen[chip]==PLAYER2_TOKEN)
        {
            data[playerRow][playerCol]=Player2;
            playerCol++;
        }
        else if (fen[chip]=='/')
        {
            playerRow++;
            playerCol = 0;
        }
        else
        {
            int xplayer = fen[chip] - '0';
            
            for (int i = 0; i < xplayer ; i++)
            {
                data[playerRow][playerCol] = Empty;
                playerCol++;
            }
        }
    }
    
    if (fen.at(fen.length()-1)=='x')
    {
        nextPlayer_to_move = Player1;
    }
    else if (fen.at(fen.length()-1) == 'o')
    {
        nextPlayer_to_move = Player2;
        
    }

}

    //done
void Board::printBoard_as_FENstring(ostream &os) const
{
    int nullCount = 0;

    for (int x = 0; x < NUM_ROWS; x++)
    {
        if (x != 0)
            os << '/';
        
        for (int y = 0; y < NUM_COLS; y++)
        {
            if (data[x][y] == Player1)
            {
                if (nullCount != 0)
                {
                    os <<nullCount;
                    nullCount = 0;
                }
                os << PLAYER1_TOKEN;
            }
            
            else if (data[x][y] == Player2)
            {
                if (nullCount != 0)
                {
                    os << nullCount;
                    nullCount =0;
                }
                os << PLAYER2_TOKEN;
            }
            
            else
            {
                nullCount++;
            }
            
        }
        
        
        if (nullCount != 0)
        {
            os << nullCount;
            nullCount = 0;
        }
        
    }
    
    if (nextPlayer_to_move == Player1)
    {
        os << " x";
    }
    else
    {
        os << " o";
    }
    
}

    //done
void Board::prettyPrintBoard(ostream &os) const // Given and therefore tested do not change this under any circumstance
{
    
    os << endl;
    for (int row = NUM_ROWS - 1; row >= 0; row--)
    {
        os << "     +---+---+---+---+---+---+---+"
        << endl
        << "    ";
        
        for (int col = 0; col < NUM_COLS; col++)
        {
            os << " | " ;
            if ( data[row][col] == Player1)
                os <<  PLAYER1_TOKEN;
            else if (data[row][col] == Player2)
                os << PLAYER2_TOKEN;
            else
                os << EMPTY_TOKEN;
        }
        os << " |" << endl;
    }
    os << "     +---+---+---+---+---+---+---+" << endl
    <<"  col  1   2   3   4   5   6   7" << endl;
    return;
}

    //done
Result Board::makeMove(int col)
{
    
    int firstMove = getFirstFreeRow(col);
    
    if(col < 0 )
    {
        return IllegalMove;
    }
    if(col > 6){
        return IllegalMove;
    }
    if (firstMove == 6)
    {
        return IllegalMove;
    }
    
    else if ((data[firstMove][col]= nextPlayer_to_move))
    {
        if (isWin(firstMove, col)==true)
        {
            updateToMove();
            return Win;
        }
        else if (isBoardFull()==true)
        {
            updateToMove();
            return Draw;
        }
        else
        {
            updateToMove();
            return NoResult;
        }
    }

    return NoResult;
}
    //done
int Board::toMove() const
{
    
    
    if (nextPlayer_to_move == Player1)
    {
        return 1;
    }
    else if (nextPlayer_to_move == Player2)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}
    //done
int Board::getFirstFreeRow(int col) const
{
    for (int x = 0; x < NUM_ROWS; x++)
    {
        if ( data[x][col] == Empty)
        {
            return x;
        }
    }
    return NUM_ROWS;
}

    //maybe?1

PieceType Board::updateToMove()
{
    if (toMove()==2)
    {
        nextPlayer_to_move=Player1;
        return Player2;
    }
    else if (toMove()==1)
    {
        nextPlayer_to_move=Player2;
        return Player1;
    }
    else
    {
        return Empty;
    }
    
}

    //
bool Board::isBoardFull() const
{
    for ( int x = 0; x < NUM_ROWS; x++)
    {
        for ( int y = 0; y < NUM_COLS; y++)
        {
            if (data[x][y] == Empty)
            {
                return false;
            }
            
        }
    }
    return true;
}



    //done
bool Board::inBounds(int row, int col) const
{
    if ( row > NUM_ROWS-1  || row < 0 || col < 0 || col > NUM_COLS-1)
    {
        return false;
    }
    else {
        return true;
    }
    return true;
}

    //done
int Board::piecesInDirection(int row, int col, int dRow, int dCol) const
{
    
    int amounts = 0;
    PieceType user = data[row][col];
    row += dRow;
    col += dCol;
    
    while (inBounds(row, col) && data[row][col]== user)
    {
        amounts++;
        row += dRow;
        col += dCol;
    }
    return amounts;
    
}
bool Board::isWin(int row, int col) const
{
    
    if (piecesInDirection(row, col, 0, 1) + piecesInDirection(row, col, 0, -1) >= 3 )
    {
        
        return true;
    }
    else if (piecesInDirection(row, col, 1, 0) + piecesInDirection(row, col, -1, 0) >= 3)
    {
        
        return true;
    }
    else if(piecesInDirection(row, col, 1, -1) + piecesInDirection(row, col, -1, 1) >= 3)
    {
        
        return true;
    }
    
    else if (piecesInDirection(row, col, 1, 1) + piecesInDirection(row, col, -1, -1) >= 3)
    {
        
        return true;
    }
    else
    {
        return false;
    }
    return false;
    
}