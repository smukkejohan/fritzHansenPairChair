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
    
    //clickCount = 0;
    
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
    
    
    soundPlayerCresendo.load("cresendo-drone.wav");
    soundPlayerCresendo.setMultiPlay(true);
    
    
    soundPlayerSpacey.load("spacey-drone-half.wav");
    
    
    /*
     gui.setup();
     gui.add(droneLowStart.setup("Drone Low", 0.0, 0.0, 1000));
     gui.add(droneLowGroup);
     */
    //goDroneLow.addListener(this, &ofApp::droneLowPlay);
    
    goDroneLow.addListener(this, &Soundscape::droneLowPlay);
    goDroneHigh.addListener(this, &Soundscape::droneHighPlay);
    goClick.addListener(this, &Soundscape::clickPlay);
    goPluck.addListener(this, &Soundscape::pluckPlay);
    
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
    //    droneLowPlay();
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
void Soundscape::droneLowPlay(){

    //oneshot
    if(!soundPlayerDroneLow.isPlaying()){
        soundPlayerDroneLow.setVolume(droneLowVol);
        soundPlayerDroneLow.play();
    }
}

/*
//--------------------------------------------------------------
void Soundscape::droneLowPlay(float speed){
    soundPlayerDroneLow.setSpeed(speed);
    soundPlayerDroneLow.play();;

}
 */



//--------------------------------------------------------------
void Soundscape::droneHighPlay(){
    //soundPlayerDroneHigh.setSpeed(ofRandom(0.8, 1.2));
    if(!soundPlayerDroneHigh.isPlaying()){
        soundPlayerDroneHigh.play();
    }
}


//--------------------------------------------------------------
void Soundscape::clickPlay(){
    soundPlayerClick.setSpeed(ofRandom(clickRangeMin, clickRangeMax));
    soundPlayerClick.play();
    
}

bool Soundscape::interval(int timeInterval){
    //try creating a scaled tolerance for the interval
    int tolerance = timeInterval/10;
    return (ofGetElapsedTimeMillis() % timeInterval <= tolerance);
}


//--------------------------------------------------------------
void Soundscape::pluckPlay(){
    soundPlayerPluck.setSpeed(ofRandom(pluckRangeMin, pluckRangeMax));
    soundPlayerPluck.play();
 
}

//--------------------------------------------------------------
void Soundscape::spaceyPlay(){
    if(!soundPlayerSpacey.isPlaying()){

        soundPlayerSpacey.play();
    }
}
