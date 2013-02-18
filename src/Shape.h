//
//  Shape.h
//  emptyExample
//
//  Created by Luis Daniel Palacios on 4/28/12.
//  Copyright (c) 2012 luisdaniel. All rights reserved.
//

#ifndef emptyExample_Shape_h
#define emptyExample_Shape_h



class Shape {
    
public:
    //Shape();
    int getBlockType(int pPiece, int pRotation, int pX, int pY);
    int getXInitialPosition(int pShape, int pRotation);
    int getYInitialPosition(int pShape, int pRotation);
};


#endif