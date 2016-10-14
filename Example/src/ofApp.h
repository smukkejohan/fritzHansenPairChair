#pragma once

#include "ofMain.h"
#include "ofxShadowSimple.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void renderScene(bool isDepthPass);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofEasyCam cam;
    ofMesh bunny;
    
    ofxShadowSimple shadow;
    
    
    ofFbo outFbo;
    
    ofxAssimpModelLoader chairModel;
    ofMesh chairMesh;
    
    ofxPanel gui;
    ofParameter<ofVec3f> chairRotation {"rotation",
        ofVec3f(270,0,0), ofVec3f(0,0,0), ofVec3f(360,360,360)};
        
    ofParameter<ofVec3f> chairOffset {"offset",
        ofVec3f(0,0,0),
        ofVec3f(-400,-400,-400),
        ofVec3f(400,400,400)
    };
        
    ofParameterGroup chairParams {"chair",
            chairRotation,
            chairOffset
        };
    
    ofParameterGroup params {"params",
        chairParams
    };



};
