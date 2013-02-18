//
//  Game.h
//  emptyExample
//
//  Created by Luis Daniel Palacios on 4/28/12.
//  Copyright (c) 2012 luisdaniel. All rights reserved.
//

#ifndef emptyExample_Game_h
#define emptyExample_Game_h


#include "Field.h"
#include "Shape.h"
//#include "IO.h"
#include <time.h>
#include "ofMain.h"

//#define WAIT_TIME 700 

class Game
{
public:
    
    Game(Field *pField, Shape *pShapes, int pScreenHeight);
    ~Game();
    
    void drawScene();
    void createNewShape(char t);
    void createNewShape();
    void drawGameOver();
    void setNewNextShape(char t);
    void setNewNextShape();
    char getNextShape();
    void createNewRandomShape();
    
    int mPosX, mPosY;               // Position of the piece that is falling down
    int mShape, mRotation;          // Kind and rotation the piece that is falling down
    int gamePoints;                 //score
    
    
    ofTrueTypeFont verdana32;
    
    
    
private:
    
    int mScreenHeight;              // Screen height in pixels
    int mNextPosX, mNextPosY;       // Position of the next piece
    int mNextShape, mNextRotation;  // Kind and rotation of the next piece
    
    Field *mField;
    Shape *mShapes;
    
    int getRand (int pA, int pB);
    void initGame();
    void drawShape(int pX, int pY, int pShape, int pRotation);
    void drawField();
};


#endif
