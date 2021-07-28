#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    myCreatureSystem.setup();
    
    //load font
    ofTrueTypeFont::setGlobalDpi(72);
    myFont1.load("verdana.ttf", 100, true, true);
    myFont2.load("verdana.ttf", 20, true, true);
}

//--------------------------------------------------------------
void ofApp::update(){
    myCreatureSystem.update();
    
    //get value determining wether food has been eaten (turned black)
    state1 = myCreatureSystem.getState1();
    state2 = myCreatureSystem.getState2();
    state3 = myCreatureSystem.getState3();
    
    //get value of lives from creatureSystem (which originally gets it from self). lives stands for whether the enemy has been within a the radius of self (for which I have set the hard-coded but roughly accurate number of 50). 
    livesLeft = myCreatureSystem.update();
    
    life = to_string(livesLeft);
}

//--------------------------------------------------------------
void ofApp::draw(){
    //If the three foods have gone within the radius of self, then win game.
    
    if (state1 == false && state2 == false && state3 == false) {
        ofPushMatrix();
        ofPushStyle();
        ofSetColor(0, 128, 0);

        myFont1.drawString("WIN", ofGetWidth()/2.5, ofGetHeight()/2);
        ofPopStyle();
        ofPopMatrix();
    } else
        
    //Update lives
    if (livesLeft > 0) {
        ofSetColor(255);
        myFont2.drawString("Lives left:", ofGetWidth()/50, ofGetHeight()/1.05);
        ofSetColor(255, 0, 0);
        myFont2.drawString(life, ofGetWidth()/8, ofGetHeight()/1.05);
        myCreatureSystem.draw();
    } else {
    
    //If self has been in contact with enemies more than three times, then game over. 
        ofPushMatrix();
        ofPushStyle();
        ofBackground(0);
        ofSetColor(255, 0, 0);
        myFont1.drawString("GAME OVER", ofGetWidth()/5, ofGetHeight()/2);
        ofPopStyle();
        ofPopMatrix();
    }
}
