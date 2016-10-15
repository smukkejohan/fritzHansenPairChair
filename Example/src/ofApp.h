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
    void prepareExplodedParts();
    
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
    
    ofxShadowSimple shadow;
    
    
    ofFbo outFbo;
    
    ofxAssimpModelLoader chairModel;
    ofMesh chairMesh;

    
    //move to explode class
    
    ofxAssimpModelLoader chairBack;
    ofxAssimpModelLoader chairSeat;
    ofxAssimpModelLoader chairBase;
    ofxAssimpModelLoader chairLegs;
    ofxAssimpModelLoader chairFeet;
    ofxAssimpModelLoader chairParts[5];
    int nParts; //number of chair parts
    ofPoint chairPartsPos[5];
    ofVec3f chairPartsVec[5];
    
    
    
    
    
    //endmove
    
    
    ofxPanel gui;
    ofParameter<ofVec3f> chairRotation {"Rotation", ofVec3f(20,0,0), ofVec3f(0,0,0), ofVec3f(360,360,360)};
    
    
    ofParameter<ofVec3f> chairOffset {"Offset",
        ofVec3f(0,0,0),
        ofVec3f(-400,-400,-400),
        ofVec3f(400,400,400)
    };

    ofParameter<ofVec3f> chairScale {"Scale",
        ofVec3f(0.015,0.015,0.015),
        ofVec3f(-0.5,-0.5,-0.5),
        ofVec3f(0.5,0.5,0.5)
    };

    
    ofParameter<ofVec3f> lightOffset {"Offset",
        ofVec3f(0,0,0),
        ofVec3f(-400,-400,-400),
        ofVec3f(400,400,400)
    };
    
    ofParameterGroup chairParams {"Chair",
            chairRotation,
            chairOffset,
            chairScale
        };
    
    ofParameterGroup lightingParams {"Lighting",
        lightOffset
    };
    
    ofxToggle displayModel, displayParts, explodeParts ;

    ofParameterGroup params {"params",
        chairParams,
        lightingParams,
    };
    
    
    



};
