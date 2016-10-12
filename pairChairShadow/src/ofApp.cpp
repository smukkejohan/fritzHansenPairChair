#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    pairChairModel.loadModel("BH20_high_3D.obj");
    
    light.setAreaLight(100, 100);
    light.enable();
    
    ofEnableLighting();
    ofEnableDepthTest();
    
    
    // lets say our units are cm
    floor.set(400, 400, 10);
    
    
    // rotate chair to stand on the floor
    // set the scale of the chair
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    cam.begin();
    
    floor.draw();
    
    pairChairModel.drawFaces();
    
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
