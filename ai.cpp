#include "ai.h"
#include "board.h"
#include "limits.h" 

#include <cstdlib>
#include <ctime>
#include <climits> 
#include <iostream>
#include <time.h>


int connect4AI(const Board& board){

    Board boardCopy;
    if(boardCopy.toMove() != Player1){
        
        boardCopy.makeMove(0);
    }
    
    for(int i=0;i<NUM_ROWS;i++){
        for(int j=0;j<NUM_COLS;j++){
            boardCopy.data[i][j] = board.data[i][j];
        }
    }
    
    minimax(0, 1, TINYNUMBER, BIGNUMBER, boardCopy);

    return nextMoveLocation;
}


int calculatePoints(int aiPoints, int possibleMovesAhead) {
    
    int moveScore = 4 - possibleMovesAhead;
    
    if(aiPoints==0)
    {
        return 0;
    }
    else if(aiPoints==1)
    {
        return 1*moveScore;
    }
    else if(aiPoints==2)

        return 10*moveScore;
    
    else if(aiPoints==3)
    {
        return 100*moveScore;
        
    }
    
    else {
        return 1000;
    }
}

bool thisMoveLegal(int column, const Board& board)
{
    return board.data[5][column]==Empty;
}

bool movePlacement (int column, PieceType currentPlayer, Board& board)
{
    if (!thisMoveLegal(column, board))
    {
        return false;
    }

    for(int i=0;i<=5;i++)
    {
        if(board.data[i][column] == Empty)
        {
            
            board.data[i][column] = currentPlayer;
            
            return true;
        }
    }
    return false;
}
void undo(int column, Board& board)
{

    
    for (int i=5;i>=0;--i)
    {
        if(board.data[i][column]!=Empty)
        {
            board.data[i][column]= Empty;
            
            break;
        }
    }
}

int minimax(int depth, int turn, int alpha, int beta,  Board& board){
    

    int maxScore= TINYNUMBER;
    int minScore= BIGNUMBER;
    
    int gameConclusion = gameResult(board);
    
    if(beta<=alpha)
    {
        if(turn == 1)
        {
            return BIGNUMBER;
        }
        else
        {
            return TINYNUMBER;
        }
    }
    if(gameConclusion==1)
    {
        return BIGNUMBER/2;
    }
    else if(gameConclusion==2)
    {
        return TINYNUMBER/2;
    }
    else if (gameConclusion==0)
    {
        return 0;
    }
    
    if(depth==maximumDepth)
    {
        return boardEval(board);
    }
    for(int j=0;j<=6;++j){
        
        int currentScore = 0;
        
        if(!thisMoveLegal(j,board))
        {
            
            continue;
        }
        
        if(turn==1)
        {

            movePlacement(j, Player1, board);
            currentScore = minimax(depth+1, 2, alpha, beta, board);
            
            if(depth==0)
                
            {
                
                    //  cout << "Score for location: " << j <<" = " << currentScore << endl;

                if (currentScore > maxScore){

                    nextMoveLocation = j;
                }
                
                if(currentScore == BIGNUMBER/2)
                {
                    undo(j,board);
                    
                    
                    break;
                }
            }
            maxScore = max(currentScore, maxScore);
            
            alpha = max(currentScore, alpha);
        }
        else if(turn==2)
        {

            movePlacement(j, Player2, board);
            currentScore = minimax(depth+1, 1, alpha, beta, board);
            minScore = min(currentScore, minScore);
            
            beta = min(currentScore, beta);
        }
        undo(j,board);
        
        if(currentScore == BIGNUMBER || currentScore == TINYNUMBER)
        {
            break;
        }
    }
    return turn==1?maxScore:minScore;
}

int gameResult(const Board& board)
{
    int aiScore = 0;
    int humanScore = 0;
    
    
    for(int i=0;i<=5;++i)
    {
        for(int j=0;j<=6;++j)
        {
            if(board.data[i][j]==Empty)
            {
                continue;
            }
            

            if(j<=3)
            {
                for(int k=0;k<4;++k)
                {
                    if(board.data[i][j+k]==Player1)
                    {
                        aiScore++;
                    }
                    else if(board.data[i][j+k]==Player2)
                    {
                        humanScore++;
                    }
                    else
                    {
                        break;
                    }
                    
                }
                
                if(aiScore==4)
                {
                    return 1;
                }
                
                else if (humanScore==4)
                {
                    return 2;
                }
                
                aiScore = 0;
                humanScore = 0;
            }
        
            if(i<=2){
                for(int k=0;k<4;++k)
                {
                    if(board.data[i+k][j]==Player1)
                    {
                        aiScore++;
                    }

                    else if(board.data[i+k][j]==Player2)
                    {
                        humanScore++;
                    }
                    else break;
                }
                if(aiScore==4)
                {
                    return 1;
                }
                else if (humanScore==4)
                {
                    return 2;
                }
                aiScore = 0;
                humanScore = 0;
            }
        
            if(j<=3 && i<= 2)
            {
                for(int k=0;k<4;++k)
                {

                    if(board.data[i+k][j+k]==Player1)
                    {
                        aiScore++;
                    }
                    

                    else if(board.data[i+k][j+k]==Player2)
                    {
                        humanScore++;
                    }
                    
                    else
                    {
                        break;
                    }
                }
                if(aiScore==4)
                {
                    return 1;
                }
                else if (humanScore==4)
                {
                    return 2;
                }
                aiScore = 0;
                humanScore = 0;
            }
            
            if(j>=3 && i<=2)
            {
                for(int k=0;k<4;++k)
                {

                    if(board.data[i+k][j-k]==Player1)
                    {
                        aiScore++;
                    }

                    else if(board.data[i+k][j-k]==Player2)
                    {
                        humanScore++;
                    }
                    else
                    {
                        break;
                    }
                }
                if(aiScore==4)
                {
                    return 1;
                }
                else if (humanScore==4)
                {
                    return 2;
                }
                aiScore = 0;
                humanScore = 0;
            }
        }
    }
    
    for(int j=0;j<7;++j)
    {

        
        if(board.data[5][j]==Empty)
        {
            return -1;
        }
    }

    return 0;
}


