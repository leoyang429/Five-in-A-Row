#include "ofApp.h"

typedef pair<double, double> point;

Gomoku gomoku;
vector<point> intersects;

bool ai_mode = false;
GomokuAI gomoku_ai;

//--------------------------------------------------------------
void ofApp::setup(){
    SetupUI();
    SetupBoard();
}

//--------------------------------------------------------------
void ofApp::update(){
    int winner;
    if (!gomoku.IsGameEnd() && (winner = gomoku.GetWinner()) != kNoPlayer) {
        if (ai_mode) {
            if (winner == 2 - gomoku_ai.GetIsFirstPlayer()) {
                ofSystemAlertDialog("AI wins; please try again:(");
            } else {
                ofSystemAlertDialog("Congratulations, You beats AI!!");
            }
        } else {
            if (winner == kFirstPlayer) {
                ofSystemAlertDialog("Congrats to player 1, You win!!");
            } else {
                ofSystemAlertDialog("Congrats to player 2, You win!!");
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofFill();
    DrawBackground();
    DrawBoard();
    DrawStones();
    DrawButtons();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 8 && gomoku.IsReplayMode()) { // backspace for undo
        gomoku.Undo();
        undoSound.play();
        return;
    }
    
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
    
    // next move in replay mode
    if (y <= ofGetHeight() - kMargin && gomoku.IsReplayMode()) {
        gomoku.NextReplayMove();
        clickSound.play();
        return;
    }
    
    // check whether a move is made
    vector<vector<int> > board = gomoku.GetBoard();
    for (int i = 0; i < intersects.size(); ++i) {
        point intersect = intersects[i];
        
        if (sqrt((x - intersect.first) * (x - intersect.first)
                 + (y - intersect.second) * (y - intersect.second)) < kDistance
            && board[i % kBoardSize][i / kBoardSize] == kNoPlayer) {
            
            clickSound.play();
            gomoku.AddMove(i);
            
            if (ai_mode) {
                GetAIMove();
            }
            
            return;
        }
    
    }
    
    // click the buttons
    if (restart_button.checkClick(x, y)) {
        restartSound.play();
        ai_mode = false;
        gomoku.Clear();
    }
    
    if (undo_button.checkClick(x, y)) {
        undoSound.play();
        gomoku.Undo();
    }
    
    if (save_button.checkClick(x, y)) {
        saveSound.play();
        SaveGame();
    }
    
    if (ai_button.checkClick(x, y)) {
        aiSound.play();
        SetAIMode();
    }
    
    if (replay_button.checkClick(x, y)) {
        replaySound.play();
        SetReplayMode();
    }
    
    if (exit_button.checkClick(x, y)) {
        _Exit(0);
    }
    
    if (show_matches_button.checkClick(x, y)) {
        showMatchesSound.play();
        ShowPastMatches();
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

void ofApp::SetupUI() {
    ofSetCircleResolution(100);
    
    SetupBackground();
    SetupButtons();
    SetupSound();
}

void ofApp::SetupBackground() {
    background.load("boardbackground.jpeg");
    menubackground.load("menubackground.jpeg");
}

void ofApp::SetupButtons() {
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
    
    show_matches_button = SimpleButton("Past Matches", 1410, ofGetHeight() - kMargin + 10);
    show_matches_button.visible = true;
}

void ofApp::SetupSound() {
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
    
    aiSound.load("ai.mp3");
    
    showMatchesSound.load("showmatches.mp3");
    showMatchesSound.setVolume(0.3f);
}

void ofApp::SetupBoard() {
    width = ofGetWidth() / (kBoardSize + 1);
    height = (ofGetHeight() - kMargin) / (kBoardSize + 1);
    
    for (int i = 1; i <= kBoardSize; ++i) {
        for (int j = 1; j <= kBoardSize; ++j) {
            intersects.push_back(make_pair(width * i, height * j));
        }
    }
}

void ofApp::DrawBackground() {
    ofSetColor(255, 255, 255);
    menubackground.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(237, 189, 101);
    background.draw(0, 0, ofGetWidth(), ofGetHeight() - kMargin);
}

void ofApp::DrawBoard() {
    ofSetColor(0, 0, 0);
    for(int i = 1; i <= kBoardSize; ++i) {
        ofDrawLine(i * width, 0, i * width, ofGetHeight() - kMargin);
    }
    for(int i = 1; i <= kBoardSize; ++i) {
        ofDrawLine(0, i * height, ofGetWidth(), i * height);
    }
}

void ofApp::DrawButtons() {
    restart_button.draw();
    undo_button.draw();
    save_button.draw();
    replay_button.draw();
    ai_button.draw();
    exit_button.draw();
    show_matches_button.draw();
}

void ofApp::DrawStones() {
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
}

void ofApp::GetAIMove() {
    update();
    if (gomoku.IsGameEnd()) {
        return;
    }
    
    vector<vector<int> > board = gomoku.GetBoard();
    int move = gomoku_ai.Move(board);
    if (move < 0 || move >= kBoardSize * kBoardSize) {
        ofSystemAlertDialog("Computer Resigned, You win!");
        gomoku.Clear();
    } else {
        clickSound.play();
        gomoku.AddMove(move);
    }
}

void ofApp::SetAIMode() {
    gomoku.Clear();
    gomoku_ai = GomokuAI();
    bool is_ai_first_player = ofSystemTextBoxDialog("Do you want to go first(y/n)", "y") != "y";
    gomoku_ai.SetIsFirstPlayer(is_ai_first_player);
    ai_mode = true;
    if (is_ai_first_player) {
        vector<vector<int> > board = gomoku.GetBoard();
        gomoku.AddMove(gomoku_ai.Move(board));
    }
}

void ofApp::SaveGame() {
    
    fout.open(kSavedGames, ofFile::Append);
    
    string match_name = ofSystemTextBoxDialog("Please enter a name for your match", "untitled");
    
    // weird that you cannot copy fout to anther function
    // otherwise it would open a read-only copy
    //gomoku.SaveMatch(fout, match_name);
    
    fout << ofGetYear();
    if (ofGetMonth() < 10) {
        fout << 0;
    }
    fout << ofGetMonth();
    if (ofGetDay() < 10) {
        fout << 0;
    }
    fout << ofGetDay() << ' ';
    fout << match_name << ' ';
    for (int move: gomoku.GetMoves()) {
        fout << move << ' ';
    }
    fout << endl;
    
    fout.close();
}

void ofApp::SetReplayMode() {
    if (!gomoku.IsReplayMode()) {
        ReplayGame();
    } else {
        gomoku = Gomoku();
        replay_button = SimpleButton("Replay", 710, ofGetHeight() - kMargin + 10);
        replay_button.visible = true;
    }
}

void ofApp::ReplayGame() {
    
    string replay_date = ofSystemTextBoxDialog("Please enter the date of game you'd like to replay (yyyymmdd)");
    string replay_name = ofSystemTextBoxDialog("Please enter the name of game you'd like to replay");
    
    fin.open(kSavedGames, ofFile::ReadOnly);
    
    gomoku.SetReplayMode(fin, replay_date, replay_name);
        
    if (!gomoku.IsReplayMode()) {
        ofSystemAlertDialog("Match not recorded!");
    }
    
    fin.close();
}

void ofApp::ShowPastMatches() {
    string past_matches = "";
    
    fin.open(kSavedGames, ofFile::ReadOnly);
    
    string past_match;
    while (getline(fin, past_match)) {
        past_matches += gomoku.LineToVector(past_match)[0];
        past_matches += " ";
        past_matches += gomoku.LineToVector(past_match)[1];
        past_matches += "\n";
    }
    
    fin.close();
    
    ofSystemAlertDialog(past_matches);
}
