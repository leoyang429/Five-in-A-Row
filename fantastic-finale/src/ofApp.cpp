#include "ofApp.h"

typedef pair<double, double> point;

const int kBoardSize = 15;
const double kRadius = 20;

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
    
    board = vector<vector<int> >(kBoardSize, vector<int>(kBoardSize, kNoPlayer));
    which_player = kFirstPlayer;
    
    bgm.load("epic_sax_guy.mp3");
    bgm.setLoop(true);
    bgm.play();
    bgm.setVolume(0.03f);
    
    clickSound.load("click.mp3");
    
    const double kWidth = ofGetWidth() / (kBoardSize + 1);
    const double kHeight = ofGetHeight() / (kBoardSize + 1);
    
    for (int i = 1; i <= kBoardSize; ++i) {
        for (int j = 1; j <= kBoardSize; ++j) {
            intersects.push_back(make_pair(kWidth * i, kHeight * j));
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (getWinner() != kNoPlayer) {
        cout << "Congrats to player " << getWinner() << " !" << endl;
        OF_EXIT_APP(0);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // called every frame
    
    const double kWidth = 1.0 * ofGetWidth() / (kBoardSize + 1);
    const double kHeight = 1.0 * ofGetHeight() / (kBoardSize + 1);
    
    ofSetColor(255,255,255);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(0, 0, 0);
    for(int i = 1; i <= kBoardSize; ++i) ofDrawLine(i * kWidth, 0, i * kWidth, ofGetHeight());
    for(int i = 1; i <= kBoardSize; ++i) ofDrawLine(0, i * kHeight, ofGetWidth(), i * kHeight);
    
    bool is_first_player = true;
    for(point circle: circles) {
        if (is_first_player) {
            ofSetColor(0, 100, 0);
        } else {
            ofSetColor(0, 0, 100);
        }
        ofDrawCircle(circle.first, circle.second, kRadius);
        is_first_player = !is_first_player;
    }
    
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
    
    for (int i = 0; i < intersects.size(); ++i) {
        
        point intersect = intersects[i];
        
        if (sqrt((x - intersect.first) * (x - intersect.first) + (y - intersect.second) * (y - intersect.second)) < 30) {
            circles.push_back(intersect);
            
            board[i % kBoardSize][i / kBoardSize] = which_player;
            which_player = (which_player == 1) ? 2 : 1;
            
            clickSound.play();
            clickSound.setVolume(0.8f);
            
            break;
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
