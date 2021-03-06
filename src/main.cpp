#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}

/*
 README.mdにも書きましたがこちらにも書いておきます
 グラフィックスプログラミング最終課題です
 3Dブロック崩しを作りました
 addonはofxGuiのみ使用しました
 そのほかにフォントのデータ Arial.ttf が bin/data/Arial.ttf として入っています
 操作方法は、最初に左上のguiを操作し、パラメータを決めた後にguiのreadyボタンを押します
 パラメータはボールの数、ボールの速さ、ボードのの大きさの3つです
 その後、ボールを打つ画面に入るので、ラインをもとにボールを発射したい場所を決めます
 全てのボールを発車するとボードが動かせるようになります
 全てのブロックを壊すとクリア、全てのボールが外に出るとゲームオーバーです
 どちらかの状態でguiのrestartを押すとまたプレイできます

 当たり判定は一応バグのないようになっているかと思います
 ボールの距離感が掴みにくい、ボールを増やすと重くなるのが問題点です
 １学期間ありがとうございました
 
 */
