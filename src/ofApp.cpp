#include "ofApp.h"


//############################### setup func #############################################

void ofApp::setup(){
    //--------------------------- gui ---------------------------
    
    gui.setup();
    gui.add(ballNum.setup("Ball Num", 1, 1, 5));
    gui.add(ballVel.setup("Ball Speed", 7, 5, 25));
    gui.add(boardSize.setup("Board Size", 200, 50, 1200));
    gui.add(validation.setup("ready"));
    gui.add(reset.setup("restart"));
    validation.addListener(this, &ofApp::guiUpdater);
    reset.addListener(this, &ofApp::resetfunc);
    
    //--------------------------- font ---------------------------
    
    font1.load("Arial.ttf", 72);
    font2.load("Arial.ttf", 24);

    //--------------------------- config ---------------------------
    
    F = false;
    TITLE_FLAG = true;
    START_FLAG = false;
    END_FLAG = false;
    CLEAR_FLAG = false;
    
    pointerX = 0;
    pointerY = 0;
    ofSetBackgroundColor(255);
    
    //--------------------------- lighting ---------------------------
    
    ofEnableDepthTest();
    ofEnableLighting();
    ofSetSmoothLighting(true);
    
    light_ambient.set(0.5, 0.5, 0.5);
    //light_diffuse.set(0.5, 0.5, 0.5);
    light_specular.set(1.0, 1.0, 1.0);
    
    light0.setAmbientColor(light_ambient);
    light0.setDiffuseColor(light_diffuse);
    light0.setSpecularColor(light_specular);
    light0.setPosition(0, 500, 2000);
    light0.enable();
    
    //--------------------------- outLayer ---------------------------
    
    OutLayer.setup(LAYER_SIZE, LAYER_DEPTH);
    
    //--------------------------- board ---------------------------

    ofVec3f boardPos = ofVec3f(0, 0, 500);
    Board.setup(boardPos, BOARD_W, BOARD_H, BOARD_D);
    
    //--------------------------- ball ---------------------------
    
    Balls.resize(0);
    BallF.resize(0);
    BallAlive.resize(0);
    guiUpdater();

    //--------------------------- block ---------------------------
    
    for(int k = 0; k < BNUM_D; k++){
        for(int j = 0; j < BNUM_H; j++){
            for(int i = 0; i < BNUM_W; i++){
                block b;
                ofVec3f pos;
                pos.x = LAYER_SIZE/2 - B_WIDTH/2 - i*B_WIDTH;
                pos.y = LAYER_SIZE/2 - B_HEIGHT/2 - j*B_HEIGHT;
                pos.z = 200 - B_DEPTH/2 - k*B_DEPTH;
                b.setup(pos, B_WIDTH, B_HEIGHT, B_DEPTH);
                blocks[i][j][k] = b;
                
                blockAlive[i][j][k] = true;
            }
        }
    }
    
    //--------------------------- camera ---------------------------
    
    camera.setPosition(0, 5, 1400);
    ofSetFullscreen(true);
    
    //--------------------------------------------------------------
}

//############################### update func #############################################

void ofApp::update(){
    //--------------------------- board gui ---------------------------
    
    if(TITLE_FLAG) { Board.update_gui(boardSize); }
    
    else{
        //--------------------------- game config ---------------------------
        
        if(!END_FLAG) {
            bool temp = true;
            for(auto alive : BallAlive) if(alive) temp = false;
            if(temp) END_FLAG = true;
        }
        
        bool temp = true;
        for(auto f : BallF) if(!f) temp = false;
        if(temp) { START_FLAG = true; }
            
        //--------------------------- board ---------------------------
        
        if(START_FLAG && !END_FLAG && !CLEAR_FLAG)Board.update(pointerX, pointerY);
        
        //--------------------------- ball ---------------------------
        
        for(int i = 0; i < Balls.size(); i++) {
            if(Balls[i].pos.z > 550) BallAlive[i] = false;
            if(BallF[i])Balls[i].update();
        }
        
        //--------------------------- boundary condition ---------------------------
            
            for(int i = 0; i < Balls.size(); i++) if(BallF[i] && BallAlive[i]) {
                boundary(i);
            }
    }
    
    //--------------------------------------------------------------------

}

//############################### draw func #############################################

