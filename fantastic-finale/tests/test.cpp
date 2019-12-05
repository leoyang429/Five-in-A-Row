#include "catch.hpp"
#include <iostream>
#include "gomoku-ai.hpp"
#include "gomoku.hpp"

TEST_CASE("gomoku") {
    
    Gomoku gomoku;
    vector<vector<int> > board;
    
    SECTION("AddMove") {
        gomoku.AddMove(112);
        board = gomoku.GetBoard();
        REQUIRE(board[7][7] == kFirstPlayer);
        
        gomoku.AddMove(0);
        board = gomoku.GetBoard();
        REQUIRE(board[0][0] == kSecondPlayer);
    }
    
    SECTION("Undo") {
        gomoku.AddMove(112);
        gomoku.Undo();
        board = gomoku.GetBoard();
        REQUIRE(board[7][7] == kNoPlayer);
    }
    
    SECTION("GetWinner") {
        REQUIRE(gomoku.GetWinner() == kNoPlayer);
        for (int i = 0; i < 2 * kConsecutive - 1; ++i) {
            if (!(i & 1)) {
                gomoku.AddMove(i / 2);
            } else {
                gomoku.AddMove(i * 10);
            }
        }
        REQUIRE(gomoku.GetWinner() == kFirstPlayer);
    }
    
    SECTION("LineToVetor") {
        string line = "this is a test case";
        vector<string> vec = gomoku.LineToVector(line);
        REQUIRE(vec.size() == 5);
        REQUIRE(vec[0] == "this");
    }
    
}

TEST_CASE("GomokuAI") {
    
    GomokuAI gomoku_ai;
    vector<vector<int> > board(kBoardSize, vector<int>(kBoardSize, 0));
    
    SECTION("GetScore Function") {
        gomoku_ai.SetIsFirstPlayer(true);
        
        // empty board
        REQUIRE(gomoku_ai.GetScore(board, 1, true) == 10);
        
        board[7][7] = 1; // a single stone
        REQUIRE(gomoku_ai.GetScore(board, 1, true) == 10);
        REQUIRE(gomoku_ai.GetScore(board, 2, true) == 10);
        
        board[7][8] = 1; // two
        REQUIRE(gomoku_ai.GetScore(board, 1, true) == 10 + kConsecutiveScore[2]);
        
        board[7][9] = 1; // three
        REQUIRE(gomoku_ai.GetScore(board, 1, true) == 10 + kConsecutiveScore[3]);
        
        board[7][10] = 1; // four
        REQUIRE(gomoku_ai.GetScore(board, 1, true) == 10 + kConsecutiveScore[4]);
        
        board[7][6] = 2; // four with one end blocked
        REQUIRE(gomoku_ai.GetScore(board, 1, true) == 10 + kConsecutiveScore[3]);
        
        board[7][11] = 1; // five
        REQUIRE(gomoku_ai.GetScore(board, 1, true) == kWinningScore);
        
        board[7][12] = 1; // more than five
        REQUIRE(gomoku_ai.GetScore(board, 1, true) == kWinningScore);
        
        board[7][12] = 0;
        board[7][11] = 2; // four with both ends blocked
        REQUIRE(gomoku_ai.GetScore(board, 1, true) == 10 + kConsecutiveScore[2]);
    }
    
    SECTION("GetHash") {
        REQUIRE(gomoku_ai.GetHash(board) == 0);
    }
    
    SECTION("GetPossibleMoves") {
        REQUIRE(gomoku_ai.GetPossibleMoves(board).empty());
        
        board[7][7] = 1;
        REQUIRE(gomoku_ai.GetPossibleMoves(board).size() == 8);
    }
    
    SECTION("Move") {
        gomoku_ai.SetIsFirstPlayer(true);
        REQUIRE(gomoku_ai.Move(board) == 112);
        
        gomoku_ai.SetIsFirstPlayer(false);
        board[7][7] = 1;
        REQUIRE((gomoku_ai.Move(board) >= 0 && gomoku_ai.Move(board) < kBoardSize * kBoardSize));
    }
    
}
