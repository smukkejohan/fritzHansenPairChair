#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundAuto(false);
    
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
    
    pairChairModel.loadModel("chair.dae");
    //pairChairMesh = pairChairModel.getMesh(0);
    
    for(auto & n : pairChairModel.getMeshNames()) {
        Part p;
        p.mesh = pairChairModel.getMesh(n);
        
        p.explosionDirection = ofVec3f(ofRandom(-1, 1),ofRandom(0.01,0.5),ofRandom(-1,1));
        
        p.setParent(chairNode);
        
        parts.push_back(p);
    }

    
    // parts
    
    
    //light.setAreaLight(100, 100);
    //light.enable();
    
    
    // lets say our units are mm
    floor.set(4000, 4000, 10);
    
    // rotate chair to stand on the floor
    // set the scale of the chair
    
    gui.setup(params);
    
    gui.loadFromFile("settings.xml");
    
    shadeFbo.allocate(1920, 1080);
    
    reflectFbo.allocate(1920, 1080);
    
    
    float width = ofGetWidth();
    float height = ofGetHeight();
    borders.addVertex( ofPoint(0,0));
    borders.addVertex( ofPoint(width,0));
    borders.addVertex( ofPoint(width, height));
    borders.addVertex( ofPoint(0,height));
    borders.addVertex( ofPoint(0,0));
    
    borders2 = borders;
    borders2 = borders2.getResampledByCount(ofGetWidth());
    
}

ofPoint ofApp::randomPtForSize(ofRectangle rect, int side){
    
    ofPoint aa = ofPoint(rect.x, rect.y);
    ofPoint bb = ofPoint(rect.x + rect.width, rect.y);
    ofPoint cc = ofPoint(rect.x + rect.width, rect.y + rect.height);
    ofPoint dd = ofPoint(rect.x, rect.y + rect.height);
    
    if (side == 0){
        return aa + ofRandom(0,1) * (bb-aa);
    } else if (side == 1){
        return bb + ofRandom(0,1) * (cc-bb);
    } else if (side == 2){
        return cc + ofRandom(0,1) * (dd-cc);
    } else {
        return dd + ofRandom(0,1) * (aa-dd);
    }
    return ofPoint(0,0);
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
    shadeFbo.readToPixels(pixels);
    
    contourFinder.setMinAreaRadius(minArea);
    contourFinder.setMaxAreaRadius(maxArea);
    contourFinder.setThreshold(threshold);
    contourFinder.findContours(pixels);
    contourFinder.setFindHoles(holes);
    
    
    /*for (int i = 0; i < chars.size(); i++){
        vector < ofPolyline > temp = chars[i].getOutline();
        lines.insert(lines.end(), temp.begin(), temp.end());
    }*/

    
    lines = contourFinder.getPolylines();
    
    for (int i= 0; i < lines.size(); i++){
        for (int j = 0; j < lines[i].size(); j++){
            //lines[i][j] += ofPoint(100, 500);
            
            //lines[i][j] = lines[i]
        }
        
        lines[i] = lines[i].getResampledBySpacing(4.0);
        lines[i] = lines[i].getSmoothed(10);
    }
    
    chairNode.setOrientation(chairRotation);
    chairNode.setPosition(chairOffset);
    
    for(auto & p : parts) {
        p.explosionFactor = ofVec3f(explodeAmount,explodeAmount,explodeAmount);
        p.autoRotationOffsetVelocity = autoRotationOffsetVelocity;
        p.autoRotationFactor = autoRotationFactor;
    }
    
    
}

