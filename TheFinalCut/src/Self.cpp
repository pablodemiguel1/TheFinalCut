#include "Self.h"

//--------------------------------------------------------------
void Self::setup(int numEnemies){
    ofSetFrameRate(60);

    check = 50;
    numOfLines = 150;
    radius = 20;
    angleStep = 360.0 / numOfLines;
    circleX = ofGetWidth()/2;
    circleY = 10;

    for (int i=0; i<numOfLines; i++)
    {
        noiseSeeds.push_back(ofPoint(ofRandom(-20,100)));
    }
    lives = 3;
    //canBeChecked = true;
    
    //Take numEnemies from creatureSystem (2 enemies). 
    for (int i = 0; i < numEnemies; i++) {
        canBeChecked.push_back(true);
        distanceMeasured.push_back(100);
    }
}

//--------------------------------------------------------------
int Self::update(vector <Enemy> enemyPositions){
    
    vec3 selfPos = vec3(circleX, circleY, 0);
    
    for (int i = 0; i < enemyPositions.size(); i++) {
        canBeChecked.push_back(true);
        //Grab index that we are currently on in the length of the vector using the function that we got from the Enemy class, and using it to check the distance measured against the variable 'check'. enemyPositions[i] is not actually the positions, its the entire enemy class (all the instances of it). Because the checks happen simultenously, it means that we  need a vector for our distanceMeasured and our canBeChecked.
        distanceMeasured[i] = ofDist(selfPos.x, selfPos.y, enemyPositions[i].returnPositions().x, enemyPositions[i].returnPositions().y);
                    
            if (canBeChecked[i] == true){
               if( distanceMeasured[i] <= check){
                   //state = false;
                   lives -= 1;
                   canBeChecked[i] = false;
               }
            }
            if (distanceMeasured[i] > check){
                   canBeChecked[i] = true;
               }
        }
    //Return lives to pass them to creatureSystem.cpp update.
    return lives;
    }

//--------------------------------------------------------------
void Self::draw(vec3 movement){
    ofPushStyle();
    if (movement.x != 0 || movement.y != 0) {
        circleX = ofClamp(circleX+(movement.x-circleX), 0, ofGetWidth());
        circleY = ofClamp(circleY+(movement.y-circleY), 0, ofGetHeight());
    }
    
    ofTranslate(circleX, circleY);
    ofSetColor(128, 0, 0);
    
    for (int i=0; i<numOfLines; i++) {
        float noisedRadius = ofNoise(noiseSeeds[i]) * angleStep + radius;
        ofPoint pointLocation;
        pointLocation.x = cos(ofDegToRad(angleStep*i)) * noisedRadius;
        pointLocation.y = sin(ofDegToRad(angleStep*i)) * noisedRadius;

        float angle = atan2(circleY-pointLocation.x, circleX-pointLocation.y);
        ofRotateDeg(ofRadToDeg(angle));
        
        noiseSeeds[i] += 0.01;
        ofDrawRectangle(pointLocation,15, 2);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
vec3 Self::getPos(){
    vec3 selfPos = vec3(circleX, circleY, 0);
    return selfPos;
}
