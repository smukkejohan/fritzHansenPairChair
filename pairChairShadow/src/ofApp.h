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
    
    float autoRotationFactor;
    
    void customDraw() {
        
        partRotationOffset += explosionDirection;

        ofVec3f r = autoRotationFactor * partRotationOffset;
        
        if(r.x > 360) {
            r.x -= 360;
        }
        if(r.y > 360) {
            r.y -= 360;
        }
        if(r.z > 360) {
            r.z -= 360;
        }
        if(r.x < 360) {
            r.x += 360;
        }
        if(r.y < 360) {
            r.y += 360;
        }
        if(r.z < 360) {
            r.z += 360;
        }
        
        
        ofPushMatrix();
        
        //ofTranslate(mesh.getCentroid());
        //ofScale(0.5, 0.5, 0.5);
        //ofTranslate(-mesh.getCentroid());
        
        ofTranslate( explosionFactor * explosionDirection );
        
        
        ofRotateX(r.x);
        ofRotateY(r.y);
        ofRotateZ(r.z);
        
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

    ofParameter<ofVec3f> chairOffset {"offset", ofVec3f(0,0,0), ofVec3f(-4000,-4000,-4000), ofVec3f(4000,4000,4000)};
    ofParameter<ofVec3f> lightPosition {"pos", ofVec3f(0,0,0), ofVec3f(-8000,-8000,-8000), ofVec3f(8000,8000,8000)};
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
    
    
    ofParameter<bool> drawGui {"drawGui", true};

    
    ofParameter<float> blurShadeScale {"blur", 0, 0, 10};
    ofParameter<float> blurShadeRotation {"blurRot", 0, 0, PI};
    
    ofParameter<float> noiseFadeIn {"noiseIn", 0, 0, 1};
    ofParameter<float> invertNoise {"noiseInvert", 0, 0, 1};

    ofParameter<ofFloatColor> bgColor {"Background color",
        ofFloatColor(1,1,1,1),
    ofFloatColor(0,0,0,0),
        ofFloatColor(1,1,1,1)};
    
    
    ofParameter<float> shadeOpacity {"shadeOpacity", 255
        , 0, 255};
    ofParameter<float> reflectOpacity {"reflectOpacity", 255, 0, 255};

    ofParameter<float> tunnelOpacity {"tunnelOpacity", 255, 0, 255};
    
    ofParameter<float> time {"time", 0, 0, DURATION};
    
    ofParameter<int> tunnelLines {"tunnelLines", 0, 0, 10};
    
    ofParameter<float> smoothTunnel {"smoothTunnel", 0, 0, 20};
    
    ofParameter<float> noiseTunnel {"noiseTunnel", 0, 0, DURATION};

    
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
        bgColor,
        shadeOpacity,
        reflectOpacity,
        tunnelLines,
        smoothTunnel,
        noiseTunnel,
    };
    
    ofParameterGroup chairParams {"chair",
        chairRotation,
        chairOffset,
        explodeAmount,
        autoRotationFactor
    };
    
    ofParameterGroup lightParams {"light",
        tunnelOpacity,
        blurShadeScale,
        noiseFadeIn,
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
    
    int sceneNumber = -1;
    
    ofVec3f fromOffset;
    ofVec3f fromRotation;
    
    ofVec3f targetRotation;
    ofVec3f targetRotation2;
    
    ofVec3f fromLightPos;

    bool changeScene(int n) {
        if(n != sceneNumber) {
            sceneNumber = n;
            fromOffset = chairOffset.get();
            fromRotation = chairRotation.get();
            fromLightPos = lightPosition.get();
            return true;
        }
        return false;
    }
    
    
};
