#include "Enemy.h"

//--------------------------------------------------------------
void Enemy::setup(vec3 initPos){
//    Initialise Position
    myPos = initPos;
    uniqueMultiplier = initPos.x;
    
    check = 50;
    spikes = 10;
    stepSize = 50;
    radius = 5; 
    angleStep = 360.0/spikes;
    state = true;
    
    ofSetCircleResolution(60);
    
    //Each of the three overlapping wobbly shapes of enemy have a different form
    for (int i = 0; i < spikes; i++) {
        noiseSeeds_1.push_back(ofRandom(10000));
        noiseSeeds_2.push_back(ofRandom(10000));
        noiseSeeds_3.push_back(ofRandom(10000));
    }
}

//--------------------------------------------------------------
vec3 Enemy::update(){
//    Set position
    myPos.x = ofMap( ofNoise(uniqueMultiplier + ofGetElapsedTimef()/5.0, -1000), 0, 1, 0, ofGetWidth());
    myPos.y = ofMap( ofNoise(uniqueMultiplier + ofGetElapsedTimef()/5.0, 1000), 0, 1, 0, ofGetHeight());
    
    return myPos;
}

//--------------------------------------------------------------
void Enemy::draw(){
//    Blend the three functions that create a different shape with a different colour.
    ofPushStyle();
    glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_SRC_ALPHA);
        colorRing_1();
        colorRing_2();
        colorRing_3();
    glDisable(GL_BLEND);
    ofPopStyle();
}