void ofApp::draw(){
    //=========================== EasyCam begin ===========================
    
    camera.begin();
    
    //--------------------------- lighting ---------------------------
    
    //light0.draw();

    //--------------------------- ball ---------------------------
    
    for(int i = 0; i < Balls.size(); i++) Balls[i].draw();

    //--------------------------- outLayer ---------------------------
    
    OutLayer.draw();
    
    //--------------------------- block ---------------------------
    
    for(int k = 0; k < BNUM_D; k++){
        for(int j = 0; j < BNUM_H; j++){
            for(int i = 0; i < BNUM_W; i++){
                if(blockAlive[i][j][k])blocks[i][j][k].draw();
            }
        }
    }
    
    //--------------------------- Shooting Line  ---------------------------
    
    if(!START_FLAG && !TITLE_FLAG) beforeDraw();
    
    //--------------------------- board ---------------------------
    
    Board.draw();

    camera.end();
    //=========================== EasyCam end ===========================
    
    //--------------------------- gui ---------------------------
   
    //一度無効にしないとguiがうまく写らない
    ofDisableDepthTest();
    gui.draw();
    ofEnableDepthTest();
    
    //--------------------------- font ---------------------------
    
    if(TITLE_FLAG){
        ofSetColor(0, 0, 0);
        font1.drawString("welcom to 3D Breakout!", 350, 120);
        font2.drawString("you can change parammeter", 20, 200);
        font2.drawString("push ready to play game", 20, 250);

    }
    else if(END_FLAG){
        ofSetColor(0, 0, 0);
        font1.drawString("Game Over", 600, 120);
        font2.drawString("Push restart if you want to play", 20, 200);
    }
    else if(CLEAR_FLAG){
        ofSetColor(0, 0, 0);
        font1.drawString("Game Clear!", 600, 120);
        font2.drawString("Push restart if you want to play", 20, 200);
    }
    
     //--------------------------------------------------------------------
}

//############################### key func #############################################

void ofApp::keyPressed(int key){
    
}

//------------------------------------------------------------------------

void ofApp::keyReleased(int key){

}

//############################### mouse func #############################################

void ofApp::mouseMoved(int x, int y ){
    pointerX = ((float)mouseX-(float)ofGetWidth()/2.0) / ((float)ofGetWidth()/2.0) * 1060.0;
    pointerY = -((float)mouseY-(float)ofGetHeight()/2.0)/((float)ofGetHeight()/2.0) * 670.0;

}

//------------------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button){

}

//------------------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button){
    
}

//------------------------------------------------------------------------

void ofApp::mouseReleased(int x, int y, int button){
    if(!TITLE_FLAG && !START_FLAG) {
        for(int i = 0; i < ballNum; i++){
            if(BallF[i]) continue;
            float X = pointerX*1.1;
            float Y = pointerY*1.25;
            float Z = LAYER_SIZE/2-200-B_DEPTH/2;
            float L2 = sqrt(pow(X,2)+pow(Y,2)+pow(Z,2));
            X = (X / L2);
            Y = (Y / L2);
            Z = (Z / L2);
            Balls[i].vel = ofVec3f(X, Y, -Z);
            BallF[i] = true;
            break;
        }
    }
}

//------------------------------------------------------------------------

void ofApp::mouseEntered(int x, int y){

}

//------------------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//############################### other func #############################################

void ofApp::windowResized(int w, int h){

}

//------------------------------------------------------------------------

void ofApp::gotMessage(ofMessage msg){

}

//------------------------------------------------------------------------

void ofApp::dragEvent(ofDragInfo dragInfo){

}

//############################### original func ############################################

