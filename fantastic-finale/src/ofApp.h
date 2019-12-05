#pragma once

#include "ofMain.h"

#include "gomoku.hpp"
#include "gomoku-ai.hpp"

// external libraries
#include "ofxButtons.h"
#include "ofxNotifications.h"

const double kRadius = 20;
const double kMargin = 100;
const string kSavedGames = "savedgames";

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
        void draw();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void SetupUI();
        void SetupBackground();
        void SetupButtons();
        void SetupSound();
        void SetupBoard();
    
        void DrawBackground();
        void DrawBoard();
        void DrawButtons();
        void DrawStones();
        
        void GetAIMove();
        void SetAIMode();
        void SetReplayMode();
        void SaveGame();
        void ReplayGame();
        void ShowPastMatches();
    
        double width;
        double height;
        
        ofImage background;
        ofImage menubackground;
    
        ofSoundPlayer bgm;
        ofSoundPlayer clickSound;
        ofSoundPlayer restartSound;
        ofSoundPlayer undoSound;
        ofSoundPlayer saveSound;
        ofSoundPlayer replaySound;
    
        SimpleButton restart_button = SimpleButton("", 0, 0);
        SimpleButton undo_button = SimpleButton("", 0, 0);
        SimpleButton save_button = SimpleButton("", 0, 0);
        SimpleButton replay_button = SimpleButton("", 0, 0);
        SimpleButton ai_button = SimpleButton("", 0, 0);
        SimpleButton exit_button = SimpleButton("", 0, 0);
        SimpleButton show_matches_button = SimpleButton("", 0, 0);
    
        ofFile fout;
        ofFile fin;
    
};
