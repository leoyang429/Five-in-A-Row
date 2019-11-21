#include "ofApp.h"

typedef pair<double, double> pdd;

const int kBoardSize = 15;
const double kRadius = 20;

vector<pdd> intersects;
vector<pdd> circles;

//--------------------------------------------------------------
void ofApp::setup(){
// called only once
    // font.load()
    
    mySound.load("epic_sax_guy.mp3");
    mySound.play();
    mySound.setVolume(0.05f);
    
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
// called continuously overtime
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    const double kWidth = 1.0 * ofGetWidth() / (kBoardSize + 1);
    const double kHeight = 1.0 * ofGetHeight() / (kBoardSize + 1);
    
    ofSetColor(255,255,255);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(0, 0, 0);
    for(int i = 1; i <= kBoardSize; ++i) ofDrawLine(i * kWidth, 0, i * kWidth, ofGetHeight());
    for(int i = 1; i <= kBoardSize; ++i) ofDrawLine(0, i * kHeight, ofGetWidth(), i * kHeight);
    
    bool is_first_player = true;
    for(pdd circle: circles) {
        if (is_first_player) {
            ofSetColor(0, 100, 0);
        } else {
            ofSetColor(0, 0, 100);
        }
        ofDrawCircle(circle.first, circle.second, kRadius);
        is_first_player = !is_first_player;
    }

    /*
    ofFill();
    ofSetColor(255, 255, 255, 255); // fill color
    ofDrawRectangle(300, 300, 300, 200);
    ofNoFill();
    ofSetColor(255, 0, 0, 255); // contour (stroke) color
    ofDrawRectangle(500, 500, 300, 200);
    
    ofNoFill();
    
// called on every frame
// relative to the center of rectangle
    // don't hard code!!
    ofDrawRectangle(ofGetWidth()/2, ofGetHeight()/2, 300, 200);
    
    ofDrawLine(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2+300, ofGetHeight()/2+200);
    
    ofDrawIcoSphere(300, 300, 75);
    
    //ofDrawSphere(300, 300, 75);
    
    ofDrawLine(30, 30, 200, 200);
    
    //ofFill();
    
    cam.begin();
    
    ofDrawRectangle(0, 0, 300, 200); // set z to 0
    
    ofDrawBox(300, 300, 50, 200, 500, 300);
    
    cam.end();
    
    ofDrawBitmapString("hello world", 600, 300);
    
    // font.drawString();
    // draw image
    
     
    */
     
     
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
        pdd intersect = intersects[i];
        if (sqrt((x - intersect.first) * (x - intersect.first) + (y - intersect.second) * (y - intersect.second)) < 30) {
            circles.push_back(intersect);
            cout<<"you've clicked on the "<<i<<"th point"<<endl;
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
