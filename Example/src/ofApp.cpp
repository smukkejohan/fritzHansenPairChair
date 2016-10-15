#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    int nearClip = 1;
    int farClip = 300;
    
    ofSetBoxResolution( 30, 30, 30 );
    
    cam.disableMouseInput();
    cam.setDistance( 10 );
    //cam.setPosition(0, 0, -10 );
    cam.setPosition(0, -30, -10 );
    cam.lookAt( ofVec3f(0,0,0), ofVec3f(0,-1,0) );
    cam.setNearClip(nearClip);
    cam.setFarClip(farClip);
    
    cam.enableMouseInput();
    
    // range of the shadow camera //
    //tried setting nearClip to 1 but it was weird... less shadows
    shadow.setRange( 10, 150 );
    shadow.setBias( 0.01 );
    
    
    outFbo.allocate(1920, 1080);
    
    
    chairModel.loadModel("BH30.obj");
    chairMesh = chairModel.getMesh(0);
    

    //move to another method
    chairBack.loadModel("BH31_back.obj");
    chairSeat.loadModel("BH31_seat.obj");
    chairBase.loadModel("BH31_base.obj");
    chairLegs.loadModel("BH20_legs.obj");
    chairFeet.loadModel("BH20_feet.obj");
    
    chairParts[0] = chairBack;
    chairParts[1] = chairSeat;
    chairParts[2] = chairBase;
    chairParts[3] = chairLegs;
    chairParts[4] = chairFeet;
    nParts = 5;
    float explosionRad = 10;
    
    //init explosion field
    for (int i=0; i<nParts; i++) {     //Scan all the parts
        ofPoint partCenter( ofRandom( -1, 1 ),
                           ofRandom( -1, 1 ),
                           ofRandom( -1, 1 ) );
        partCenter.normalize(); //Normalize vector's length to 1
        partCenter *= explosionRad;      //Now the center vector has
        chairPartsPos[i] = partCenter;
       
        ofVec3f partVec(ofRandom( -1, 1 ),
                        ofRandom( -1, 1 ),
                        ofRandom( -1, 1 ));
        partVec.normalize();
        chairPartsVec[i] = partVec;
    }
    //endmove
    
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

    
    //gui setups
    gui.setup(params);
    gui.add(displayModel.setup("display model", false) );
    gui.add(displayParts.setup("display parts", false) );
    gui.add(explodeParts.setup("explode parts", false) );

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
    

   
    outFbo.begin();
        shadow.beginDepthPass();
            glEnable(GL_DEPTH_TEST);
            renderScene(true);
            glDisable(GL_DEPTH_TEST);
        shadow.endDepthPass();
    
        shadow.beginRenderPass( cam );
            cam.begin();
            glEnable(GL_DEPTH_TEST);
            //toggle to show chair or not
            renderScene(displayModel);
            glDisable(GL_DEPTH_TEST);
            cam.end();
        shadow.endRenderPass();
    outFbo.end();
    
    
    outFbo.draw(0,0);
    //move to its own window
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::renderScene(bool isDepthPass) {
    
    ofBackground( 255,255,255 );
    
    
    ofSetColor( 241,238,162 );
    ofPushMatrix(); {
        ofRotateX( cos( ofGetElapsedTimef() * 2.3) * sin( ofGetElapsedTimef() ) * RAD_TO_DEG );
        ofRotateY( sin( ofGetElapsedTimef() ) * RAD_TO_DEG );
        //ofTranslate(chairOffset.get());
        
        
        if(explodeParts){
            for(int i = 0; i < nParts; i++){

                /*
                float time = ofGetElapsedTimef();    //Get time in seconds
                float angle = time * 10; //Compute angle. We rotate at speed
                //10 degrees per second
                ofRotate( angle, 0, 1, 0 );    //Rotate the coordinate system
                */
                 
                chairParts[i].drawFaces();
            }
        }else{
            chairModel.drawFaces();
        }
        
        
    }
    ofPopMatrix();
    
    ofSetColor( 241,221,113 );
    
    
    
    
    
    
    ofSetColor( 241,212,55 );
    ofPushMatrix(); {
        ofTranslate(5, 0, 0 );
        //ofRotate(180, 1, 0, 0 );
        
        ofTranslate(chairOffset.get());
        //ofRotateX( cos( ofGetElapsedTimef() * 2.3) * sin( ofGetElapsedTimef() ) * RAD_TO_DEG );
        //ofRotateY( sin( ofGetElapsedTimef() ) * RAD_TO_DEG );
        
        ofRotateX(chairRotation.get().x);
        ofRotateY(chairRotation.get().y);
        ofRotateZ(chairRotation.get().z);
        //make adjustable scale
        //ofScale( 0.015, 0.015, 0.015 );
        ofScale(chairScale.get().x, chairScale.get().y, chairScale.get().z);

        if(isDepthPass) {
            if(displayParts){
                for(int i = 0; i < nParts; i++){
                    chairParts[i].drawFaces();
                }
            }else{
                chairModel.drawFaces();
            }
        }
        //chairMesh.draw();
    } ofPopMatrix();
    
    // floor //
    ofSetColor( 142,187,151 );
    ofDrawBox( 0, 5, 0, 250, 2, 250 );
    
    // wall //
    //ofDrawBox(0, -8, 10, 80, 30, 2 );
    
    
    //ofDrawSphere( light.getPosition(), 1 );
    
    //cam.end();

    ofSetColor(255);
    

}

//--------------------------------------------------------------
void ofApp::prepareExplodedParts() {
    

    
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
