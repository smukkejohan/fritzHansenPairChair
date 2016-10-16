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
    
    gui.loadFromFile("settings.xml");
    
    outFbo.allocate(1920, 1080);
    
}


ofPoint  reflect(ofPoint vector, ofPoint normal)
{
    return vector - 2 * normal.dot(vector) * normal;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    shadow.setRange( rangeMin, rangeMax );

    shadow.setBias(shadowBias);
    shadow.setIntensity(shadowIntensity);
    //light.setPosition(lightPosition);
    
    shadow.setLightPosition(lightPosition);
    
    shadow.setLightLookAt( ofVec3f(0,0,0), ofVec3f(0,-1,0) );
    
    
    ofPixels pixels;
    outFbo.readToPixels(pixels);
    
    contourFinder.setMinAreaRadius(minArea);
    contourFinder.setMaxAreaRadius(maxArea);
    contourFinder.setThreshold(threshold);
    contourFinder.findContours(pixels);
    contourFinder.setFindHoles(holes);
    
    
    //borders = contourFinder.getPolyline(0);
    
}

void ofApp::drawReflections() {
}

void ofApp::drawTunnel() {
    
    
    ofSetColor(0,0,0);
    for(int i=0; i<10; i++) {
        for (auto & c : contourFinder.getPolylines()) {
            ofPushMatrix();
            ofTranslate(c.getCentroid2D());
            ofScale(
                    (i+1)/10.0,
                    (i+1)/10.0,
                    (i+1)/10.0);
            ofTranslate(-c.getCentroid2D());
            c.draw();
            ofPopMatrix();
        }
    }
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofEnableDepthTest();
    
    shadow.beginDepthPass();
    renderScene(true);
    shadow.endDepthPass();
    
    outFbo.begin();
    
    shadow.beginRenderPass( cam );
    cam.begin();
    renderScene(false);
    cam.end();
    shadow.endRenderPass();
    
    outFbo.end();

    // rename outFbo to shadefbo
    
    // create new fbo for output
    
    
    ofDisableDepthTest();
    
    ofSetColor(255);
    
    //outFbo.draw(0,0);
    
    //contourFinder.draw();
    
    drawTunnel();
    
    
    shadow.getDepthTexture().draw(0,0,192,108);
    
    
    // move to its own window
    gui.draw();

}

void ofApp::renderScene(bool isDepthPass) {
    
    ofBackground(0,0,0);
    ofSetColor(255);

    floor.draw();
    
    
    if(isDepthPass) {
    
        ofPushMatrix(); {
    
        ofTranslate(chairOffset.get());
    
            ofRotateX(chairRotation.get().x);
            ofRotateY(chairRotation.get().y);
            ofRotateZ(chairRotation.get().z);
    
            pairChairModel.drawFaces();
    
        } ofPopMatrix();
        
    }
    
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
