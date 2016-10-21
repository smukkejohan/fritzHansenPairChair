//
//  soundscape.cpp
//  pairChairShadow
//
//  Created by illutron on 21/10/16.
//
//

#include "soundscape.hpp"


//--------------------------------------------------------------
void Soundscape::setup(){
    
    
    pluckGroup.setup("Pluck");
    pluckGroup.add(pluckRangeMin);
    pluckGroup.add(pluckRangeMax);
    pluckGroup.add(pluckVol);
    
    clickGroup.setup("Click");
    clickGroup.add(clickRangeMin);
    clickGroup.add(clickRangeMax);
    clickGroup.add(clickVol);
    
    
    soundPlayerDroneLow.load("lost-transmission-drone.wav");
    soundPlayerDroneLow.setMultiPlay(true);
    
    soundPlayerDroneHigh.load("high-pitched-drone.wav");
    soundPlayerDroneHigh.setMultiPlay(true);
    
    soundPlayerClick.load("55Hz.wav");
    soundPlayerClick.setMultiPlay(true);
    
    //add more plucks?
    soundPlayerPluck.load("pluck.wav");
    soundPlayerPluck.setMultiPlay(true);
    
    /*
     gui.setup();
     gui.add(droneLowStart.setup("Drone Low", 0.0, 0.0, 1000));
     gui.add(droneLowGroup);
     */
    //goDroneLow.addListener(this, &ofApp::droneLowButtonPressed);
    
    goDroneLow.addListener(this, &Soundscape::droneLowButtonPressed);
    goDroneHigh.addListener(this, &Soundscape::droneHighButtonPressed);
    goClick.addListener(this, &Soundscape::clickButtonPressed);
    goPluck.addListener(this, &Soundscape::pluckButtonPressed);
    
    //soundGui.setup(soundParams);
    soundGui.setup();
    soundGui.add(goDroneLow.setup("Drone Low"));
    soundGui.add(droneLowVol);
    soundGui.add(goDroneHigh.setup("Drone High"));
    soundGui.add(droneHighVol);
    
    soundGui.add(&clickGroup);
    soundGui.add(goClick.setup("Click"));
    soundGui.add(&pluckGroup);
    soundGui.add(goPluck.setup("Pluck"));
    
    vector<ofSoundPlayer> sounds;
    sounds.push_back(soundPlayerDroneLow);
    sounds.push_back(soundPlayerDroneHigh);
    sounds.push_back(soundPlayerClick);
    sounds.push_back(soundPlayerPluck);
    
}


//--------------------------------------------------------------
void Soundscape::update(){
    //if(droneLowStart && !soundPlayerDroneLow.isPlaying()){
    //    droneLowButtonPressed();
    //}
    
    soundPlayerDroneLow.setVolume(droneLowVol);
    soundPlayerDroneHigh.setVolume(droneHighVol);
    soundPlayerClick.setVolume(clickVol);
    soundPlayerPluck.setVolume(pluckVol);
}

//--------------------------------------------------------------
void Soundscape::draw(){
    
    soundGui.draw();
    
};


//--------------------------------------------------------------
void Soundscape::droneLowButtonPressed(){
    soundPlayerDroneLow.setSpeed(ofRandom(0.8, 1.2));
    //soundPlayerDroneLow.setPosition(droneLowStart);
    soundPlayerDroneLow.play();
}


//--------------------------------------------------------------
void Soundscape::droneHighButtonPressed(){
    soundPlayerDroneHigh.setSpeed(ofRandom(0.8, 1.2));
    soundPlayerDroneHigh.play();
}


//--------------------------------------------------------------
void Soundscape::clickButtonPressed(){
    soundPlayerClick.setSpeed(ofRandom(clickRangeMin, clickRangeMax));
    soundPlayerClick.play();
}

//--------------------------------------------------------------
void Soundscape::pluckButtonPressed(){
    soundPlayerPluck.setSpeed(ofRandom(pluckRangeMin, pluckRangeMax));
    soundPlayerPluck.play();
}

