#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetBoxResolution( 30, 30, 30 );
    
    /*
    cam.disableMouseInput();
    cam.setDistance( 10 );
    //cam.setPosition(0, 0, -10 );
    cam.setPosition(0, -30, -10 );
    cam.lookAt( ofVec3f(0,0,0), ofVec3f(0,-1,0) );
    cam.setNearClip(1);
    cam.setFarClip(300);
    
    cam.enableMouseInput();
*/
    
    pairChairModel.loadModel("BH31_high_3D.obj");
    pairChairMesh = pairChairModel.getMesh(0);
    
    
    //light.setAreaLight(100, 100);
    //light.enable();
    
    
    // lets say our units are mm
    floor.set(4000, 4000, 10);
    
    // rotate chair to stand on the floor
    // set the scale of the chair
    
    gui.setup(params);
    
    
    // range of the shadow camera //
    shadow.setRange( 10, 5000 );
    shadow.setBias( 0.01 );
    
    
    outFbo.allocate(1920, 1080);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //light.setPosition(lightPosition);
    
    shadow.setLightPosition(lightPosition);
    
    shadow.setLightLookAt( ofVec3f(0,0,0), ofVec3f(0,-1,0) );
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofEnableDepthTest();

    
    outFbo.begin();

    
    shadow.beginDepthPass();
    renderScene(true);
    shadow.endDepthPass();
    
    shadow.beginRenderPass( cam );
    cam.begin();
    renderScene(false);
    cam.end();
    shadow.endRenderPass();

    outFbo.end();

    
    ofDisableDepthTest();
    
    ofSetColor(255);
    
    outFbo.draw(0,0);
    
    // move to its own window
    gui.draw();

}

void ofApp::renderScene(bool isDepthPass) {
    
    ofBackground(0,0,0);
    ofSetColor(255);

    floor.draw();
    
    ofPushMatrix();
    
    ofTranslate(chairOffset.get());
    
    ofRotateX(chairRotation.get().x);
    ofRotateY(chairRotation.get().y);
    ofRotateZ(chairRotation.get().z);
    
    pairChairModel.drawFaces();
    
    ofPopMatrix();
    
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
