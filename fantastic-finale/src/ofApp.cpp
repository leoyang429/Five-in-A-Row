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

vector<point> intersects;
vector<point> circles;

vector<vector<int> > board;

//--------------------------------------------------------------
void ofApp::setup(){

    // called only once
    
    const double kWidth = ofGetWidth() / (kBoardSize + 1);
    const double kHeight = (ofGetHeight() - kMargin) / (kBoardSize + 1);
    
    restart_button = SimpleButton("Restart", 110, ofGetHeight() - kMargin + 10);
    restart_button.visible = true;
    
    retract_button = SimpleButton("Retract", 310, ofGetHeight() - kMargin + 10);
    retract_button.visible = true;
    
    board = vector<vector<int> >(kBoardSize, vector<int>(kBoardSize, kNoPlayer));
    which_player = kFirstPlayer;
    
    bgm.load("epic_sax_guy.mp3");
    bgm.setLoop(true);
    bgm.play();
    bgm.setVolume(0.03f);
    
    clickSound.load("click.mp3");
    
    for (int i = 1; i <= kBoardSize; ++i) {
        for (int j = 1; j <= kBoardSize; ++j) {
            intersects.push_back(make_pair(kWidth * i, kHeight * j));
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    int winner = getWinner();
    if (winner != kNoPlayer) {
        cout << "Congrats to player " << winner << " !" << endl;
        if(winner == kFirstPlayer) {
            ofxNotification("Congrats to player 1", "You win!!");
        } else {
            ofxNotification("Congrats to player 2", "You win!!");
        }
        OF_EXIT_APP(0);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // called every frame
    
    const double kWidth = ofGetWidth() / (kBoardSize + 1);
    const double kHeight = (ofGetHeight() - kMargin) / (kBoardSize + 1);
    
    ofFill();
    
    ofSetColor(255, 255, 255);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(237, 189, 101);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight() - kMargin);
    
    ofSetColor(0, 0, 0);
    for(int i = 1; i <= kBoardSize; ++i) ofDrawLine(i * kWidth, 0, i * kWidth, ofGetHeight() - kMargin);
    for(int i = 1; i <= kBoardSize; ++i) ofDrawLine(0, i * kHeight, ofGetWidth(), i * kHeight);
    
    bool is_first_player = true;
    for(point circle: circles) {
        if (is_first_player) {
            ofSetColor(0, 0, 0);
        } else {
            ofSetColor(255, 255, 255);
        }
        ofDrawCircle(circle.first, circle.second, kRadius);
        is_first_player = !is_first_player;
    }
    
    restart_button.draw();
    retract_button.draw();
    
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
    
    for (int i = 0; i < intersects.size(); ++i) {
        
        point intersect = intersects[i];
        
        if (sqrt((x - intersect.first) * (x - intersect.first) + (y - intersect.second) * (y - intersect.second)) < kDistance
            && board[i % kBoardSize][i / kBoardSize] == kNoPlayer) {
            circles.push_back(intersect);
            
            board[i % kBoardSize][i / kBoardSize] = which_player;
            which_player = (which_player == 1) ? 2 : 1;
            
            clickSound.play();
            clickSound.setVolume(0.8f);
            
            break;
        }
    
    }
    
    if (restart_button.checkClick(x, y)) {
        clearBoard();
    }
    
    if (retract_button.checkClick(x, y)) {
        if (!circles.empty()) {
            circles.pop_back();
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
    which_player = 1;
    circles.clear();
}
