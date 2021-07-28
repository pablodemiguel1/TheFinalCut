#pragma once

#include "ofMain.h"

using namespace glm;

class Food3{
    
public:
    void setup(vec3 initPos);
    void update(vec3 selfPos);
    void draw();
    bool getState();
private:
    vec3 foodPos;
    
    vector<ofPoint> noiseSeeds;
    
    int numOfLines;
    float radius;
    float angleStep;
    float check;
    ofColor health;
    bool state;
};
