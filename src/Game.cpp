//
//  Game.cpp
//  emptyExample
//
//  Created by Luis Daniel Palacios on 4/28/12.
//  Copyright (c) 2012 luisdaniel. All rights reserved.
//

#include <iostream>
#include "Game.h"


Game::Game(Field *pField, Shape *pShapes, int pScreenHeight) 
{
	mScreenHeight = pScreenHeight;
    
	// Get the pointer to the Board and Pieces classes
	mField = pField;
	mShapes = pShapes;
    
    ///text stuff
    ofTrueTypeFont::setGlobalDpi(72);
    verdana32.loadFont("verdana.ttf", 32);
    
	// Game initialization
    gamePoints = 0;
	initGame ();
}


int Game::getRand (int pA, int pB) {
    return rand()%(pB-pA+1)+pA;
}


void Game::initGame() {
    // Init random numbers
    srand ((unsigned int) time(NULL));
    
    // First piece
    mShape = getRand (0, 6);
    mRotation       = getRand (0, 3);
    mPosX           = (FIELD_WIDTH / 2) + mShapes->getXInitialPosition (mShape, mRotation);
    mPosY           = mShapes->getYInitialPosition (mShape, mRotation);
    
    //  Next piece
    mNextShape      = getRand (0, 6);
    mNextRotation   = getRand (0, 3);
    mNextPosX       = FIELD_WIDTH + 5;
    mNextPosY       = 5;
}


void Game::createNewShape(char t) {
    //new piece
    mShape = mNextShape;
    mRotation = mNextRotation;
    mPosX = (FIELD_WIDTH / 2) + mShapes->getXInitialPosition (mShape, mRotation);
    mPosY = mShapes->getYInitialPosition (mShape, mRotation);
    
    switch (t) {
        case 'z':
            mNextShape = 4;
            break;
        case 's':
            mNextShape = 5;
            break;
        case 't':
            mNextShape = 6;
            break;
        case 'l':
            mNextShape = 2;
            break;
        case 'j':
            mNextShape = 3;
            break;
        case 'o':
            mNextShape = 0;
            break;
        case 'i':
            mNextShape = 1;
            break;
        default:
            break;
    }
    cout<<mNextShape<<endl;
    // Random next piece
    //mNextShape      = getRand (0, 6);
    mNextRotation   = getRand (0, 3);
}

void Game::createNewShape() {
    //new piece
    mShape = mNextShape;
    mRotation = mNextRotation;
    mPosX = (FIELD_WIDTH / 2) + mShapes->getXInitialPosition (mShape, mRotation);
    mPosY = mShapes->getYInitialPosition (mShape, mRotation);
    
    // Random next piece
    //mNextShape      = getRand (0, 6);
    //mNextRotation   = getRand (0, 3);
}


void Game::createNewRandomShape() {
    //new piece
    mShape = mNextShape;
    mRotation = mNextRotation;
    mPosX = (FIELD_WIDTH / 2) + mShapes->getXInitialPosition (mShape, mRotation);
    mPosY = mShapes->getYInitialPosition (mShape, mRotation);
    
    // Random next piece
    mNextShape      = getRand (0, 6);
    mNextRotation   = getRand (0, 3);
}


void Game::drawShape(int pX, int pY, int pShape, int pRotation) {    
    // Obtain the position in pixel in the screen of the block we want to draw
    int mPixelsX = mField->getXPosInPixels(pX);
    int mPixelsY = mField->getYPosInPixels(pY);
    
    // Travel the matrix of blocks of the piece and draw the blocks that are filled
    for (int i = 0; i < SHAPE_BLOCKS; i++) {
        for (int j = 0; j < SHAPE_BLOCKS; j++) {
            // Get the type of the block and draw it with the correct color
            switch (mShapes->getBlockType(pShape, pRotation, j, i))
			{
				case 1: ofSetColor(0, 255, 0); break;	// For each block of the piece except the pivot
				case 2: ofSetColor(0, 0, 255); break;
                default: break; // For the pivot
			}
            if (mShapes->getBlockType (pShape, pRotation, j, i) != 0) {
                //ofSetColor(255, 0, 0);
                ofRect(mPixelsX+i*BLOCK_SIZE, mPixelsY+j*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
            }
        }
    }
}

void Game::drawField() {
    // Calculate the limits of the board in pixels
    int mX1 = FIELD_POSITION - (BLOCK_SIZE * (FIELD_WIDTH / 2)) - 1;
    int mX2 = FIELD_POSITION + (BLOCK_SIZE * (FIELD_WIDTH / 2));
    int mY = mScreenHeight - (BLOCK_SIZE * FIELD_HEIGHT);
    
    // Check that the vertical margin is not to small
    //assert (mY > MIN_VERTICAL_MARGIN);
    
    // Rectangles that delimits the board
    ofSetColor(0, 0, 255);
    ofRect(mX1-FIELD_LINE_WIDTH, mY, FIELD_LINE_WIDTH, mScreenHeight);
    ofRect(mX2, mY, FIELD_LINE_WIDTH, mScreenHeight);
    
    // Check that the horizontal margin is not to small
    //assert (mX1 > MIN_HORIZONTAL_MARGIN);
    
    // Drawing the blocks that are already stored in the board
    mX1 += 1;
    for (int i = 0; i < FIELD_WIDTH; i++)
    {
        for (int j = 0; j < FIELD_HEIGHT; j++)
        {
            // Check if the block is filled, if so, draw it
            if (!mField->isFreeBlock(i, j)) {
                ofSetColor(255, 0, 0);
                ofRect( mX1 + i * BLOCK_SIZE, mY+j*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
            }
        }
    }
}

void Game::drawScene () {
    drawField(); // Draw the delimitation lines and blocks stored in the board
    drawShape(mPosX, mPosY, mShape, mRotation);                    // Draw the playing piece
    drawShape(mNextPosX, mNextPosY, mNextShape, mNextRotation);    // Draw the next piece
}



void Game::drawGameOver() {
    ofSetColor(255, 255, 0);
    verdana32.drawString("Game Over :(", FIELD_POSITION - verdana32.stringWidth("Game Over")/2, mScreenHeight - (BLOCK_SIZE * FIELD_HEIGHT)/2);
}


void Game::setNewNextShape(char t) {
    switch (t) {
        case 'z':
            mNextShape = 4;
            break;
        case 's':
            mNextShape = 5;
            break;
        case 't':
            mNextShape = 6;
            break;
        case 'l':
            mNextShape = 2;
            break;
        case 'j':
            mNextShape = 3;
            break;
        case 'o':
            mNextShape = 0;
            break;
        case 'i':
            mNextShape = 1;
            break;
        default:
            break;
    }
    mNextRotation   = getRand (0, 3);
}

void Game::setNewNextShape() {
    mNextShape = getRand(0,6);
    mNextRotation   = getRand (0, 3);
}

char Game::getNextShape() {
    switch (mNextShape) {
        case 4:
            return 'z';
            break;
        case 5:
            return 's';
            break;
        case 6:
            return 't';
            break;
        case 2:
            return 'l';
            break;
        case 3:
            return 'j';
            break;
        case 0:
            return 'o';
            break;
        case 1:
            return 'i';
            break;
        default:
            return 'e';
            break;
    }
}




Game::~Game() { }








