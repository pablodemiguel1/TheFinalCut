#pragma once

#include "ofMain.h"
#include "Food1.h"
#include "Food2.h"
#include "Food3.h"
#include "Enemy.h"
#include "Self.h"
#include "OpticalFlow.h"

using namespace glm;

class CreatureSystem {
public:
    void setup();
    int update();
    void draw();
    
    bool getState1();
    bool getState2();
    bool getState3();
    int livesState();
    
private:
    Food1 myFood1;
    Food2 myFood2;
    Food3 myFood3;
    Enemy myEnemy;
    Self mySelf;
    OpticalFlow myOpticalFlow;
    
    vector<Enemy> myEnemies;
    
    bool state1;
    bool state2;
    bool state3;
    int livesLeft;
    int numEnemies; 
};
