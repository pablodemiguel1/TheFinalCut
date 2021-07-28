//Project title: Creature Environment.
//Author: Pablo De Miguel
//Submission for Creative Coding term 2 project.

// Creature Environment is an interactive game which consists of a variety of creatures with different behaviours: the Self (spiky red creature) responds to the user's movements in front of the camera. The aim is to direct it with body movements to "eat" the foods (the purple creatures) by passing over them, while avoiding touching the enemies (the colourful blobs). If Self eats all the food, then the game is won. However, if it touches any enemy more than three times, the game is lost. The constant movement from the food and the enemies requires the user to be engaged until they have either won or lost the game.

//From a technical perspective, Creature Environment draws heavily from three weekly exercise code examples: noisySun, Virtual Petri Dish and opticalFlow.

//The logic of the exercise noisySun in forming a radius from ofNoise/sin/cos is used in the creation of each individual creature (Food1, Food2, Food3, Enemy & Self). The same variable names have been used, so it should be relatively straightforward to understand what each stands for (ex: angleStep, stepSize etc.). I have modified the code to meet my own aesthetic objectives for each creature.

//The influence of Virtual Petri Dish on this program is more conceptual than technical. The interactive game consists of an environment of creatures, were one of them influences the state of a set of others. There are some technical aspects that I have incorporated, namely the state/health variables (to determine the state of the food and make it dissapear if the Self goes over it). I have however incorporated other aspects such as having one figure that the user controls, as well as having enemies that finish the game but have no impact on the food - all of which are not included in the original Virtual Petri Dish code.

//The code from opticalFlow is used to determine the position of "self" through the user's body movements in front of the camera. The code is almost untouched. The modifications have been to erase the rotating doors and the debug option, as well as moving all the code from the draw to the update function. The latter is because I am not drawing anything in OpticalFlow, but instead I have taken the average direction vectors derived from the user's movement in front of the camera and have passed them to the class 'Self'.

//Any other specific references are explained in the code.

//I want to thank Alex Bridgen for his valuable help in developing this program.

#pragma once

#include "ofMain.h"
#include "CreatureSystem.h"

using namespace glm;

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
private:
    CreatureSystem myCreatureSystem;
    
    bool state1; 
    bool state2;
    bool state3; 
    int livesLeft;

    ofTrueTypeFont myFont1;
    ofTrueTypeFont myFont2;

    string life; 
};
