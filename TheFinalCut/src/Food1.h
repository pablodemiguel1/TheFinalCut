#pragma once

#include "ofMain.h"

using namespace glm;

class Food1{
    
public:
    void setup(vec3 initPos);
    void update(vec3 selfPos); 
    void draw();
    bool getState();
private:
    vec3 foodPos;
    
    vector<float> noiseSeeds;
    
    float angle;
    float angleStep, stepSize;
    int spikes;
    int check;
    ofColor health;
    bool state;
};
