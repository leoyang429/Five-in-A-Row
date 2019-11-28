#include "ofApp.h"

typedef pair<double, double> point;

Gomoku gomoku;
vector<point> intersects;

bool ai_mode;
GomokuAI gomoku_ai;

//--------------------------------------------------------------
void ofApp::setup(){

    // called only once
    
    // break down into logic and ui set
    
    const double kWidth = ofGetWidth() / (kBoardSize + 1);
    const double kHeight = (ofGetHeight() - kMargin) / (kBoardSize + 1);
    
    ai_mode = false;
    
    ofSetCircleResolution(100);
    
    background.load("boardbackground.jpeg");
    menubackground.load("menubackground.jpeg");
    
    restart_button = SimpleButton("Restart", 110, ofGetHeight() - kMargin + 10);
    restart_button.visible = true;
    
    undo_button = SimpleButton("Undo", 310, ofGetHeight() - kMargin + 10);
    undo_button.visible = true;
    
    save_button = SimpleButton("Save Game", 510, ofGetHeight() - kMargin + 10);
    save_button.visible = true;
    
    replay_button = SimpleButton("Replay", 710, ofGetHeight() - kMargin + 10);
    replay_button.visible = true;
    
    ai_button = SimpleButton("AI", 910, ofGetHeight() - kMargin + 10);
    ai_button.visible = true;
    
    exit_button = SimpleButton("Exit", 1210, ofGetHeight() - kMargin + 10);
    exit_button.visible = true;
    
    bgm.load("thegameison.mp3");
    bgm.setLoop(true);
    bgm.setVolume(0.1f);
    bgm.play();
    
    clickSound.load("click.mp3");
    
    restartSound.load("restart.mp3");
    restartSound.setVolume(0.3f);
    
    undoSound.load("undo.wav");
    undoSound.setVolume(0.3f);
    
    saveSound.load("save.mp3");
    saveSound.setVolume(0.3f);
    
    replaySound.load("replay.mp3");
    replaySound.setVolume(0.3f);
    
    for (int i = 1; i <= kBoardSize; ++i) {
        for (int j = 1; j <= kBoardSize; ++j) {
            intersects.push_back(make_pair(kWidth * i, kHeight * j));
        }
    }
    
    gomoku = Gomoku();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    int winner;
    if (!gomoku.IsGameEnd() && (winner = gomoku.GetWinner()) != kNoPlayer) {
        // add sound here
        if(winner == kFirstPlayer) {
            ofSystemAlertDialog("Congrats to player 1, You win!!");
        } else {
            ofSystemAlertDialog("Congrats to player 2, You win!!");
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // called every frame
    
    const double kWidth = ofGetWidth() / (kBoardSize + 1);
    const double kHeight = (ofGetHeight() - kMargin) / (kBoardSize + 1);
    
    ofFill();
    
    ofSetColor(255, 255, 255);
    menubackground.draw(0, 0, ofGetWidth(), ofGetHeight());
    //ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(237, 189, 101);
    background.draw(0, 0, ofGetWidth(), ofGetHeight() - kMargin);
    //ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight() - kMargin);
    
    ofSetColor(0, 0, 0);
    for(int i = 1; i <= kBoardSize; ++i) {
        ofDrawLine(i * kWidth, 0, i * kWidth, ofGetHeight() - kMargin);
    }
    for(int i = 1; i <= kBoardSize; ++i) {
        ofDrawLine(0, i * kHeight, ofGetWidth(), i * kHeight);
    }
    
    vector<int> moves = gomoku.GetMoves();
    bool is_first_player = true;
    for(int move: moves) {
        if (is_first_player) {
            ofSetColor(0, 0, 0);
        } else {
            ofSetColor(255, 255, 255);
        }
        ofDrawCircle(intersects[move].first, intersects[move].second, kRadius);
        is_first_player = !is_first_player;
    }
    
    restart_button.draw();
    undo_button.draw();
    save_button.draw();
    replay_button.draw();
    ai_button.draw();
    exit_button.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // consider use back to implement "undo", etc. in play mode
    
    if (key == ' ' && gomoku.IsReplayMode()) {
        gomoku.NextReplayMove();
        clickSound.play();
        return;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    const double kDistance = 30;
    const double kWidth = ofGetWidth() / (kBoardSize + 1);
    const double kHeight = (ofGetHeight() - kMargin) / (kBoardSize + 1);
    
    if (y <= ofGetHeight() - kMargin && gomoku.IsReplayMode()) {
        gomoku.NextReplayMove();
        clickSound.play();
        return;
    }
    
    vector<vector<int> > board = gomoku.GetBoard();
    for (int i = 0; i < intersects.size(); ++i) {
        
        point intersect = intersects[i];
        
        if (sqrt((x - intersect.first) * (x - intersect.first)
                 + (y - intersect.second) * (y - intersect.second)) < kDistance
            && board[i % kBoardSize][i / kBoardSize] == kNoPlayer) {
            gomoku.AddMove(i);
            
            clickSound.play();
            
            if (ai_mode) {
                update();
                if (gomoku.IsGameEnd()) {
                    return;
                }
                board = gomoku.GetBoard();
                int move = gomoku_ai.Move(board);
                if (move < 0 || move >= kBoardSize * kBoardSize) {
                    ofSystemAlertDialog("Computer Resigned, You win!");
                    gomoku.Clear();
                } else {
                    gomoku.AddMove(move);
                }
            }
            
            return;
        }
    
    }
    
    if (restart_button.checkClick(x, y)) {
        restartSound.play();
        gomoku.Clear();
    }
    
    if (undo_button.checkClick(x, y)) {
        undoSound.play();
        gomoku.Undo();
    }
    
    if (save_button.checkClick(x, y)) {
        saveSound.play();
        saveGame();
    }
    
    if (ai_button.checkClick(x, y)) {
        gomoku.Clear();
        gomoku_ai = GomokuAI();
        gomoku_ai.SetIsFirstPlayer(false);
        ai_mode = true;
    }
    
    if (replay_button.checkClick(x, y)) {
        replaySound.play();
        if (!gomoku.IsReplayMode()) {
            replayGame();
        } else {
            gomoku = Gomoku();
            replay_button = SimpleButton("Replay", 710, ofGetHeight() - kMargin + 10);
            replay_button.visible = true;
        }
    }
    
    if (exit_button.checkClick(x, y)) {
        _Exit(0);
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::saveGame() {
    
    fout.open("savedgames.txt", ofFile::Append);
    
    // still need to ensure the name of a particular day is unique
    string match_name = ofSystemTextBoxDialog("Please enter a name for your match", "untitled");
    gomoku.SaveMatch(fout, match_name);
    
    fout.close();
}

void ofApp::replayGame() {
    
    string replay_date = ofSystemTextBoxDialog("Please enter the date of game you'd like to replay (yyyymmdd)");
    string replay_name = ofSystemTextBoxDialog("Please enter the name of game you'd like to replay");
    
    fin.open("savedgames.txt", ofFile::ReadOnly);
    
    gomoku.SetReplayMode(fin, replay_date, replay_name);
        
    if (!gomoku.IsReplayMode()) {
        ofSystemAlertDialog("Match not recorded!");
    }
    
    fin.close();
}
