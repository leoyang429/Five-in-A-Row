#ifndef gomoku_ai_hpp
#define gomoku_ai_hpp

#include <iostream>
#include <random>
#include "gomoku.hpp"
#include <unordered_map>

typedef unsigned long long ll;

const int kMaxSearchDepth = 6;

const int kWinningScore = 1000000000;
const int kConsecutiveScore[5] = {0, 0, 50, 500, 5000};
const int kEnemyConsecutiveScore[5] = {0, 0, 50, 2000, 500000};

class GomokuAI {
    
private:
    bool is_empty_board;
    bool is_first_player;
    ll zobrist_table[kBoardSize][kBoardSize][2];
    std::mt19937 mt;
    ll hash;
    
public:
    unordered_map<int, int> model;
    GomokuAI(); // set up the hash table
    ll RandomUnsignedLL();
    void SetIsFirstPlayer(bool is_first_player);
    bool GetIsFirstPlayer();
    int GetScore(const std::vector<std::vector<int> >& board, int player, bool is_enemy_next);
    ll GetHash(const std::vector<std::vector<int> >& board);
    int Move(std::vector<std::vector<int> >& board);
    int Minimax(std::vector<std::vector<int> >& board, int depth, int alpha_beta);
    std::vector<int> GetPossibleMoves(std::vector<std::vector<int> >& board);
    int HasWon(const std::vector<std::vector<int> >& board, int player);
    
};

#endif
