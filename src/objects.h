//
//  objects.h
//  finalProject
//
//  Created by 野沢充彦 on 2020/07/14.
//

#ifndef objects_hpp
#define objects_hpp

#include <stdio.h>
#include "ofMain.h"

//--------------------------- object ---------------------------

class object{
public:
    ofVec3f pos;
    ofVec3f vel;
    ofVec3f velPrev1;
    ofVec3f velPrev2;
    
    int w;
    int h;
    int d;

    
    void setup(ofVec3f pos_, int w_, int h_, int d_);
    void draw();
    void update();

    
    
};

//--------------------------- block ---------------------------

class block : public object{
public:
    void draw();

};

//--------------------------- outLayer ---------------------------

class outLayer {
public:
    int depth;
    int LayerSize;
    ofVec3f up;
    ofVec3f down;
    ofVec3f right;
    ofVec3f left;
    ofVec3f back;
    
    
    
    void draw();
    void setup(int LayerSize_, int depth_);
    
    
};

//--------------------------- board ---------------------------

class board : public object{
public:
    void draw();
    void update(float X, float Y);
    void update_gui(int boardSize_);
    
    
};

//--------------------------- ball ---------------------------

class ball : public object{
public:
    int r;
    int V;
    
    void setup(int radius, int LayerSize);
    void draw();
    void update();
    void update_gui1(int V_);
    
};

#endif /* objects_h */

//--------------------------------------------------------------
