#ifndef gomoku_ai_hpp
#define gomoku_ai_hpp

#include <iostream>
#include "gomoku.hpp"

class GomokuAI {
    
private:
    bool is_first_player;
    
public:
    void SetIsFirstPlayer(bool is_first_player);
    int Evaluate(const std::vector<std::vector<int> >& board);
    int Move(const std::vector<std::vector<int> >& board);
    
};

#endif
