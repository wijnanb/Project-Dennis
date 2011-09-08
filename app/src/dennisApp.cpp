#include "dennisApp.h"

//--------------------------------------------------------------
void dennisApp::setup(){
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
	
    colorImg.allocate(320,240);
}

//--------------------------------------------------------------
void dennisApp::update(){
	bool bNewFrame = false;
	
	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();
	
	if (bNewFrame){
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
	}
	
}

//--------------------------------------------------------------
void dennisApp::draw(){
	ofSetHexColor(0xffffff);
	colorImg.draw(20,20);
}

//--------------------------------------------------------------
void dennisApp::keyPressed(int key){

}

//--------------------------------------------------------------
void dennisApp::keyReleased(int key){

}

//--------------------------------------------------------------
void dennisApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void dennisApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void dennisApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void dennisApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void dennisApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void dennisApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void dennisApp::dragEvent(ofDragInfo dragInfo){ 

}
