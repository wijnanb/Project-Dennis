#ifndef CALIBRATION_H
#define CALIBRATION_H 1

#include "ofxOpenCv.h"
#include "opencv.hpp"



class Calibration {
	
	public:
		Calibration();
		~Calibration();
		void grab(ofxCvColorImage* videoImg);
		bool isReady();
	void undistort(ofxCvColorImage* videoImg);
	
	int n_boards;
	int board_dt; //Wait dt frames per chessboard view 
	int board_w; 
	int board_h;
	int N;
	
	CvMat* image_points;
	CvMat* object_points;
	CvMat* point_counts;
	CvMat* intrinsic_matrix;
	CvMat* distortion_coeffs;
	
	CvPoint2D32f* corners; 
	int corner_count; 
	int successes; 
	int step, frame;
	
};

#endif