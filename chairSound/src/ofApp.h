#pragma once

#include "ofMain.h"
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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void droneLowButtonPressed();
    void droneHighButtonPressed();
    void clickButtonPressed();
    void pluckButtonPressed();
    
    ofSoundPlayer soundPlayerDroneLow;
    ofSoundPlayer soundPlayerDroneHigh;
    ofSoundPlayer soundPlayerClick;
    ofSoundPlayer soundPlayerPluck;

    ofxButton goDroneLow;
    ofxButton goDroneHigh;
    ofxButton goClick;
    ofxButton goTwang;
    ofxButton goPluck;
    
    //adjustable starting time for the low drone
    /*
    ofParameter<bool> droneLowPlaying {"playing", false};
    ofParameter<float> droneLowStart {"start (ms)", 0.0, 0.0, 1000};
    ofParameter<float> droneLowSpeed {"speed", 0.0, -3, 3};
    */

    
    ofParameter<float> droneLowVol {"droneLowVol", 1, 0.0, 1};
    ofParameter<float> droneHighVol {"droneHighVol", 1, 0.0, 1};
    ofParameter<float> clickVol {"clickVol", 1, 0.0, 1};
    ofParameter<float> pluckVol {"pluckVol", 1, 0.0, 1};
    
    
    ofParameter<float> clickRangeMin {"clickRangeMin", 0.8, 0.0, 1};
    ofParameter<float> clickRangeMax {"clickRangeMax", 1.2, 1, 2};

    ofParameter<float> pluckRangeMin {"pluckRangeMin", 0.8, 0.0, 1};
    ofParameter<float> pluckRangeMax {"pluckRangeMax", 1.2, 1, 2};
    
    /*
    ofParameterGroup droneLowGroup{"Drone Low",
        droneLowPlaying,
        droneLowStart,
        droneLowSpeed
    };
    */
    
    ofParameterGroup clickGroup{"Click",
        clickRangeMin,
        clickRangeMax,
        clickVol
    };

    ofParameterGroup pluckGroup{"Pluck",
        pluckRangeMin,
        pluckRangeMax,
        pluckVol
    };
    
    //bring it all together
    /*
    ofParameterGroup soundParams{"Sound",
        droneLowGroup,
        clickGroup,
        pluckGroup
    };
     */
    
    ofxPanel soundGui;
    
};