void ofApp::boundary(int n){

    //--------------------------- wall ---------------------------
    
    if(500 < Balls[n].pos.x+Balls[n].r|| Balls[n].pos.x-Balls[n].r < -500) Balls[n].vel.x *= -1;
    if(500 < Balls[n].pos.y+Balls[n].r|| Balls[n].pos.y-Balls[n].r < -500) Balls[n].vel.y *= -1;
    if(Balls[n].pos.z-Balls[n].r < -500) Balls[n].vel.z *= -1;

    

    //--------------------------- block ---------------------------
    bool temp = true;
    
    for(int k = 0; k < BNUM_D; k++){
        for(int j = 0; j < BNUM_H; j++){
            for(int i = 0; i < BNUM_W; i++){
                if(blockAlive[i][j][k]){
                    temp = false;
                    if(collision(blocks[i][j][k], n)) blockAlive[i][j][k] = false;
                }
            }
        }
    }
    if(temp) {
        CLEAR_FLAG = true;
    }

    //--------------------------- board ---------------------------
    
    if(495 < Balls[n].pos.z+Balls[n].r && Balls[n].pos.z+Balls[n].r < 520 &&
       Board.pos.y-Board.h/2 < Balls[n].pos.y && Balls[n].pos.y < Board.pos.y+Board.h/2 &&
       Board.pos.x-Board.w/2 < Balls[n].pos.x && Balls[n].pos.x < Board.pos.x+Board.w/2 ) Balls[n].vel.z *= -1;

    
    //-------------------------------------------------------------
    
}

//------------------------------------------------------------------------

bool ofApp::collision(block B, int i){
    // ブロックの6側面が球と領域を共有した場合、速度を変える
    
    int x1 = B.pos.x - B.w/2;
    int x2 = B.pos.x + B.w/2;
    int y1 = B.pos.y - B.h/2;
    int y2 = B.pos.y + B.h/2;
    int z1 = B.pos.z - B.d/2;
    int z2 = B.pos.z + B.d/2;
    
    float bx = Balls[i].pos.x;
    float by = Balls[i].pos.y;
    float bz = Balls[i].pos.z;
    
    bool fs = false;
    bool fb = false;
    bool fr = false;
    bool fl = false;
    bool fu = false;
    bool fd = false;
    
    // 正面、後ろ
    for(int x = x1; x <= x2; x+=5){
        for(int y = y1; y <= y2; y+=5){
            float d1 = ofDist(bx, by, bz, x, y, z1); // back
            float d2 = ofDist(bx, by, bz, x, y, z2); // straight
            if(d1 < Balls[i].r) fb = true;
            if(d2 < Balls[i].r) fs = true;
        }
    }

    // 右、左
    for(int y = y1; y <= y2; y+=5){
        for(int z = z1; z <= z2; z+=5){
            float d1 = ofDist(bx, by, bz, x1, y, z); //left
            float d2 = ofDist(bx, by, bz, x2, y, z); //right
            if(d1 < Balls[i].r) fl = true;
            if(d2 < Balls[i].r) fr = true;
        }
    }
    // 上、下
    for(int z = z1; z <= z2; z+=5){
        for(int x = x1; x <= x2; x+=5){
            float d1 = ofDist(bx, by, bz, x, y1, z); // down
            float d2 = ofDist(bx, by, bz, x, y2, z); // up
            if(d1 < Balls[i].r) fd = true;
            if(d2 < Balls[i].r) fu = true;
        }
    }

    
    if((fb && Balls[i].vel.z > 0) || (fs && Balls[i].vel.z < 0)) Balls[i].vel.z *= -1;
    if((fl && Balls[i].vel.x > 0) || (fr && Balls[i].vel.x < 0)) Balls[i].vel.x *= -1;
    if((fd && Balls[i].vel.y > 0) || (fu && Balls[i].vel.y < 0)) Balls[i].vel.y *= -1;

    
    if(fs || fb || fl || fr || fd || fu) return true;
    else return false;
    
}

//------------------------------------------------------------------------

void ofApp::beforeDraw(){
    ofSetColor(0, 0, 0);
    ofSetLineWidth(5);
    ofDrawLine(pointerX, pointerY, 200+B_DEPTH/2, 0, 0, 500);
    ofSetLineWidth(1);
}

//------------------------------------------------------------------------

void ofApp::guiUpdater(){
    if(F & TITLE_FLAG){
        for(int i = Balls.size(); i < ballNum; i++){
            ball temp;
            temp.setup(BALL_RADIUS, LAYER_SIZE);
            temp.V = ballVel;
            Balls.push_back(temp);
            BallF.push_back(false);
            BallAlive.push_back(true);
            
            Board.update_gui(boardSize);
        }
        TITLE_FLAG = false;
    }
    F = true;
}

void ofApp::resetfunc(){
    if(END_FLAG || CLEAR_FLAG) setup();
}

//#################################################################################
