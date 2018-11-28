#ifndef AI_H__
#define AI_H__

#include "board.h"
/*
 
 Welcome to Connect4_84's implementation of the reach for Connect 4. Our task was to implement an AI that can beat the 90 percent of the players. This AI uses mainly Minimax Alpha Beta Pruning(ABP) algorithm, an adversarial search algorithm for zero-sum games. The reason we picked this algorithm was due to the time constraints giving for our AI, at a limit of 2 seconds for each of AI's calculation. Due to the solved nature of the game, it's possible to calculate all of the possibilities of the match, however, by using min and max attack of the board, we can cut the time down dramatically.
 
 Basic Pseudocode of Minimax-ABP
 (source: Artificial Intelligence: A Modern Approach, Russell, Stuart J.; Norvig, Peter, 2003)
 
 function alphabeta(node, depth, α, β, maximizingPlayer)
      if depth = 0 or node is a terminal node
          return the heuristic value of node
      if maximizingPlayer
          v := -∞
          for each child of node
              v := max(v, alphabeta(child, depth – 1, α, β, FALSE))
              α := max(α, v)
              if β ≤ α
                  break (* β cut-off *)
          return v
      else
          v := ∞
          for each child of node
              v := min(v, alphabeta(child, depth – 1, α, β, TRUE))
              β := min(β, v)
              if β ≤ α
                  break (* α cut-off *)
          return v
 
 Definition of alpha and beta  (from Stuart J.; Norvig, Peter, 2003) 

 α = the value of the best (i.e., highest-value) choice we have found so far at any choice point along the path for MAX.
 
 β = the value of the best (i.e., lowest-value) choice we have found so far at any choice point along the path for MIN.
 
 */

/**
 * Requires: nothing.
 * Modifies: nothing.
 * Effects: Chooses a column for the next move
 *          and returns the column index. The
 *          return value must be in range
 *          [0, NUM_COLS-1].
 */
int connect4AI(const Board& board);


int boardEval(const Board& board);
int minimax(int depth, int turn, int alpha, int beta,  Board& board);


int nextMoveLocation = -1;
const int maximumDepth= 8 ;
const int BIGNUMBER =   INT_MAX;
const int TINYNUMBER =  INT_MIN;


bool thisMoveLegal(int column, const Board& board);
bool movePlacement (int column, PieceType currentPlayer, Board& board);
void undo(int column, Board& board);

int calculatePoints(int aiPoints, int possibleMovesAhead);
int gameResult(const Board& board);







#endif /* AI_H__ */
