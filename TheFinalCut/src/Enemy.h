#pragma once

#include "ofMain.h"

using namespace glm;

class Enemy{
    
public:
    void setup(vec3 initPos);
    vec3 update();
    void draw();
    void colorRing_1();
    void colorRing_2();
    void colorRing_3();
    bool getState();
    vec3 returnPositions();
private:
        
    vec3 myPos;
    
    vector <float> noiseSeeds_1;
    vector <float> noiseSeeds_2;
    vector <float> noiseSeeds_3;
        
    float angle;
    float angleStep, stepSize;
    int spikes;
    float radius;
    float check;
    ofColor health1;
    ofColor health2;
    ofColor health3;
    
    bool state;
    
    int uniqueMultiplier;
    int numEnemies; 
};
