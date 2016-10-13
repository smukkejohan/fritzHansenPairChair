#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofSetBoxResolution( 30, 30, 30 );
    
    cam.disableMouseInput();
    cam.setDistance( 10 );
    //cam.setPosition(0, 0, -10 );
    cam.setPosition(0, -30, -10 );
    cam.lookAt( ofVec3f(0,0,0), ofVec3f(0,-1,0) );
    cam.setNearClip(1);
    cam.setFarClip(300);
    
    cam.enableMouseInput();
    
    // range of the shadow camera //
    shadow.setRange( 10, 150 );
    shadow.setBias( 0.01 );
    
    /*bunny.load( "lofi-bunny.ply" );
    
    vector< ofMeshFace > faces = bunny.getUniqueFaces();
    for( int i = 0; i < faces.size(); i++ ) {
        faces[i].setVertex( 0, faces[i].getVertex(0 ));
        faces[i].setNormal(0, faces[i].getFaceNormal() );
        faces[i].setNormal(1, faces[i].getFaceNormal() );
        faces[i].setNormal(2, faces[i].getFaceNormal() );
    }
    bunny.setFromTriangles( faces );
    bunny.smoothNormals( 60 );
    cout << "Bunny normals = " << bunny.getNumNormals() << endl;
    */
    
    
    chairModel.loadModel("BH31_high_3D.obj");
    chairMesh = chairModel.getMesh(0);
    
    /*
    vector< ofMeshFace > chairFaces = chairMesh.getUniqueFaces();
    for( int i = 0; i < chairFaces.size(); i++ ) {
        chairFaces[i].setVertex( 0, chairFaces[i].getVertex(0 ));
        chairFaces[i].setNormal(0, chairFaces[i].getFaceNormal() );
        chairFaces[i].setNormal(1, chairFaces[i].getFaceNormal() );
        chairFaces[i].setNormal(2, chairFaces[i].getFaceNormal() );
    }
    chairMesh.setFromTriangles( chairFaces );
    chairMesh.smoothNormals( 60 );
    cout << "Chair normals = " << chairMesh.getNumNormals() << endl;
    */

    //gui.setup(params);

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //shadow.setLightPosition( ofVec3f(cos(ofGetElapsedTimef()*0.6) * 10, -30, -25) );
    //shadow.setLightPosition( ofVec3f(cos(ofGetElapsedTimef()*0.6) * 50, -30, -50) );
    shadow.setLightPosition(ofVec3f(cos(ofGetElapsedTimef()*0.6) * 50,
                                    sin(ofGetElapsedTimef()*10) -30,
                                    (sin(ofGetElapsedTimef()*0.7)*30)-50
                                    )
                            );
    shadow.setLightLookAt( ofVec3f(0,0,0), ofVec3f(0,-1,0) );
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    shadow.beginDepthPass();
    glEnable(GL_DEPTH_TEST);
    renderScene();
    glDisable(GL_DEPTH_TEST);
    shadow.endDepthPass();
    
    
    shadow.beginRenderPass( cam );
    cam.begin();
    glEnable(GL_DEPTH_TEST);
    renderScene();
    glDisable(GL_DEPTH_TEST);
    cam.end();
    shadow.endRenderPass();
    
    
}

//--------------------------------------------------------------
void ofApp::renderScene() {
    
    ofBackground( 241,212,55 );
    
    /*
    ofSetColor( 241,238,162 );
    ofPushMatrix(); {
        ofRotateX( cos( ofGetElapsedTimef() * 2.3) * sin( ofGetElapsedTimef() ) * RAD_TO_DEG );
        ofRotateY( sin( ofGetElapsedTimef() ) * RAD_TO_DEG );
        ofDrawBox( 2, 2, 2 );
    } ofPopMatrix();
    
    ofSetColor( 241,221,113 );
    ofDrawSphere( -4, sin( ofGetElapsedTimef() ) * 3, 2 );
    ofSetColor( 183,241,195 );
    ofDrawSphere( -4, sin( ofGetElapsedTimef() * 0.3 ) * 3, 5, 2 );
    
    */
    
    
    ofSetColor( 241,212,55 );
    ofPushMatrix(); {
        ofTranslate(5, 0, 0 );
        //ofRotate(180, 1, 0, 0 );
        
        ofTranslate(chairOffset.get());
        ofRotateX( cos( ofGetElapsedTimef() * 2.3) * sin( ofGetElapsedTimef() ) * RAD_TO_DEG );
        ofRotateY( sin( ofGetElapsedTimef() ) * RAD_TO_DEG );
        
        //ofRotateX(chairRotation.get().x);
        //ofRotateY(chairRotation.get().y);
        ofRotateZ(chairRotation.get().z);
        //make adjustable scale
        ofScale( 0.015, 0.015, 0.015 );
        //bunny.draw();
        chairModel.drawFaces();
        //chairMesh.draw();
    } ofPopMatrix();
    
    // floor //
    ofSetColor( 142,187,151 );
    ofDrawBox( 0, 5, 0, 250, 2, 250 );
    
    // wall //
    //ofDrawBox(0, -8, 10, 80, 30, 2 );
    
    
    //ofDrawSphere( light.getPosition(), 1 );
    
    cam.end();

    ofDisableDepthTest();
    ofDisableLighting();
    ofSetColor(255);
    
    //move to its own window
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
