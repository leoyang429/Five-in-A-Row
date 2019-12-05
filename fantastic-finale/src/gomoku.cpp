#include "gomoku.hpp"

using std::vector;
using std::string;

Gomoku::Gomoku() {
    board = vector<vector<int> >(kBoardSize, vector<int>(kBoardSize, kNoPlayer));
    replay_mode = false;
    replay_move = 2;
    which_player = kFirstPlayer;
    game_ends = false;
}

void Gomoku::Clear() {
    board = vector<vector<int> >(kBoardSize, vector<int>(kBoardSize, kNoPlayer));
    moves.clear();
    replay_move = 2;
    which_player = kFirstPlayer;
    game_ends = false;
}

vector<vector<int> > Gomoku::GetBoard() {
    return board;
}

vector<int> Gomoku::GetMoves() {
    return moves;
}

void Gomoku::AddMove(int move) {
    moves.push_back(move);
    board[move % kBoardSize][move / kBoardSize] = which_player;
    SwitchPlayer();
}

void Gomoku::Undo() {
    if (!moves.empty()) {
        board[moves.back() % kBoardSize][moves.back() / kBoardSize] = kNoPlayer;
        moves.pop_back();
        SwitchPlayer();
        if (replay_mode) {
            --replay_move;
        }
    }
    game_ends = false;
}

int Gomoku::GetWinner() {
    
    for (int i = 0; i < kBoardSize; ++i) {
        for (int j = 0; j < kBoardSize; ++j) {
            if (board[i][j] != kNoPlayer) {
                for (int k = 0; k < kDirections; ++k) {

                    bool is_winner = true;
                    for (int l = 1; l < kConsecutive; ++l) {
                        int x = i + l * kXChange[k];
                        int y = j + l * kYChange[k];
                        
                        if (x < 0 || y < 0 || x >= kBoardSize || y >= kBoardSize
                            || board[x][y] != board[i][j]) {
                            is_winner = false;
                            break;
                        }
                    }
                    
                    if (is_winner) {
                        game_ends = true;
                        return board[i][j];
                    }
                    
                }
            }
        }
    }
    
    return kNoPlayer;
}

bool Gomoku::SetReplayMode(ofFile fin, string replay_date, string replay_name) {
    
    string to_replay;
    while (getline(fin, to_replay)) {
        vector<string> might_replay = LineToVector(to_replay);
        if (might_replay.size() > 2 && might_replay[0] == replay_date && might_replay[1] == replay_name) {
            replay = might_replay;
            replay_mode = true;
            Clear();
            return true;
        }
    }
    
    return false;
}

void Gomoku::NextReplayMove() {
    if (replay_move < replay.size()) {
        int move = ofToInt(replay[replay_move++]);
        moves.push_back(move);
        
        board[move % kBoardSize][move / kBoardSize] = which_player;
        which_player = (which_player == 1) ? 2 : 1;
    }
}

void Gomoku::SaveMatch(ofFile fout, string match_name) {
    fout << ofGetYear() << ofGetMonth() << ofGetDay() << ' ';
    fout << match_name << ' ';
    for (int move: moves) {
        fout << move << ' ';
    }
    fout << endl;
}

void Gomoku::SwitchPlayer() {
    which_player = (which_player == 1) ? 2 : 1;
}

bool Gomoku::IsReplayMode() {
    return replay_mode;
}

vector<string> Gomoku::LineToVector(string line) {
    vector<string> vec;
    istringstream input_string_stream(line);
    string temp;
    while(input_string_stream >> temp) {
        vec.push_back(temp);
    }
    return vec;
}

bool Gomoku::IsGameEnd() {
    return game_ends;
}
