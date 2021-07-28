#include "Food1.h"

//--------------------------------------------------------------
void Food1::setup(vec3 initPos){
    //Initialise position determined in creatureSystem.
    foodPos = initPos;
    
    //Check is the radius of the food.
    check = 60;

    //Variables taken from noisySun and modified for my own purposes. Same applies to Food2 & Food3.
    angle = 50;
    spikes = 50;
    stepSize = 20;
    angleStep = 360.0/spikes;
    health = ofColor(191, 64, 191);
    
//    Set state to true to differentiate it from when Food goes within the radius of Self, in which case state turns false. 
    state = true;
    
    for (int i = 0; i < spikes; i++) {
        noiseSeeds.push_back(ofRandom(1000));
        }
}

//--------------------------------------------------------------
void Food1::update(vec3 selfPos){
    //Position of food derived from ofNoise. ofGetElapsedTimef() is divided by different numbers in Food2, Food3 & Enemy. This makes each creature run their own particular course.
    foodPos.x = ofMap( ofNoise(ofGetElapsedTimef()/2.0, -1000), 0, 1, 0, ofGetWidth());
    foodPos.y = ofMap( ofNoise(ofGetElapsedTimef()/2.0, 1000), 0, 1, 0, ofGetHeight());
    
    //Check whether the position of Food is within the paramter of Self. If it is, turn the color to black (creates the effect of Food dissappearing against the black background) and return state false, which is used in the if statements in ofApp to determine whether the game is won or lost.
    float distanceMeasured = ofDist(selfPos.x, selfPos.y, foodPos.x, foodPos.y);
    if( distanceMeasured <= check ){
        health = ofColor(0);
        state = false; 
    } 
}

//--------------------------------------------------------------
void Food1::draw(){
    //Create figure
    ofPushStyle();
    angle = angle + 0.3;

    ofTranslate(foodPos.x, foodPos.y);

    ofPushMatrix();
    ofRotateDeg(angle*5);
    ofSetColor(health);
    ofNoFill();
    ofSetLineWidth(5);

    ofBeginShape();
    for (int i = 0; i < spikes; i++) {
        float noisedRadius = ofNoise(noiseSeeds[i]) * stepSize;
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
    ofPopStyle();
}

//--------------------------------------------------------------
bool Food1::getState(){
    return state;
}
