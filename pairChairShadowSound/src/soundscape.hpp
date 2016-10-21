//
//  soundscape.hpp
//  pairChairShadow
//
//  Created by illutron on 21/10/16.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Soundscape{
public:
    void droneLowButtonPressed();
    void droneHighButtonPressed();
    void clickButtonPressed();
    void pluckButtonPressed();
    void draw();
    void setup();
    void update();
    
    ofSoundPlayer soundPlayerDroneLow;
    ofSoundPlayer soundPlayerDroneHigh;
    ofSoundPlayer soundPlayerClick;
    ofSoundPlayer soundPlayerPluck;
    
    ofxButton goDroneLow;
    ofxButton goDroneHigh;
    ofxButton goClick;
    ofxButton goTwang;
    ofxButton goPluck;
    
    ofParameter<float> droneLowVol {"droneLowVol", 1, 0.0, 1};
    ofParameter<float> droneHighVol {"droneHighVol", 1, 0.0, 1};
    ofParameter<float> clickVol {"clickVol", 1, 0.0, 1};
    ofParameter<float> pluckVol {"pluckVol", 1, 0.0, 1};
    
    ofParameter<float> pluckRangeMin {"pluckRangeMin", 0.8, 0.0, 1};
    ofParameter<float> pluckRangeMax {"pluckRangeMax", 1.2, 1.0, 2};
  
    ofParameter<float> clickRangeMin {"clickRangeMin", 0.8, 0.0, 1};
    ofParameter<float> clickRangeMax {"clickRangeMax", 1.2, 1, 2};
    
    ofxGuiGroup pluckGroup;
    ofxGuiGroup clickGroup;
    
    ofxPanel soundGui;
    
    
};

