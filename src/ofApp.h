#pragma once

#include "ofMain.h"
#include "objects.h"
#include "ofxGui.h"



class ofApp : public ofBaseApp{
    private:
        

	public:
    //########################### method ###########################

    //--------------------------- default --------------------------
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
    
    //--------------------------- original --------------------------

    void boundary(int n);
    bool collision(block Block, int i);
    void beforeDraw();
    void guiUpdater();
    void resetfunc();
    

    //########################### variable ###########################

    //--------------------------- gui --------------------------
    // using addon
    
    ofxPanel gui;
    ofxIntSlider ballNum;
    ofxIntSlider ballVel;
    ofxIntSlider boardSize;
    ofxButton validation;
    ofxButton reset;
    
    //--------------------------- font --------------------------
    
    ofTrueTypeFont font1;
    ofTrueTypeFont font2;
    
        
    //--------------------------- camera --------------------------
    
    ofEasyCam camera;
    
    //--------------------------- lighting --------------------------

    ofLight light0;
    ofFloatColor light_ambient, light_diffuse, light_specular;
    
    
    //--------------------------- outLyer --------------------------

    const static int LAYER_SIZE = 1000;
    const static int LAYER_DEPTH = 50;
    
    outLayer OutLayer;

    //--------------------------- block --------------------------

    static const int BNUM_W = 5;
    static const int BNUM_H = 10;
    static const int BNUM_D = 5;
    
    static const int B_WIDTH = LAYER_SIZE / BNUM_W;  // 200
    static const int B_HEIGHT = LAYER_SIZE / BNUM_H;  // 100
    static const int B_DEPTH = B_HEIGHT;  // 100
    
    block blocks[BNUM_W][BNUM_H][BNUM_D];
    bool blockAlive[BNUM_W][BNUM_H][BNUM_D];
    
    //--------------------------- board --------------------------
    
    static const int BOARD_W = 200;
    static const int BOARD_H = 200;
    static const int BOARD_D = 20;
    board Board;
    
    //--------------------------- ball --------------------------

    static const int BALL_RADIUS = 30;

    vector<ball> Balls;
    vector<bool> BallF;
    vector<bool> BallAlive;
    
    //--------------------------- game config --------------------------

    bool F;
    bool TITLE_FLAG;
    bool START_FLAG;
    bool END_FLAG;
    bool CLEAR_FLAG;
    
    float pointerX;
    float pointerY;
    
    
    
    

    
};
