#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    
    ofGLFWWindowSettings mainSettings;
    
    mainSettings.resizable = false;
    //mainSettings.setGLVersion(3, 2);
    mainSettings.decorated = false;
    //mainSettings.setPosition(ofPoint(0,0));
    mainSettings.windowMode = OF_FULLSCREEN;
    
    cout << mainSettings.glVersionMajor << " : " << mainSettings.glVersionMinor << endl;
    
    mainSettings.width = 1920;
    mainSettings.height = 1080;
    
    
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(mainSettings);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    
	//ofSetupOpenGL(1920,1080,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(mainWindow, mainApp);
    
    ofRunMainLoop();


}
