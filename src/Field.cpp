//
//  Field.cpp
//  emptyExample
//
//  Created by Luis Daniel Palacios on 4/28/12.
//  Copyright (c) 2012 luisdaniel. All rights reserved.
//

#include <iostream>

#include "Field.h"

using namespace std;


Field::Field(Shape *pShapes, int pScreenHeight)
{
	// Get the screen height
	mScreenHeight = pScreenHeight;
    
	// Get the pointer to the pieces class
	mShapes = pShapes;
    
    deletedLines = 0;
    
	//Init the board blocks with free positions
	initField();
}


void Field::initField() {
    for (int i = 0; i < FIELD_WIDTH; i++) {
        for (int j = 0; j < FIELD_HEIGHT; j++) {
            mField[i][j] = POS_FREE;
        }
    }
}


void Field::storeShape (int pX, int pY, int pShape, int pRotation) {
    // Store each block of the shape into the board
    for (int i1 = pX, i2 = 0; i1 < pX + SHAPE_BLOCKS; i1++, i2++) {
        for (int j1 = pY, j2 = 0; j1 < pY + SHAPE_BLOCKS; j1++, j2++) {
            // Store only the blocks of the shape that are not holes
            if (mShapes->getBlockType (pShape, pRotation, j2, i2) != 0)
                mField[i1][j1] = POS_FILLED;
        }
    }
}

bool Field::isGameOver() {
    //If the first line has blocks, then, game over
    for (int i = 0; i < FIELD_WIDTH; i++) {
        if (mField[i][0] == POS_FILLED) return true;
    }
    return false;
}

void Field::deleteLine(int pY) {
    // Moves all the upper lines one row down
    for (int j = pY; j > 0; j--) {
        for (int i = 0; i < FIELD_WIDTH; i++) {
            mField[i][j] = mField[i][j-1];
        }
    }
}

void Field::deletePossibleLines () {
    for (int j = 0; j < FIELD_HEIGHT; j++) {
        int i = 0;
        while (i < FIELD_WIDTH) {
            if (mField[i][j] != POS_FILLED) break;
            i++;
        }
        if (i == FIELD_WIDTH) {
            deletedLines ++;
            deleteLine(j);
        }
    }
}

bool Field::isFreeBlock (int pX, int pY) {
    if (mField[pX][pY] == POS_FREE) {
        return true;
    } else {
        return false;
    }
}


int Field::getXPosInPixels (int pPos) {
    return  ((FIELD_POSITION - (BLOCK_SIZE * (FIELD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
}


int Field::getYPosInPixels (int pPos) {
    return ((mScreenHeight - (BLOCK_SIZE * FIELD_HEIGHT)) + (pPos * BLOCK_SIZE));
}

bool Field::isPossibleMovement (int pX, int pY, int pShape, int pRotation)
{
    // Checks collision with pieces already stored in the board or the board limits
    // This is just to check the 5x5 blocks of a piece with the appropriate area in the board
    for (int i1 = pX, i2 = 0; i1 < pX + SHAPE_BLOCKS; i1++, i2++) {
        for (int j1 = pY, j2 = 0; j1 < pY + SHAPE_BLOCKS; j1++, j2++) {
            // Check if the piece is outside the limits of the board
            if (i1 < 0 || i1 > FIELD_WIDTH -1 || j1 > FIELD_HEIGHT - 1) {
                if (mShapes->getBlockType(pShape, pRotation, j2, i2) != 0) {
                    return false;
                }
            }
            // Check if the piece have collisioned with a block already stored in the map
            if (j1 >= 0) {
                if ((mShapes->getBlockType(pShape, pRotation, j2, i2) != 0) && (!isFreeBlock(i1, j1))) {
                    return false;
                }
            }
        }
    }
    // No collision
    return true;
    
}


int Field::getDeletedLines() {
    return deletedLines;
}











