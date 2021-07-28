#include "CreatureSystem.h"

//--------------------------------------------------------------
void CreatureSystem::setup(){
    //Random initial position for all creatures (foods, enemies and self).
    vec3 pos = vec3(ofRandomWidth()/5, ofRandomHeight()/5, 0);
    
    numEnemies = 2;
   
    //Set up two instances of enemies.
    for (int i = 0; i < numEnemies; i++) {
        myEnemies.push_back(myEnemy);
    }
    //Initialise the array of enemies (pass a position unique to each enemy instance).
    for (int i = 0; i < numEnemies; i++) {
        myEnemies[i].setup(pos*i);
    }
    
    //Pass the position to each food  and the number of enemies (2) to self.
    myFood1.setup(pos);
    myFood2.setup(pos);
    myFood3.setup(pos);
    mySelf.setup(numEnemies);
    
    //Setup optical flow to have self follow real-time movements on camera.
    myOpticalFlow.setup();
}

//--------------------------------------------------------------
int CreatureSystem::update(){
    //Get position of self and enemy, and pass it through the foods/self update functions.
    vec3 posSelf = mySelf.getPos();
    vec3 posEnemy = myEnemy.update();
    
    //Update array of enemies
    for (int i = 0; i < numEnemies; i++) {
        myEnemies[i].update();
    }
        
    myFood1.update(posSelf);
    myFood2.update(posSelf);
    myFood3.update(posSelf);
    mySelf.update(myEnemies);
    myOpticalFlow.update();
    
    //get number of lives from self update and return, so that we can pass it to ofApp. 
    livesLeft = mySelf.update(myEnemies);
    return livesLeft;
}
//--------------------------------------------------------------
void CreatureSystem::draw(){
//Get camera movement from user
    ofPoint movement = myOpticalFlow.update();

    //Draw single or multiple instances of foods/enemy
    ofPushMatrix();
    myFood1.draw();
    ofPopMatrix();
    ofPushMatrix();
    myFood2.draw();
    ofPopMatrix();
    ofPushMatrix();
    myFood3.draw();
    ofPopMatrix();
    for (int i = 0; i < 2; i++) {
        ofPushMatrix();
        myEnemies[i].draw();
        ofPopMatrix();
    }
    ofPushMatrix();
    mySelf.draw(movement);
    ofPopMatrix();
}

//--------------------------------------------------------------
//Each state number represents the food number. Ex: state1 = state (whether dead or alive) of food1.
bool CreatureSystem::getState1(){
    state1 = myFood1.getState();
    return state1;
}

//--------------------------------------------------------------
bool CreatureSystem::getState2(){
    state2 = myFood2.getState();
    return state2;
}

//--------------------------------------------------------------
bool CreatureSystem::getState3(){
    state3 = myFood3.getState();
    return state3;
}

