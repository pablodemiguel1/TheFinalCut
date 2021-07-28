#include "OpticalFlow.h"

//--------------------------------------------------------------
void OpticalFlow::setup()
{
//    Code borrowed from opticalFlow, Computer Vision week 2.
    ofSetFrameRate(60);
    video.setDeviceID(0);
    video.setDesiredFrameRate(60);
    video.initGrabber(640, 480);
    calculatedFlow = false;
    movement = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
//    phase = 0;
}

//--------------------------------------------------------------
ofPoint OpticalFlow::update(){
//    Code borrowed from opticalFlow, Computer Vision week 2. Elements in the draw function have been moved to the update function.
    video.update();        //Decode the new frame if needed

    if ( video.isFrameNew() )
    {
        if ( gray1.bAllocated ) {
            gray2 = gray1;
            calculatedFlow = true;
        }

        //Convert to ofxCv images
        ofPixels & pixels = video.getPixels();
        currentColor.setFromPixels( pixels );

        float decimate = 0.25;              //Decimate images to 25% (makes calculations faster + works like a blurr too)
        ofxCvColorImage imageDecimated1;
        imageDecimated1.allocate( currentColor.width * decimate, currentColor.height * decimate );
        imageDecimated1.scaleIntoMe( currentColor, CV_INTER_AREA );             //High-quality resize
        gray1 = imageDecimated1;

        if ( gray2.bAllocated ) {
            Mat img1 = cvarrToMat(gray1.getCvImage());  //Create OpenCV images
            Mat img2 = cvarrToMat(gray2.getCvImage());
            Mat flow;                        //Image for flow
            //Computing optical flow (visit https://goo.gl/jm1Vfr for explanation of parameters)
            calcOpticalFlowFarneback( img1, img2, flow, 0.7, 3, 11, 5, 5, 1.1, 0 );
            //Split flow into separate images
            vector<Mat> flowPlanes;
            split( flow, flowPlanes );
            //Copy float planes to ofxCv images flowX and flowY
            IplImage iplX( flowPlanes[0] );
            flowX = &iplX;
            IplImage iplY( flowPlanes[1] );
            flowY = &iplY;
        }
    }
    //reset statistics about avg direction
    sumX = sumY = avgX = avgY = numOfEntries = 0;

    if (calculatedFlow)
    {

        int w = gray1.width;
        int h = gray1.height;

        //1. Input images + optical flow
        ofPushMatrix();
        ofScale( 4, 4 );

        //Optical flow
        float *flowXPixels = flowX.getPixelsAsFloats();
        float *flowYPixels = flowY.getPixelsAsFloats();
        ofSetColor( 0, 0, 255 );
        for (int y=0; y<h; y+=5) {
            for (int x=0; x<w; x+=5) {
                float fx = flowXPixels[ x + w * y ];
                float fy = flowYPixels[ x + w * y ];
                //Draw only long vectors
                if ( fabs( fx ) + fabs( fy ) > .5 ) {
                    //add to total direction
                    sumX+=fx;
                    sumY+=fy;
                    numOfEntries++;
                }
            }
        }
        ofPopMatrix();
    }

    //calculate average direction vector
    if (numOfEntries>0){
        avgX = sumX / numOfEntries;
        avgY = sumY / numOfEntries;
    }
    
    ofPoint avgDir = ofPoint(avgX, avgY);
    ofPushMatrix();

    movement.x = ofClamp(movement.x + (avgDir.x), 0, ofGetWidth());
    movement.y = ofClamp(movement.y - (avgDir.y), 0, ofGetHeight());
    
//    Return movement to pass it through Self. 
    return movement;
}
