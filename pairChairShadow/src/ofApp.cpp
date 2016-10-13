#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    pairChairModel.loadModel("BH31_high_3D.obj");
    
    pairChairMesh = pairChairModel.getMesh(0);

    
    
    light.setAreaLight(100, 100);
    light.enable();
    
    
    // lets say our units are mm
    floor.set(4000, 4000, 10);
    
    // rotate chair to stand on the floor
    // set the scale of the chair
    
    gui.setup(params);
}

//--------------------------------------------------------------
void ofApp::update(){
    light.setPosition(lightPosition);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofEnableDepthTest();
    ofEnableLighting();
    
    cam.begin();
    
    floor.draw();
    
    
    ofPushMatrix();
    
    ofTranslate(chairOffset.get());
    
    ofRotateX(chairRotation.get().x);
    ofRotateY(chairRotation.get().y);
    ofRotateZ(chairRotation.get().z);
    
    pairChairModel.drawFaces();
    
    ofPopMatrix();
    
    cam.end();
    
    
    ofDisableDepthTest();
    ofDisableLighting();
    ofSetColor(255);
    
    
    // move to its own window
    gui.draw();

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
