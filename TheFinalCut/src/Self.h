#pragma once

#include "ofMain.h"
#include "Enemy.h"


using namespace glm;

class Self {
    
public:
    void setup(int numEnemies);
    int update(vector <Enemy> enemyPositions);
    void draw(vec3 movement);
    vec3 getPos();
private:
    
    Enemy myEnemy;
    
    vector <ofPoint> noiseSeeds;
    
    int numOfLines;
    int circleX, circleY;
    float radius;
    float angleStep;
    
    float check;
    bool state;
    vector<bool> canBeChecked;
    vector<float> distanceMeasured; 
    int lives;
};
