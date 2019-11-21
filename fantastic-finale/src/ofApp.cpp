#include "ofApp.h"

typedef pair<double, double> point;

const int kBoardSize = 15;
const double kRadius = 20;

const double kMargin = 100;

const int kNoPlayer = 0;
const int kFirstPlayer = 1;
const int kSecondPlayer = 2;

const int kXChange[8]={0, 0, 1, 1, 1, -1, -1, -1};
const int kYChange[8]={1, -1, 0, 1, -1, 0, 1, -1};
const int kDirections = 8;

const int kConsecutive = 5;

int which_player = 1;

bool game_ends = false;

vector<point> intersects;
vector<int> moves;

bool replay_mode = false;
vector<string> replay;
int replay_move= 2;

vector<vector<int> > board;

//--------------------------------------------------------------
void ofApp::setup(){

    // called only once
    
    const double kWidth = ofGetWidth() / (kBoardSize + 1);
    const double kHeight = (ofGetHeight() - kMargin) / (kBoardSize + 1);
    
    ofSetCircleResolution(100);
    
    fout.open("savedgames.txt", ofFile::Append);
    
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
    
    board = vector<vector<int> >(kBoardSize, vector<int>(kBoardSize, kNoPlayer));
    which_player = kFirstPlayer;
    
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
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    int winner = getWinner();
    if (winner != kNoPlayer && !game_ends) {
        cout << "Congrats to player " << winner << " !" << endl;
        if(winner == kFirstPlayer) {
            ofSystemAlertDialog("Congrats to player 1, You win!!");
            //ofxNotification("Congrats to player 1", "You win!!");
        } else {
            ofSystemAlertDialog("Congrats to player 2, You win!!");
            //ofxNotification("Congrats to player 2", "You win!!");
        }
        game_ends = true;
        //OF_EXIT_APP(0);
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
    for(int i = 1; i <= kBoardSize; ++i) ofDrawLine(i * kWidth, 0, i * kWidth, ofGetHeight() - kMargin);
    for(int i = 1; i <= kBoardSize; ++i) ofDrawLine(0, i * kHeight, ofGetWidth(), i * kHeight);
    
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
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    
    if (y <= ofGetHeight() - kMargin && replay_mode) {
        if (replay_move < replay.size()) {
            clickSound.play();
            moves.push_back(ofToInt(replay[replay_move++]));
        }
        return;
    }
    
    for (int i = 0; i < intersects.size(); ++i) {
        
        point intersect = intersects[i];
        
        if (sqrt((x - intersect.first) * (x - intersect.first) + (y - intersect.second) * (y - intersect.second)) < kDistance
            && board[i % kBoardSize][i / kBoardSize] == kNoPlayer) {
            moves.push_back(i);
            
            board[i % kBoardSize][i / kBoardSize] = which_player;
            which_player = (which_player == 1) ? 2 : 1;
            
            clickSound.play();
            
            return;
        }
    
    }
    
    if (restart_button.checkClick(x, y)) {
        restartSound.play();
        clearBoard();
    }
    
    if (undo_button.checkClick(x, y)) {
        undoSound.play();
        if (!moves.empty()) {
            board[moves.back() % kBoardSize][moves.back() / kBoardSize] = kNoPlayer;
            moves.pop_back();
            which_player = (which_player == 1) ? 2 : 1;
            if (replay_mode) {
                --replay_move;
            }
        }
        game_ends = false;
    }
    
    if (save_button.checkClick(x, y)) {
        saveSound.play();
        saveGame();
    }
    
    if (replay_button.checkClick(x, y)) {
        if (!replay_mode) {
            replaySound.play();
            replayGame();
        } else {
            replaySound.play();
            clearBoard();
            replay_mode = false;
            replay.clear();
            replay_button = SimpleButton("Replay", 710, ofGetHeight() - kMargin + 10);
            replay_button.visible = true;
        }
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

int ofApp::getWinner() {
    
    // still need to consider balance breaker for player 1
    for (int i = 0; i < kBoardSize; ++i) {
        for (int j = 0; j < kBoardSize; ++j) {
            if (board[i][j] != kNoPlayer) {
                for (int k = 0; k < kDirections; ++k) {

                    bool is_winner = true;
                    for (int l = 1; l < kConsecutive; ++l) {
                        int x = i + l * kXChange[k];
                        int y = j + l * kYChange[k];
                        
                        if (x < 0 || y < 0 || x >= kBoardSize || y >= kBoardSize || board[x][y] != board[i][j]) {
                            is_winner = false;
                            break;
                        }
                    }
                    
                    if (is_winner) {
                        return board[i][j];
                    }
                    
                }
            }
        }
    }
    
    return kNoPlayer;
        
}

void ofApp::clearBoard() {
    board = vector<vector<int> >(kBoardSize, vector<int>(kBoardSize, kNoPlayer));
    which_player = 1;
    moves.clear();
    game_ends = false;
    if (replay_mode) {
        replay_move = 2;
    }
}

void ofApp::saveGame() {
    string match_name = ofSystemTextBoxDialog("Please enter a name for your match", "untitled");
    fout << ofGetYear() << ofGetMonth() << ofGetDay() << ' ';
    fout << match_name << ' ';
    for (int move: moves) {
        fout << move << ' ';
    }
    fout << endl;
}

void ofApp::replayGame() {
    
    string replay_date = ofSystemTextBoxDialog("Please enter the date of game you'd like to replay (yyyymmdd)");
    string replay_name = ofSystemTextBoxDialog("Please enter the name of game you'd like to replay");
    
    fin.open("savedgames.txt", ofFile::ReadOnly);
    
    string to_replay;
    while (getline(fin, to_replay)) {
        vector<string> might_replay = lineToVector(to_replay);
        if (might_replay.size() > 2 && might_replay[0] == replay_date && might_replay[1] == replay_name) {
            replay = might_replay;
            replay_mode = true;
            replay_button = SimpleButton("Exit Replay", 710, ofGetHeight() - kMargin + 10);
            replay_button.visible = true;
            clearBoard();
        }
    }
        
    if (!replay_mode) {
        ofSystemAlertDialog("Match not recorded!");
    }
    
    fin.close();
}

vector<string> ofApp::lineToVector(string line) {
    vector<string> vec;
    istringstream ss(line);
    string temp;
    while(ss >> temp) {
        vec.push_back(temp);
    }
    return vec;
}