void ofApp::drawReflections() {
    
    if (ofGetMousePressed())ofBackground(0);
    
    cout << ofGetFrameRate() << endl;
    
    //ofSetColor(255,255,255,180);
    
    //ofSeedRandom(mouseX);
    
    ofRectangle rect(0,0,ofGetWidth(), ofGetHeight());
    
    for (int z = 0; z < 10; z ++){
        int side = ofRandom(0,4);
        int sideb = ofRandom(0,4);
        
        if (side != sideb){
            
            //ofPoint a = borders2[ (mouseX+borders2.size()/2) % borders2.size() ]; // //borders2[ mouseX % borders2.size() ];; //borders2[  ]; //ofPoint(0, mouseY); ///randomPtForSize(rect, side);
            
            ofPoint a = ofPoint(mouseX, mouseY);
            
            ofPoint b = ofPoint(mouseX, mouseY);//
            
            if(lines.size() > 0) {
                a = lines[0].getCentroid2D();
            }
            
            //ofPoint(ofGetWidth(), mouseY); ///randomPtForSize(rect, sideb);
            
            
            bool bNoMoreIntersects = false;
            int count = 0;
            while (!bNoMoreIntersects && count < 100){
                
                bool bIntersectsWord = false;
                float minDistance = 10000000;
                ofPoint pos;
                ofPoint newAngle;
                float angleIntersection;
                ofPoint perp;
                
                for (int i= 0; i < lines.size(); i++){
                    for (int j = 0; j < lines[i].size()-1; j++){
                        
                        ofPoint intersection;
                        
                        if (ofLineSegmentIntersection(a, b, lines[i][j], lines[i][j+1], intersection)){
                            float distance = (a - intersection).length();
                            if (distance > 0.01){
                                if (distance < minDistance){
                                    minDistance = distance;
                                    pos = intersection;
                                    bIntersectsWord = true;
                                    
                                    
                                    ofPoint diff = lines[i][j+1] - lines[i][j];
                                    //ofPoint perp;
                                    perp.set(diff.y, -diff.x);
                                    
                                    angleIntersection = atan2(perp.y, perp.x);
                                }
                            }
                        }
                    }
                }
                
                if (bIntersectsWord == false){
                    
                    ofMesh temp;
                    temp.setMode(OF_PRIMITIVE_LINES);
                    temp.addColor(ofColor(255,255,255,10));
                    temp.addVertex(a);
                    temp.addColor(ofColor(255,255,255,10));
                    temp.addVertex(b);
                    temp.draw();
                    
                    //ofLine(a,b);
                    bNoMoreIntersects = true;
                } else {
                    
                    
                    ofMesh temp;
                    temp.setMode(OF_PRIMITIVE_LINES);
                    temp.addColor(ofColor(255,255,255,10));
                    temp.addVertex(a);
                    temp.addColor(ofColor(255,255,255,10));
                    temp.addVertex(pos);
                    temp.draw();
                    
                    
                    //ofLine(a, pos);
                    
                    ofPoint diff = pos - a;
                    float angleMe = atan2(diff.y, diff.x);
                    
                    a = pos;
                    
                    float angleDiff = 2*angleIntersection - angleMe;
                    
                    //R = 2W - P
                    
                    diff.normalize();
                    perp.normalize();
                    
                    ofPoint tempPt = reflect(diff, perp);
                    
                    float angle =  atan2(tempPt.y, tempPt.x);
                    //angle += ofRandom(-0.002, 0.002);
                    b = pos + ofPoint(1000 * cos(angle), 1000 * sin(angle));
                    
                    //cout << count << " " << a << " " << b << endl;
                }
                
                count++;
                
                
            }
            
            //        
            //        if (bIntersectsMe){
            //            ofSetColor(0,0,0,10);
            //            ofLine(a,b);
            //        } else {
            //            ofSetColor(255,255,255,10);
            //            ofLine(a,b);
            //        }
        }
    }
    
    
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
            c.getSmoothed((i+1)*20*ofNoise(ofGetElapsedTimef() + i)).draw();
            ofPopMatrix();
        }
    }
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255, 255, 255);
    
    ofEnableDepthTest();
    
    shadow.beginDepthPass();
    renderScene(true);
    shadow.endDepthPass();
    
    shadeFbo.begin();
    
    ofClear(0,0,0);
    
    shadow.beginRenderPass( cam );
    cam.begin();
    renderScene(false);
    cam.end();
    shadow.endRenderPass();
    
    shadeFbo.end();

    // rename outFbo to shadefbo
    
    // create new fbo for output
    
    ofDisableDepthTest();
    
    ofSetColor(255);
    
    shadeFbo.draw(0,0);
    
    contourFinder.draw();
    
    //drawTunnel();
    
    reflectFbo.begin();
    
    ofSetColor(255);
    //drawReflections();
    
    reflectFbo.end();
    
    ofSetColor(255);
    //reflectFbo.draw(0,0);
    
    
    /*for(auto & c : lines) {
        
        c.draw();
        
    }*/
    
    ofSetColor(255);
    shadow.getDepthTexture().draw(0,0,192,108);
    
    // move to its own window
    gui.draw();

}

void ofApp::renderScene(bool isDepthPass) {
    
    ofBackground(0,0,0);
    ofSetColor(255);

    floor.draw();
    
    //if(isDepthPass) {
    
        ofPushMatrix(); {
            
            for(auto & p : parts) {
                p.draw();
            }
    
        } ofPopMatrix();
        
    //}
    
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