//--------------------------------------------------------------
void Enemy::colorRing_1(){
//    Code for one of the three wobbly shapes from Enemy. The other two follow the same logic. It is inspired by the optional extra steps suggested in the exercise noisySun.
    float time = ofGetElapsedTimef();
    time = ofClamp(time, 0, 1);
    
    ofPushMatrix();
    ofTranslate(myPos.x, myPos.y);
    health1 = ofColor(0, 0, 255, 200);
    ofSetColor(health1);
    

    ofBeginShape();
    
    ofPoint pointLocation;
    float noisedRadius = ofNoise(noiseSeeds_1[noiseSeeds_1.size()-1]) * stepSize;
    noisedRadius = radius + noisedRadius;
    pointLocation.x = cos(ofDegToRad(angleStep*(noiseSeeds_1.size()-1))) * noisedRadius;
    pointLocation.y = sin(ofDegToRad(angleStep*(noiseSeeds_1.size()-1))) * noisedRadius;
    ofCurveVertex(pointLocation);
    
    for (int i = 0; i < noiseSeeds_1.size(); i++) {
        ofPoint pointLocation;
        float noisedRadius = ofNoise(noiseSeeds_1[i]) * stepSize;
        noisedRadius = radius + noisedRadius;
        pointLocation.x = cos(ofDegToRad(angleStep*i)) * noisedRadius;
        pointLocation.y = sin(ofDegToRad(angleStep*i)) * noisedRadius;
        ofCurveVertex(pointLocation);
        //ofDrawBezier(pointLocation);
        noiseSeeds_1[i] += 0.01;
    }
    
    pointLocation;
    noisedRadius = ofNoise(noiseSeeds_1[0]) * stepSize;
    noisedRadius = radius + noisedRadius;
    pointLocation.x = cos(ofDegToRad(angleStep*0)) * noisedRadius;
    pointLocation.y = sin(ofDegToRad(angleStep*0)) * noisedRadius;
    ofCurveVertex(pointLocation);
    
    noisedRadius = ofNoise(noiseSeeds_1[1]) * stepSize;
    noisedRadius = radius + noisedRadius;
    pointLocation.x = cos(ofDegToRad(angleStep*1)) * noisedRadius;
    pointLocation.y = sin(ofDegToRad(angleStep*1)) * noisedRadius;
    ofCurveVertex(pointLocation);
    
    ofEndShape();
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void Enemy::colorRing_2(){
    ofPushMatrix();
    ofTranslate(myPos.x, myPos.y);
    
    health2 = ofColor(0, 250, 0, 200);
    ofSetColor(health2);
    
    ofBeginShape();
    
    ofPoint pointLocation;
    float noisedRadius = ofNoise(noiseSeeds_2[noiseSeeds_2.size()-1]) * stepSize;
    noisedRadius = radius + noisedRadius;
    pointLocation.x = cos(ofDegToRad(angleStep*(noiseSeeds_2.size()-1))) * noisedRadius;
    pointLocation.y = sin(ofDegToRad(angleStep*(noiseSeeds_2.size()-1))) * noisedRadius;
    ofCurveVertex(pointLocation);
    
    for (int i = 0; i < noiseSeeds_2.size(); i++) {
        ofPoint pointLocation;
        float noisedRadius = ofNoise(noiseSeeds_2[i]) * stepSize;
        noisedRadius = radius + noisedRadius;
        pointLocation.x = cos(ofDegToRad(angleStep*i)) * noisedRadius;
        pointLocation.y = sin(ofDegToRad(angleStep*i)) * noisedRadius;
        ofCurveVertex(pointLocation);
        //ofDrawBezier(pointLocation);
        noiseSeeds_2[i] += 0.01;
        
    }
    
    pointLocation;
    noisedRadius = ofNoise(noiseSeeds_2[0]) * stepSize;
    noisedRadius = radius + noisedRadius;
    pointLocation.x = cos(ofDegToRad(angleStep*0)) * noisedRadius;
    pointLocation.y = sin(ofDegToRad(angleStep*0)) * noisedRadius;
    ofCurveVertex(pointLocation);
    
    noisedRadius = ofNoise(noiseSeeds_2[1]) * stepSize;
    noisedRadius = radius + noisedRadius;
    pointLocation.x = cos(ofDegToRad(angleStep*1)) * noisedRadius;
    pointLocation.y = sin(ofDegToRad(angleStep*1)) * noisedRadius;
    ofCurveVertex(pointLocation);
    
    ofEndShape();
    ofPopMatrix();
}

//--------------------------------------------------------------
void Enemy::colorRing_3(){
    ofPushMatrix();
    ofTranslate(myPos.x, myPos.y);
    
    health3 = ofColor(250, 0, 0, 200);
    ofSetColor(health3);
    
    ofBeginShape();
    
    ofPoint pointLocation;
    float noisedRadius = ofNoise(noiseSeeds_3[noiseSeeds_3.size()-1]) * stepSize;
    noisedRadius = radius + noisedRadius;
    pointLocation.x = cos(ofDegToRad(angleStep*(noiseSeeds_3.size()-1))) * noisedRadius;
    pointLocation.y = sin(ofDegToRad(angleStep*(noiseSeeds_3.size()-1))) * noisedRadius;
    ofCurveVertex(pointLocation);
    
    for (int i = 0; i < noiseSeeds_2.size(); i++) {
        ofPoint pointLocation;
        float noisedRadius = ofNoise(noiseSeeds_3[i]) * stepSize;
        noisedRadius = radius + noisedRadius;
        pointLocation.x = cos(ofDegToRad(angleStep*i)) * noisedRadius;
        pointLocation.y = sin(ofDegToRad(angleStep*i)) * noisedRadius;
        ofCurveVertex(pointLocation);
        //ofDrawBezier(pointLocation);
        noiseSeeds_3[i] += 0.01;
        
    }
    
    pointLocation;
    noisedRadius = ofNoise(noiseSeeds_3[0]) * stepSize;
    noisedRadius = radius + noisedRadius;
    pointLocation.x = cos(ofDegToRad(angleStep*0)) * noisedRadius;
    pointLocation.y = sin(ofDegToRad(angleStep*0)) * noisedRadius;
    ofCurveVertex(pointLocation);
    
    noisedRadius = ofNoise(noiseSeeds_3[1]) * stepSize;
    noisedRadius = radius + noisedRadius;
    pointLocation.x = cos(ofDegToRad(angleStep*1)) * noisedRadius;
    pointLocation.y = sin(ofDegToRad(angleStep*1)) * noisedRadius;
    ofCurveVertex(pointLocation);
    
    ofEndShape();
    ofPopMatrix();
}

//--------------------------------------------------------------
bool Enemy::getState(){
    return state;
}

vec3 Enemy::returnPositions(){
//    Return position of each iteration of enemy (the number of enemies is set at CreatureSystem), so that when the Self touches any of them it loses a life.
    myPos.x = ofMap( ofNoise(uniqueMultiplier + ofGetElapsedTimef()/5.0, -1000), 0, 1, 0, ofGetWidth());
    myPos.y = ofMap( ofNoise(uniqueMultiplier + ofGetElapsedTimef()/5.0, 1000), 0, 1, 0, ofGetHeight());
    
    vec3 enemyPositions = vec3(myPos.x, myPos.y, 0);
    
    //enemyPositions.push_back(myPos);

    return enemyPositions;
}
