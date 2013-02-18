#include "testApp.h"
#include <stdio.h>
#include <string>
#include <iostream>

//--------------------------------------------------------------
void testApp::setup(){
    initGame();
}

//--------------------------------------------------------------
void testApp::update(){
    
    //update screen
    //move a shape down if game is not over yet
    if (!field->isGameOver()) {
        if (!pause) {
            if (ofGetElapsedTimeMillis() - timerReset > interval) {  
                if (field->isPossibleMovement(game->mPosX, game->mPosY + 1, game->mShape, game->mRotation)) {
                    game->mPosY++;
                } else {
                    field->storeShape(game->mPosX, game->mPosY, game->mShape, game->mRotation);
                    field->deletePossibleLines ();
                    cout<<"the next shape is "<<nextShape[0]<<endl;
                    if (nextCharShape != 'e') {
                        game->createNewShape();
                        nextCharShape = 'e';
                    } else {
                        game->createNewRandomShape();
                        nextCharShape = 'e';
                    }
                }
                //timing
                timerReset = ofGetElapsedTimeMillis();
                if (score > 0 && score%4 ==0 && !intervalChange) {
                    interval *=.9;
                    cout<<"interval = "<<interval<<endl;
                    intervalChange = true;
                }
                if (score > 0 && score%4 > 0) {
                    intervalChange = false;
                }
            }
            
        }
    }
    //printNextShapeArray();

}

//--------------------------------------------------------------
void testApp::draw(){
    if (!field->isGameOver()) {
        clearScreen();
        game->drawScene();
    } else {
        clearScreen();
        game->drawScene();
        game->drawGameOver();
    }
    drawPoints();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    cout<<key<<endl;
    
    
    if (key == 112) {
        if (pause) {
            pause = false;
        } else {
            pause = true;
        }
    }
    
    if (!pause) {
        if (key == 122) {
            game->setNewNextShape('z');
            nextCharShape = 'z';
            //nextShape[0] = 'z';
            //nextShapeIndex ++;
        }
        if (key == 116) {
            game->setNewNextShape('t');
            nextCharShape = 'z';
            //nextShape[0] = 't';
            //nextShapeIndex ++;
        }
        if (key == 115) {
            game->setNewNextShape('s');
            nextCharShape = 'z';
            //nextShape[0] = 's';
            //nextShapeIndex ++;
        }
        if (key == 108) {
            game->setNewNextShape('l');
            nextCharShape = 'z';
            //nextShape[0] = 'l';
            //nextShapeIndex ++;
        }
        if (key == 106) {
            game->setNewNextShape('j');
            nextCharShape = 'z';
            //nextShape[0] = 'j';
            //nextShapeIndex ++;
        }
        if (key == 111) {
            game->setNewNextShape('o');
            nextCharShape = 'z';
            //nextShape[0] = 'o';
            //nextShapeIndex ++;
        }
        if (key == 105) {
            game->setNewNextShape('i');
            nextCharShape = 'z';
            //nextShape[0] = 'i';
            //nextShapeIndex ++;
        }
        
        if (key == 13) {
            if (field->isGameOver()) {
                game->Game::~Game();
                initGame();
            }
        }
        if (key == 358) {
            //move right
            if (field->isPossibleMovement (game->mPosX + 1, game->mPosY, game->mShape, game->mRotation)) {
                game->mPosX++;
            }
        }
        if (key == 356) {
            //move left
            if (field->isPossibleMovement (game->mPosX - 1, game->mPosY, game->mShape, game->mRotation)) {
                game->mPosX--;
            }
        }
        if (key == 359) {
            //move down
            if (field->isPossibleMovement (game->mPosX, game->mPosY + 1, game->mShape, game->mRotation)) {
                game->mPosY++;	
            }
        }
        if (key == 357) {
            //move up
            if (field->isPossibleMovement (game->mPosX, game->mPosY, game->mShape, (game->mRotation + 1) % 4)) {
                game->mRotation = (game->mRotation + 1) % 4;
            }
        }
        if (key == 32) {
            //spacebar, drop
            while (field->isPossibleMovement(game->mPosX, game->mPosY, game->mShape, game->mRotation)) { 
                game->mPosY++; 
            }
            field->storeShape(game->mPosX, game->mPosY - 1, game->mShape, game->mRotation);
            field->deletePossibleLines ();
            if (nextCharShape != 'e') {
                game->createNewShape();
                nextCharShape = 'e';
            } else {
                game->createNewRandomShape();
                nextCharShape = 'e';
            }
            
            /*
            if (nextShape[0] != 'e') {
                game->createNewShape(nextShape[0]);
                shiftNextShapeArray();
                cout<<nextShapeIndex<<endl;
            } else {
                game->createNewShape();
            }*/

        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}



void testApp::wait(float seconds) {
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}
}

void testApp::clearScreen() {
    ofSetColor(0);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
}


void testApp::drawPoints() {
    string lines= "Score: " + ofToString(field->getDeletedLines());
    ofSetColor(255, 255, 0);
    verdana18.drawString(lines, FIELD_POSITION+(BLOCK_SIZE*(FIELD_WIDTH/2))-verdana18.stringWidth("Score: "), mScreenHeight-(BLOCK_SIZE*FIELD_HEIGHT)-20);
    score = field->getDeletedLines();
}



void testApp::shiftNextShapeArray() {
    for (int i = 0; i < 9; i++) {
        nextShape[i] = nextShape[i+1];
    }
    nextShape[9] = 'e';
    nextShapeIndex --;
}
    

void testApp::printNextShapeArray() {
    for (int i = 0; i < 10; i++) {
        cout<<nextShape[i]<<" ";
    }
    cout<<endl;
}


void testApp::initGame() {
    mScreenHeight = ofGetHeight();
    Shape shapes;
    
    
    
    field = new Field(&shapes, mScreenHeight);
    game = new Game(field, &shapes, mScreenHeight);
    
    
    //stuff that takes care of the queue of incoming shapes
    for (int i = 0 ; i < 10; i++) {
        nextShape[i] = 'e';
    }
    nextShapeIndex = 0;
    
    
    interval = 1000;
    timerReset = ofGetElapsedTimeMillis();
    intervalChange = false;
    
    verdana18.loadFont("verdana.ttf", 18);
    
    score = 0;
    pause = false;
    newShapeAvailable = false;
    game->setNewNextShape();
}

