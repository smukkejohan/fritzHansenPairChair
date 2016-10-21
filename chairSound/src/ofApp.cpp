#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

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
    goDroneLow.addListener(this, &ofApp::droneLowButtonPressed);
    goDroneHigh.addListener(this, &ofApp::droneHighButtonPressed);
    goClick.addListener(this, &ofApp::clickButtonPressed);
    goPluck.addListener(this, &ofApp::pluckButtonPressed);

    //soundGui.setup(soundParams);
    soundGui.setup();
    soundGui.add(goDroneLow.setup("Drone Low"));
    soundGui.add(droneLowVol);
    soundGui.add(goDroneHigh.setup("Drone High"));
    soundGui.add(droneHighVol);

    soundGui.add(clickGroup);
    soundGui.add(goClick.setup("Click"));
    soundGui.add(pluckGroup);
    soundGui.add(goPluck.setup("Pluck"));
    

    vector<ofSoundPlayer> sounds;
    sounds.push_back(soundPlayerDroneLow);
    sounds.push_back(soundPlayerDroneHigh);
    sounds.push_back(soundPlayerClick);
    sounds.push_back(soundPlayerPluck);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //if(droneLowStart && !soundPlayerDroneLow.isPlaying()){
    //    droneLowButtonPressed();
    //}
    
     soundPlayerDroneLow.setVolume(droneLowVol);
     soundPlayerDroneHigh.setVolume(droneHighVol);
     soundPlayerClick.setVolume(clickVol);
     soundPlayerPluck.setVolume(pluckVol);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    soundGui.draw();
  
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    /*
     if(key == ' '){
        soundPlayerDroneLow.setSpeed(ofRandom(0.8, 1.2));
        soundPlayerDroneLow.play();
    }
    if(key == 'f'){
        soundPlayerDroneHigh.setSpeed(ofRandom(0.8, 1.2));
        soundPlayerDroneHigh.play();
    }
    */
}

//--------------------------------------------------------------
void ofApp::droneLowButtonPressed(){
    soundPlayerDroneLow.setSpeed(ofRandom(0.8, 1.2));
    //soundPlayerDroneLow.setPosition(droneLowStart);
    soundPlayerDroneLow.play();
}


//--------------------------------------------------------------
void ofApp::droneHighButtonPressed(){
    soundPlayerDroneHigh.setSpeed(ofRandom(0.8, 1.2));
    soundPlayerDroneHigh.play();
}


//--------------------------------------------------------------
void ofApp::clickButtonPressed(){
    soundPlayerClick.setSpeed(ofRandom(clickRangeMin, clickRangeMax));
    soundPlayerClick.play();
}

//--------------------------------------------------------------
void ofApp::pluckButtonPressed(){
    soundPlayerPluck.setSpeed(ofRandom(pluckRangeMin, pluckRangeMax));
    soundPlayerPluck.play();
}



//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
