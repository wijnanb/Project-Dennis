#include "dennisApp.h"

//--------------------------------------------------------------
void dennisApp::setup(){
	
	frameCnt = 0;
	
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
	kinectRGBImg.allocate(kinect.width, kinect.height);
	
	pointCloudRotationY = 180;
	
	cvNamedWindow( "Calibration", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "Undistorted", CV_WINDOW_AUTOSIZE);
	calibration = new Calibration();
}

//--------------------------------------------------------------
void dennisApp::update(){
	frameCnt++;
	
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
		kinectRGBImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
	}

	if ( frameCnt % 30 == 0 && !calibration->isReady() ) {
		calibration->grab(&kinectRGBImg);
	}
	
	if( calibration->isReady() ) {
		calibration->undistort(&kinectRGBImg);
	}
	
	//delete &videoImg;
}

//--------------------------------------------------------------
void dennisApp::draw(){
	ofSetColor(255, 255, 255);
	
	/** video */
	videoImg.draw(10,10);
	
	/** kinect */
	kinectImg.draw(660, 10, 640, 480);
	kinect.draw(10, 500, 320, 240);
	
	//drawPointCloud();
}


void dennisApp::drawPointCloud() {
	ofSetColor(255, 255, 255);
	
	
	ofTranslate( 800, 400, 0);
	ofScale(400, 400, 400);
	int w = 640;
	int h = 480;
	ofRotateY(pointCloudRotationY);
	
	glBegin(GL_POINTS);
	int step = 1;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect.getWorldCoordinateFor(x, y);
			ofColor color = kinect.getCalibratedColorAt(x,y);
			glColor3ub((unsigned char)color.r,(unsigned char)color.g,(unsigned char)color.b);
			glVertex3f(cur.x, cur.y, cur.z);
			
			
		}
	}
	
	ofPixels apenkop;
	ofLoadImage( apenkop, "monkeyfarts/RGBjpg0013.jpg");
	
	ofPixels apenkopZ;
	ofLoadImage( apenkopZ, "monkeyfarts/Zjpg0013.jpg");
	
	
	step = 1;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			
			ofColor color = apenkop.getColor(x,y);
			if(apenkopZ.getColor(x,y).r!=255) {
			double z = apenkopZ.getColor(x,y).r / 255.0 + 0.50;
			
			ofVec3f cur = kinect.getCalibration().getWorldCoordinateFor(x, y, z);
			
			glColor3ub((unsigned char)color.r,(unsigned char)color.g,(unsigned char)color.b);
			glVertex3f(cur.x, cur.y, cur.z);
			}
		}
	}
	
	/*
	step = 1;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			 ofVec3f cur = kinect.getCalibration().getWorldCoordinateFor(x, y, 0.1);
			 ofColor color = ofColor(255,0,0);
			 glColor3ub((unsigned char)color.r,(unsigned char)color.g,(unsigned char)color.b);
			 glVertex3f(cur.x, cur.y, cur.z);
			 
			 cur = kinect.getCalibration().getWorldCoordinateFor(x, y, 1.0);
			 color = ofColor(0,255,0);
			 glColor3ub((unsigned char)color.r,(unsigned char)color.g,(unsigned char)color.b);
			 glVertex3f(cur.x, cur.y, cur.z);
		}
	}
	*/
	glEnd();
}


//--------------------------------------------------------------
void dennisApp::keyPressed(int key){

}

//--------------------------------------------------------------
void dennisApp::keyReleased(int key){

}

//--------------------------------------------------------------
void dennisApp::mouseMoved(int x, int y ){
	pointCloudRotationY = x;
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
