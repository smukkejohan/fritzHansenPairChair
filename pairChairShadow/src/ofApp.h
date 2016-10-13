#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    ofxAssimpModelLoader pairChairModel;
    ofMesh pairChairMesh;
    
    ofEasyCam cam;
    
    ofLight light;
    
    ofBoxPrimitive floor;
    
    
    ofxPanel gui;
    
    
    ofParameter<ofVec3f> chairRotation {"rotation", ofVec3f(270,0,0), ofVec3f(0,0,0), ofVec3f(360,360,360)};

    
    ofParameter<ofVec3f> chairOffset {"offset", ofVec3f(0,0,0), ofVec3f(-400,-400,-400), ofVec3f(400,400,400)};
    

    ofParameterGroup chairParams {"chair",
        chairRotation,
        chairOffset
    };
    
    
    ofParameter<ofVec3f> lightPosition {"pos", ofVec3f(0,0,0), ofVec3f(-400,-400,-400), ofVec3f(400,400,400)};
    
    
    ofParameterGroup lightParams {"light",
        lightPosition
    };
    
    
    ofParameterGroup params {"params",
        chairParams,
        lightParams
    };


    
    
};