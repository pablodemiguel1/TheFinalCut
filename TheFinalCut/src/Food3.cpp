#include "Food3.h"

//--------------------------------------------------------------
void Food3::setup(vec3 initPos){
//    Initialise position
    foodPos = initPos;
    
    check = 50;
    health = ofColor(218, 112, 214);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);

    numOfLines = 20;
    radius = 5;
    angleStep = 360.0 / numOfLines;
    state = true;

    for (int i=0; i<numOfLines; i++)
    {
        noiseSeeds.push_back(ofPoint(ofRandom(-20,200)));
    }
}

//--------------------------------------------------------------
void Food3::update(vec3 selfPos){
    //    Set position
    foodPos.x = ofMap( ofNoise(ofGetElapsedTimef()/3.0, -1000), 0, 1, 0, ofGetWidth());
    foodPos.y = ofMap( ofNoise(ofGetElapsedTimef()/3.0, 1000), 0, 1, 0, ofGetHeight());
    
    float distanceMeasured = ofDist(selfPos.x, selfPos.y, foodPos.x, foodPos.y);
    if( distanceMeasured <= check ){
        health = ofColor(0);
        state = false; 
    } 
}
    
//--------------------------------------------------------------
void Food3::draw(){
    ofPushStyle();
    ofSetColor(health);
    ofTranslate(foodPos.x, foodPos.y);
    ofNoFill();

//    Create little moving (ofNoise) circles around a malleable radius
    for (int i=0; i<numOfLines; i++) {
        float noisedRadius = ofNoise(noiseSeeds[i]) * angleStep + radius;
        ofPoint pointLocation;
        pointLocation.x = cos(ofDegToRad(angleStep*i)) * noisedRadius;
        pointLocation.y = sin(ofDegToRad(angleStep*i)) * noisedRadius;

        float angle = atan2(foodPos.y-pointLocation.x, foodPos.x-pointLocation.y);
        ofRotateDeg(ofRadToDeg(angle));
        
        noiseSeeds[i] += 0.01;
        ofDrawCircle(pointLocation, 2);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
bool Food3::getState(){
    return state;
}
