#include "catch.hpp"
#include <iostream>
#include "gomoku-ai.hpp"

TEST_CASE("GomokuAI") {
    
    GomokuAI gomoku_ai;
    vector<vector<int> > board(kBoardSize, vector<int>(kBoardSize, 0));
    
    SECTION("GetScore Function") {
        gomoku_ai.SetIsFirstPlayer(true);
        
        // empty board
        REQUIRE(gomoku_ai.GetScore(board, 1, true) == 10);
        
        board[7][7] = 1; // a single stone
        REQUIRE(gomoku_ai.GetScore(board, 1) == 10 + 4 * kConsecutiveScore[1]);
        REQUIRE(gomoku_ai.GetScore(board, 2) == 10);
        
        board[7][8] = 1; // two
        REQUIRE(gomoku_ai.GetScore(board, 1) == 10 + 6 * kConsecutiveScore[1] + kConsecutiveScore[2]);
        
        board[7][9] = 1; // three
        REQUIRE(gomoku_ai.GetScore(board, 1) == 10 + 9 * kConsecutiveScore[1] + kConsecutiveScore[3]);
        
        board[7][10] = 1; // four
        REQUIRE(gomoku_ai.GetScore(board, 1) == kWinningScore);
        
        board[7][6] = 2; // four with one end blocked
        REQUIRE(gomoku_ai.GetScore(board, 1) == 10 + 12 * kConsecutiveScore[1] + kConsecutiveScore[3]);
        
        board[7][11] = 1; // five
        REQUIRE(gomoku_ai.GetScore(board, 1) == kWinningScore);
        
        board[7][12] = 1; // more than five
        REQUIRE(gomoku_ai.GetScore(board, 1) == kWinningScore);
        
        board[7][12] = 0;
        board[7][11] = 2; // four with both ends blocked
        REQUIRE(gomoku_ai.GetScore(board, 1) == 10 + 12 * kConsecutiveScore[1] + kConsecutiveScore[2]);
        
        board[7][11] = 0;
        board[6][7] = board[8][7] = 1; // three-four
        REQUIRE(gomoku_ai.GetScore(board, 1) == kWinningScore);
        
        board[7][10] = 0;
        board[7][6] = 0; // three-three
        REQUIRE(gomoku_ai.GetScore(board, 1) == kWinningScore);
    }
    
    SECTION("GetHash") {
        REQUIRE(gomoku_ai.GetHash(board) == 0);
        
        board[0][0] = 1;
        std::cout << gomoku_ai.GetHash(board) << endl;
    }
    
    SECTION("GetPossibleMoves") {
        REQUIRE(gomoku_ai.GetPossibleMoves(board).empty());
        
        board[7][7] = 1;
        //REQUIRE(gomoku_ai.GetPossibleMoves(board, 1).size() == 10);
    }
    
    SECTION("Move") {
        gomoku_ai.SetIsFirstPlayer(true);
        REQUIRE(gomoku_ai.Move(board) == 112);
        
        gomoku_ai.SetIsFirstPlayer(false);
        board[7][7] = 1;
        std::cout << gomoku_ai.Move(board) << std::endl;
    }
    
}
