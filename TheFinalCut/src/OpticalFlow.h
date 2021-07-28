#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

using namespace glm;
using namespace cv;

class OpticalFlow {
    
public:
    void setup();
    ofPoint update();
//    void draw();

    ofVideoGrabber video;
    bool calculatedFlow;

    ofxCvColorImage currentColor;        //First and second original images
    ofxCvGrayscaleImage gray1, gray2;    //Decimated grayscaled images
    ofxCvFloatImage flowX, flowY;        //Resulted optical flow in x and y axes
    
    float sumX, sumY, avgX, avgY;
    int numOfEntries;
    ofPoint movement; 
//    float phase;
};
