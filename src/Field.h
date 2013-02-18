//
//  Field.h
//  emptyExample
//
//  Created by Luis Daniel Palacios on 4/28/12.
//  Copyright (c) 2012 luisdaniel. All rights reserved.
//

#ifndef emptyExample_Field_h
#define emptyExample_Field_h


#include "Shape.h"

#define FIELD_LINE_WIDTH 6          // Width of each of the two lines that delimit the board
#define BLOCK_SIZE 20               // Width and Height of each block of a piece
#define FIELD_POSITION 130          // Center position of the board from the left of the screen
#define FIELD_WIDTH 10              // Field width in blocks
#define FIELD_HEIGHT 20             // Field height in blocks
#define MIN_VERTICAL_MARGIN 20      // Minimum vertical margin for the field limit
#define MIN_HORIZONTAL_MARGIN 20    // Minimum horizontal margin for the field limit
#define SHAPE_BLOCKS 5              // Number of horizontal and vertical blocks of a matrix piece

class Field
{
public:
    
    Field(Shape *pShapes, int pScreenHeight);
    
    int getXPosInPixels(int pPos);
    int getYPosInPixels(int pPos);
    bool isFreeBlock(int pX, int pY);
    bool isPossibleMovement(int pX, int pY, int pShapes, int pRotation);
    void storeShape(int pX, int pY, int pShapes, int pRotation);
    void deletePossibleLines();
    bool isGameOver();
    int getDeletedLines();      //return number of deleted lines.
    int deletedLines;           //number of deleted lines accumulated.
    
private:
    
    enum { POS_FREE, POS_FILLED };          // POS_FREE = free position of the field; POS_FILLED = filled position of the board
    int mField [FIELD_WIDTH][FIELD_HEIGHT]; // field that contains the pieces
    Shape *mShapes;
    int mScreenHeight;
    
    void initField();
    void deleteLine (int pY);
};



#endif
