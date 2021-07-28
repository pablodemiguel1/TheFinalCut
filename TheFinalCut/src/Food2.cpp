#include "Food2.h"

//--------------------------------------------------------------
void Food2::setup(vec3 initPos){
//    Initialise position
    foodPos = initPos;

    check = 50;
    angle = 50;
    spikes = 50;
    stepSize = 20;
    radius = 10;
    angleStep = 360.0/spikes;
    health = ofColor(207, 159, 255);
    state = true;
    
    for (int i = 0; i < spikes; i++) {
        noiseSeeds.push_back(ofRandom(1000));
        }
}

//--------------------------------------------------------------
void Food2::update(vec3 selfPos){
//    Set position
    foodPos.x = ofMap( ofNoise(ofGetElapsedTimef()/4.0, -1000), 0, 1, 0, ofGetWidth());
    foodPos.y = ofMap( ofNoise(ofGetElapsedTimef()/4.0, 1000), 0, 1, 0, ofGetHeight());
    
    float distanceMeasured = ofDist(selfPos.x, selfPos.y, foodPos.x, foodPos.y);
    if( distanceMeasured <= check ){
        health = ofColor(0);
        state = false;
    }
}

//--------------------------------------------------------------
void Food2::draw(){
    //Create figure
    ofPushStyle();
    angle = angle + 0.2;

    ofTranslate(foodPos.x, foodPos.y);

    ofPushMatrix();
    ofRotateDeg(angle*5);
    ofSetColor(health);
    ofNoFill();
    ofSetLineWidth(5);
    ofBeginShape();
    for (int i = 0; i < spikes; i++) {
        float noisedRadius = ofNoise(noiseSeeds[i]) * stepSize + radius;
        ofPoint pointLocation;
        pointLocation.x = cos(ofDegToRad(angleStep*i))*noisedRadius;
        pointLocation.y = sin(ofDegToRad(angleStep*i))*noisedRadius;
        ofVertex(pointLocation);
        noiseSeeds[i] += 0.01;
    }
        ofSetColor(health);
        ofDrawCircle(0, 0, 2);
    ofEndShape();
    ofPopMatrix();

    //Create rotating ring around figure.
    ofPushMatrix();
        ofRotateDeg(-angle);
        ofTranslate(25,0);
        ofBeginShape();
        for (int i = 0; i < spikes; i++) {
            float noisedRadius = ofNoise(noiseSeeds[i]) * stepSize + radius/3;
            ofPoint pointLocation;
            pointLocation.x = cos(ofDegToRad(angleStep*i))*noisedRadius;
            pointLocation.y = sin(ofDegToRad(angleStep*i))*noisedRadius;
            ofVertex(pointLocation);
            noiseSeeds[i] += 0.01;
        }
        ofEndShape();
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
bool Food2::getState(){ 
    return state;
}
