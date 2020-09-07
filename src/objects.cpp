//
//  objects.cpp
//  finalProject
//
//  Created by 野沢充彦 on 2020/07/14.
//

#include "objects.h"
#include "ofApp.h"
#include "ofMain.h"

//--------------------------- object ---------------------------

void object::setup(ofVec3f pos_, int w_, int h_, int d_){
    pos = pos_;
    w = w_;
    h = h_;
    d = d_;
}

//--------------------------- block ---------------------------

void block::draw(){
    ofSetColor(0, 100, 255, 200);
    ofDrawBox(pos, w-5, h-5, d-5);
    
    
    ofNoFill();
    ofSetColor(40, 40, 40);
    ofDrawBox(pos, w-2, h-2, d-2);
    ofFill();
}

//--------------------------- outLayer ---------------------------

void outLayer::setup(int LayerSize_, int depth_){
    LayerSize = LayerSize_;
    depth = depth_;
    up = ofVec3f(0, LayerSize/2 + depth/2, -depth/2);
    down = ofVec3f(0, -(LayerSize/2 + depth/2), -depth/2);
    right = ofVec3f(LayerSize/2 + depth/2, 0, -depth/2);
    left = ofVec3f(-(LayerSize/2 + depth/2), 0, -depth/2);
    back = ofVec3f(0, 0, -(LayerSize/2 + depth/2));
    
}

void outLayer::draw(){
    ofSetColor(128, 128, 128);
    //up
    ofDrawBox(up, LayerSize+2*depth, depth, LayerSize+depth);
    //down
    ofDrawBox(down, LayerSize+2*depth, depth, LayerSize+depth);
    //right
    ofDrawBox(right, depth, LayerSize+2*depth, LayerSize+depth);
    //left
    ofDrawBox(left, depth, LayerSize+2*depth, LayerSize+depth);
    //back
    ofDrawBox(back, LayerSize+2*depth, LayerSize+2*depth, depth);
    
    ofSetColor(0, 0, 0);
    ofNoFill();  // wire frame, invalidate Fill
    ofDrawBox(0.0, 0.0, 0.0, LayerSize);
    ofFill();
}

//--------------------------- board ---------------------------

void board::draw(){
    ofSetColor(128, 128, 128, 128);
    ofVec3f pos_ = pos;
    pos_.z += d/2;
    ofDrawBox(pos_, w, h, d);

}

void board::update(float X, float Y){
    pos.x = X*0.7775;
    pos.y = Y*0.7775;
}

void board::update_gui(int boardSize_){
    w = boardSize_, h = boardSize_;
}

//--------------------------- ball ---------------------------

void ball::setup(int radius, int LayerSize){
    r = radius;
    pos = ofVec3f(0, 0, LayerSize/2-r*2);
    vel = ofVec3f(7, 7, 7);
    V = 7;
}

void ball::draw(){
    ofSetColor(250, 250, 250);
    ofDrawSphere(pos, r);
}

void ball::update(){
    // なぜかボールが壁にハマる現象が見られたのでそのための処理
    if(velPrev2.x == vel.x && velPrev1.x != vel.x) vel.x *=-1;
    if(velPrev2.y == vel.y && velPrev1.y != vel.y) vel.y *=-1;
    if(velPrev2.z == vel.z && velPrev1.z != vel.z) vel.z *=-1;
    velPrev2 = velPrev1;
    velPrev1 = vel;
    pos+=(vel*V);
}

void ball::update_gui1(int V_){
    V = V_;
}

//--------------------------------------------------------------
