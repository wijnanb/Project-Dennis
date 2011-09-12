#include "ofMain.h"
#include "dennisApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1600,768, OF_WINDOW);			// <-------- setup the GL contex
	glEnable(GL_DEPTH_TEST);
	ofSetFrameRate(30);
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new dennisApp());
}
