#include "dennisApp.h"

//--------------------------------------------------------------
void dennisApp::setup(){
	
	/** video input */
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(VIDEO_WIDTH,VIDEO_HEIGHT);
	
    videoImg.allocate(VIDEO_WIDTH,VIDEO_HEIGHT);
	
	/** kinect init */
	kinect.init();
	//kinect.init(true);  // shows infrared instead of RGB video image
	//kinect.init(false, false);  // disable infrared/rgb video iamge (faster fps)
	kinect.setVerbose(true);
	kinect.open();
	
	kinectImg.allocate(kinect.width, kinect.height);
}

//--------------------------------------------------------------
void dennisApp::update(){
	
	/** video */
	bool bNewFrame = false;
	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();
	
	if (bNewFrame){
		videoImg.setFromPixels(vidGrabber.getPixels(), VIDEO_WIDTH,VIDEO_HEIGHT);
	}
	
	
	
	/** kinect img */
	kinect.update();
	
	// there is a new frame and we are connected
	if(kinect.isFrameNew()) {
		
		// load grayscale depth image from the kinect source
		kinectImg.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
	}
}

//--------------------------------------------------------------
void dennisApp::draw(){
	/** video */
	videoImg.draw(10,10);
	
	/** kinect */
	kinectImg.draw(660, 10, 640, 480);
	
	kinect.draw(10, 500, 320, 240);
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
