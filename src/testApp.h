#pragma once

#include "ofMain.h"
#include "Shape.h"
#include "Game.h"
#include "Field.h"
#include <time.h>
#include "ofTrueTypeFont.h"
#include <iostream>

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    void wait(float seconds);
    void clearScreen();
    void drawPoints();
    void initGame();
    
    
    ofTrueTypeFont verdana18;
    int mScreenHeight;
    float interval;
    int timerReset;
    int score;
    bool intervalChange;
    
    // Pieces
    //Shape* shapes;
    // Field
    Field* field;//(&mShapes, mScreenHeight);
    // Game
    Game* game;
    
    
    //stuff that takes care of the next shape incoming from kinect
    void shiftNextShapeArray();
    void printNextShapeArray();
    int nextShapeIndex;
    char nextShape[10];
    char nextCharShape;
    bool newShapeAvailable;
    
    bool pause;
    
    
    
    
		
};
