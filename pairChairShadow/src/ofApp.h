#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
#include "ofxShadowSimple.h"
#include "ofxEasing.h"
#include "ofxCv.h"
#include "ofxParameterFader.hpp"
#include "ofxBlur.h"



#define DURATION 120

class Part : public ofNode {
public:
    
    ofMesh mesh;
    
    ofVec3f explosionFactor;
    ofVec3f explosionDirection;
    
    ofVec3f partRotationOffset;
    ofVec3f autoRotationOffsetVelocity;
    
    float autoRotationFactor = autoRotationOffsetVelocity.x;
    
    void customDraw() {
        
        partRotationOffset += autoRotationOffsetVelocity * explosionDirection;
    
        ofPushMatrix();
        
        //ofTranslate(mesh.getCentroid());
        //ofScale(0.5, 0.5, 0.5);
        //ofTranslate(-mesh.getCentroid());
        
        ofTranslate( explosionFactor * explosionDirection );
        
        ofRotateX(partRotationOffset.x * autoRotationFactor);
        ofRotateY(partRotationOffset.y * autoRotationFactor);
        ofRotateZ(partRotationOffset.z * autoRotationFactor);
        
        mesh.draw();
        ofPopMatrix();
    }
    
};


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
    
    void drawReflections();
    void drawTunnel();
    
    vector<Part> parts;
    
    ofxShadowSimple shadow;
    ofFbo shadeFbo;
    ofFbo reflectFbo;
    
    ofxBlur blur;
    
    void renderFloor();
    void renderModels();

    ofxAssimpModelLoader pairChairModel;
    ofNode chairNode;
    ofCamera cam;
    ofBoxPrimitive floor;
    ofxPanel gui;
    
    vector < ofPolyline > lines;
    ofPolyline borders;
    ofPolyline borders2;

    ofPoint randomPtForSize(ofRectangle b, int side);
    
    ofxCv::ContourFinder contourFinder;
    ofParameter<float> minArea {"Min area", 10, 1, 100}, maxArea {"Max area", 200, 1, 500}, threshold {"Threshold", 128, 0, 255};
    ofParameter<bool> holes {"holes" , true};
    
    ofParameter<ofVec3f> chairRotation {"rotation", ofVec3f(270,0,0), ofVec3f(0,0,0), ofVec3f(360,360,360)};
    
    ofParameter<ofVec3f> autoRotationOffsetVelocity  {"auto rotation", ofVec3f(0,0,0), ofVec3f(0,0,0), ofVec3f(20,20,20)};

    ofParameter<ofVec3f> chairOffset {"offset", ofVec3f(0,0,0), ofVec3f(-4000,-4000,-4000), ofVec3f(4000,4000,4000)};
    ofParameter<ofVec3f> lightPosition {"pos", ofVec3f(0,0,0), ofVec3f(-4000,-4000,-4000), ofVec3f(4000,4000,4000)};
    ofParameter<float> rangeMin {"rangeMin", 0, 0, 1000};
    ofParameter<float> rangeMax {"rangeMax", 0, 0, 8000};
    ofParameter<float> shadowBias {"shadowBias", 0, 0, 0.02};
    ofParameter<float> shadowIntensity {"shadowIntensity", 0, 0, 1};
    ofParameter<float> explodeAmount {"explode", 0, 0, 3000};
    ofParameter<float> autoRotationFactor {"autoRotateFactor", 0, 0,1};
    
    ofParameter<ofVec3f> camPos {"camPos", ofVec3f(0,0,-4000), ofVec3f(-1000,-1000,2000), ofVec3f(1000,1000,6000)};
    
    ofParameter<float> camFov {"fov", 26, 0, 170};
    
    ofParameter<bool> renderChair {"render chair", false};
    ofParameter<bool> renderTunnel {"render tunnel", false};
    ofParameter<bool> renderReflection {"render reflection", false};
    
    ofParameter<bool> renderShade {"render shade", true};
    
    
    ofParameter<float> blurShadeScale {"blur", 0, 0, 10};
    ofParameter<float> blurShadeRotation {"blurRot", 0, 0, PI};

    
    
    ofParameter<ofFloatColor> bgColor {"Background color",
        ofFloatColor(1,1,1,1),
    ofFloatColor(0,0,0,0),
        ofFloatColor(1,1,1,1)};
    
    ofParameter<float> time {"time", 0, 0, DURATION};
    
    ofParameter<bool> pause {"pause" , false};

    
    ofParameterGroup camParams {"camera",
        camPos,
        camFov,
    };
    
    ofParameterGroup renderParams {"render",
        time,
        pause,
        renderChair,
        renderTunnel,
        renderReflection,
        renderShade,
        bgColor
    };
    
    ofParameterGroup chairParams {"chair",
        chairRotation,
        chairOffset,
        explodeAmount,
        autoRotationOffsetVelocity,
        autoRotationFactor
    };
    
    ofParameterGroup lightParams {"light",
        blurShadeScale,
        blurShadeRotation,
        lightPosition,
        rangeMin,
        rangeMax,
        shadowBias,
        shadowIntensity,
        minArea,
        maxArea,
        threshold,
        holes
    };
    
    ofParameterGroup params {"params",
        renderParams,
        camParams,
        chairParams,
        lightParams
    };
    
    
    ofShader fragShader;
    
    
    
    
    
    
    
    
};
