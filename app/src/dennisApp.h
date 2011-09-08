#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

const int VIDEO_WIDTH = 640;
const int VIDEO_HEIGHT = 480;


class dennisApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);	
	
			
		ofVideoGrabber vidGrabber;	
		ofxCvColorImage	videoImg;
	
		ofxKinect 			kinect;
		ofxKinectRecorder 	kinectRecorder;
		ofxKinectPlayer 	kinectPlayer;

		ofxCvGrayscaleImage kinectImg;
	
};

