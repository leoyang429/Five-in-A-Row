#ifndef gomoku_hpp
#define gomoku_hpp

#include "ofMain.h"
#include <iostream>
#include <string>
#include <vector>

const int kBoardSize = 15;
const int kConsecutive = 5;

const int kNoPlayer = 0;
const int kFirstPlayer = 1;
const int kSecondPlayer = 2;

const int kXChange[4]={0, 1, 1, -1};
const int kYChange[4]={1, 0, 1, 1};
const int kDirections = 4;

class Gomoku {
    
private:
    std::vector<std::vector<int> > board;
    std::vector<int> moves;
    std::vector<std::string> replay;
    bool replay_mode;
    int replay_move;
    int which_player;
    bool game_ends;
    
public:
    Gomoku();
    void Clear();
    std::vector<std::vector<int> > GetBoard();
    std::vector<int> GetMoves();
    void AddMove(int move);
    void Undo();
    int GetWinner();
    bool SetReplayMode(ofFile fin, std::string replay_date, std::string replay_name);
    void NextReplayMove();
    void SaveMatch(ofFile fout, std::string match_name);
    void SwitchPlayer();
    bool IsReplayMode();
    void SetReplay(bool replay_mode);
    bool IsGameEnd();
    std::vector<std::string> LineToVector(string line);
    
};

#endif