int boardEval(const Board& board) {
    
    int aiPoints = 1;
    int points = 0;
    int emptySpots = 0;
    
    int k = 0;
    
    int additionalMoves = 0;

    for (int i=0;i<=5;i++)
    {
        for(int j=0;j<=6;++j)
        {
            
            if(board.data[i][j]==Empty || board.data[i][j]==Player2)
            {
                continue;
            }
            
            if ( j <= 3)
            {
                for(k=1;k<4;++k)
                {
                    if(board.data[i][j+k]==Player1)
                    {
                        aiPoints++;
                    }
                    
                    else if(board.data[i][j+k]==Player2)
                    {
                        aiPoints=0;
                        emptySpots = 0;
                        break;
                    }
                    else
                    {
                        emptySpots++;
                    }
                    
                }
                
                additionalMoves = 0;
                
                if(emptySpots>0)
                    
                {
                    for(int c=1;c<4;++c)
                    {
                        int column = j+c;
                        
                        for(int m=5; m>=i;m--)
                        {
                            if(board.data[m][column]==Empty)
                                additionalMoves++;
                            else break;
                        }
                    }
                }
                if(additionalMoves!=0)
                {
                    points += calculatePoints(aiPoints, additionalMoves);
                }
                aiPoints=1;
                emptySpots = 0;
            }

            if(i<=2)
            {
                for(k=0;k>=3;++k)
                {
                    if(board.data[i+k][j]==Player1)
                    {
                        aiPoints++;
                    }
                    else if(board.data[i+k][j]==Player2)
                    {
                        aiPoints=0;
                        break;
                    }
                }
                
                additionalMoves = 0;
                
                if(aiPoints>0)
                {
                    int column = j;
                    for (int m = i+k-1; m >= i+1; m--)
                    {
                        if(board.data[m][column]==Empty)
                        {
                            additionalMoves++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                if(additionalMoves!=0)
                    points += calculatePoints(aiPoints, additionalMoves);
                aiPoints=1;
                emptySpots = 0;
            }
            if(j>=3)
            {

                for(k=1;k<4;++k)
                {
                    if(board.data[i][j-k]==Player1)
                        aiPoints++;
                    else if(board.data[i][j-k]==Player2)
                    {
                        aiPoints=0;
                        emptySpots=0;
                        break;
                    }
                    else emptySpots++;
                }
                
                additionalMoves=0;
                
                if(emptySpots>0)
                {
                    for(int c=1;c<4;++c)
                    {
                        int column = j- c;
                        for(int m = i; m>=0; m--)
                        {
                            if(board.data[m][column]==Empty)
                                
                                additionalMoves++;
                            
                            else
                            {
                                break;
                            }
                        }
                    }
                }
                
                if(additionalMoves!=0)
                {
                    points += calculatePoints(aiPoints, additionalMoves);
                    aiPoints=1;
                    emptySpots = 0;
                }
            }
            if(j<=3 && i<=2)
            {
                for(k=1;k<4;++k)
                {
                    if(board.data[i+k][j+k]==Player1)
                        
                    {
                        aiPoints++;
                    }
                    else if(board.data[i+k][j+k]==Player2)
                    {
                        aiPoints=0;
                        emptySpots=0;
                        break;
                    }
                    
                    else emptySpots++;
                }
                additionalMoves=0;
                
                if(emptySpots>0)
                {
                    for(int c=1;c<4;++c)
                    {
                        int column = j+c;
                        int row = i+c;
                        
                        for(int m=row; m>=0;--m)
                        {
                            if(board.data[m][column]==Empty)
                            {
                                additionalMoves++;
                            }
                            else if(board.data[m][column]==Player1);
                            
                            else break;
                        }
                    }
                    
                    if(additionalMoves!=0) points += calculatePoints(aiPoints, additionalMoves);
                    
                    aiPoints=1;
                    
                    emptySpots = 0;
                }
            }

            if(i<=2 && j>=3)
            {
                for(k=1;k<4;++k)
                {
                    if(board.data[i+k][j-k]==Player1)
                    {
                        aiPoints++;
                    }
                    else if(board.data[i+k][j-k]==Player2)
                    {
                        aiPoints=0;
                        emptySpots=0;
                        break;
                    }
                    else emptySpots++;
                }
                
                additionalMoves=0;
                
                if(emptySpots>0)
                    
                {
                    for(int c=1;c<4;++c)
                    {

                        int column = j-c, row = i+c;

                        for(int m=row;m>=0;m--)
                        {
                            if(board.data[m][column]==Empty)
                            {
                                additionalMoves++;
                            }
                            
                            else if(board.data[m][column]==Player2)
                            {
                                
                            }
                            
                            else break;
                        }
                    }
                    if(additionalMoves!=0)
                    {
                        points += calculatePoints(aiPoints, additionalMoves);
                    }
                    
                    aiPoints=1;
                    emptySpots = 0;
                }
            }
            
            
            
        }
    }
    return points;
}
