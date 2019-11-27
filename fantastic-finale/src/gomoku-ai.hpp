#ifndef gomoku_ai_hpp
#define gomoku_ai_hpp

#include <iostream>
#include <random>
#include "gomoku.hpp"
#include <queue>

typedef unsigned long long ll;

const int kMaxSearchDepth = 5;

const int kWinningScore = 1000000000;
const int kConsecutiveScore[4] = {0, 0, 50, 1000};

class GomokuAI {
    
private:
    bool is_empty_board;
    bool is_first_player;
    ll zobrist_table[kBoardSize][kBoardSize][2];
    std::mt19937 mt;
    ll hash;
    
public:
    GomokuAI(); // set up the hash table
    ll RandomUnsignedLL();
    void SetIsFirstPlayer(bool is_first_player);
    int Evaluate(const std::vector<std::vector<int> >& board); // next move comes from the other player
    int GetScore(const std::vector<std::vector<int> >& board, int player);
    ll GetHash(const std::vector<std::vector<int> >& board);
    int Move(std::vector<std::vector<int> >& board);
    int Minimax(std::vector<std::vector<int> >& board, int depth, int alpha_beta);
    std::vector<int> GetPossibleMoves(std::vector<std::vector<int> >& board);
    
};

#endif
