
#include "calibration.h"


Calibration::Calibration() {
	n_boards = 10;
	board_dt = 20;
	board_w = 11;  // -1 doen 
	board_h = 7; // -1 doen
	N = board_w * board_h;
	
	image_points = cvCreateMat(n_boards*N,2,CV_32FC1);
	object_points = cvCreateMat(n_boards*N,3,CV_32FC1);
	point_counts = cvCreateMat(n_boards,1,CV_32SC1);
	intrinsic_matrix = cvCreateMat(3,3,CV_32FC1);
	distortion_coeffs = cvCreateMat(5,1,CV_32FC1);
	
	corners = new CvPoint2D32f[ N ];  
	successes = 0; 
	frame = 0;
	step = 0;
}

bool Calibration::isReady() {
	return (successes >= n_boards);
}

void Calibration::grab(ofxCvColorImage* image) {
	
	CvSize board_sz = cvSize( board_w, board_h ); 
	
	CvSize size = cvSize( image->width, image->height);
	IplImage* gray_image = cvCreateImage(size, IPL_DEPTH_8U, 1);
	
	
		int found = cvFindChessboardCorners(image->getCvImage(), board_sz, corners, &corner_count, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS | CV_CALIB_CB_NORMALIZE_IMAGE);

		printf("found %d %d\n", found, corner_count);

		cvCvtColor(image->getCvImage(), gray_image, CV_BGR2GRAY); 
		cvFindCornerSubPix(gray_image, corners, corner_count,cvSize(11,11),cvSize(-1,-1), cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));

		cvDrawChessboardCorners(image->getCvImage(), board_sz, corners, corner_count, found); 
		cvShowImage( "Calibration", image->getCvImage() );

		if( corner_count == N ) {
			step = successes*N; 
			for( int i=step, j=0; j<N; ++i,++j ) {
				CV_MAT_ELEM(*image_points, float,i,0) = corners[j].x; 
				CV_MAT_ELEM(*image_points, float,i,1) = corners[j].y; 
				CV_MAT_ELEM(*object_points,float,i,0) = j/board_w; 
				CV_MAT_ELEM(*object_points,float,i,1) = j%board_w; 
				CV_MAT_ELEM(*object_points,float,i,2) = 0.0f;
			} 
			CV_MAT_ELEM(*point_counts, int,successes,0) = N; 
			successes++;
		}  
	
	
	if ( isReady() ) {
	
		printf( "ready\n" );
		
		//ALLOCATE MATRICES ACCORDING TO HOW MANY CHESSBOARDS FOUND 
		CvMat* object_points2 = cvCreateMat(successes*N,3,CV_32FC1); 
		CvMat* image_points2	= cvCreateMat(successes*N,2,CV_32FC1); 
		CvMat* point_counts2	= cvCreateMat(successes,1,CV_32SC1); //TRANSFER THE POINTS INTO THE CORRECT SIZE MATRICES 

		
		for(int i = 0; i<successes*N; ++i) {
			CV_MAT_ELEM( *image_points2, float, i, 0) = CV_MAT_ELEM( *image_points, float, i, 0);
			CV_MAT_ELEM( *image_points2, float,i,1) = CV_MAT_ELEM( *image_points, float, i, 1);
			CV_MAT_ELEM(*object_points2, float, i, 0) = CV_MAT_ELEM( *object_points, float, i, 0) ;
			CV_MAT_ELEM( *object_points2, float, i, 1) = CV_MAT_ELEM( *object_points, float, i, 1) ;
			CV_MAT_ELEM( *object_points2, float, i, 2) = CV_MAT_ELEM( *object_points, float, i, 2) ;
		} 
		
		for(int i=0; i<successes; ++i){ //These are all the same number
			CV_MAT_ELEM( *point_counts2, int, i, 0) = CV_MAT_ELEM( *point_counts, int, i, 0);
		}
		
		// At this point we have all of the chessboard corners we need. // Initialize the intrinsic matrix such that the two focal // lengths have a ratio of 1.0 //
		CV_MAT_ELEM( *intrinsic_matrix, float, 0, 0 ) = 1.0f; 
		CV_MAT_ELEM( *intrinsic_matrix, float, 1, 1 ) = 1.0f;	
		
		//CALIBRATE THE CAMERA! 
		cvCalibrateCamera2(object_points2, image_points2, point_counts2, size, intrinsic_matrix, distortion_coeffs, NULL, NULL, CV_CALIB_ZERO_TANGENT_DIST | CV_CALIB_FIX_INTRINSIC);
		// SAVE THE INTRINSICS AND DISTORTIONS 
//		cvSave(“Intrinsics.xml”,intrinsic_matrix); 
//		cvSave(“Distortion.xml”,distortion_coeffs);
	}
	
	cvReleaseImage(&gray_image);
}

void Calibration::undistort(ofxCvColorImage *image) {
	
	CvSize size = cvSize( image->width, image->height);
	// Build the undistort map that we will use for all // subsequent frames. // 
	IplImage* mapx = cvCreateImage( size, IPL_DEPTH_32F, 1 ); 	
	IplImage* mapy = cvCreateImage( size, IPL_DEPTH_32F, 1 ); 
	cvInitUndistortMap(intrinsic_matrix, distortion_coeffs, mapx, mapy); 
	// Just run the camera to the screen, now showing the raw and // the undistorted image. // 
	
	IplImage *t = cvCloneImage(image->getCvImage()); 
	IplImage *dest = cvCloneImage(image->getCvImage());
	
	cvRemap( t, dest, mapx, mapy ); 
	cvReleaseImage(&t); 
	cvShowImage("Undistorted", dest);	
	cvReleaseImage(&dest);
	 
}
	
Calibration::~Calibration() {
	cvReleaseMat(&object_points); 
	cvReleaseMat(&image_points); 
	cvReleaseMat(&point_counts);
}

