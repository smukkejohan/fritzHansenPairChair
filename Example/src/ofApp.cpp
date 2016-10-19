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
    
    
    chairModel.loadModel("BH30_baseOrigin.obj");
    chairMesh = chairModel.getMesh(0);
    
    for(int i=0 ; i< chairModel.getNumMeshes(); i++){
        MyChairPart m = MyChairPart(chairModel.getMesh(i));
        parts.push_back(m);
        
    };

    //move to another method
    //parts.push_back(chairBack.loadModel("BH30_back_baseOrigin.obj"));
    chairSeat.loadModel("BH30_seat_baseOrigin.obj");
    chairBase.loadModel("BH30_base_baseOrigin.obj");
    chairLegs.loadModel("BH30_legs_baseOrigin.obj");
    chairFeet.loadModel("BH30_feet_baseOrigin.obj");
    
    /*    parts[0] = chairBack;    parts[1] = chairSeat;    parts[2] = chairBase;    parts[3] = chairLegs;    parts[4] = chairFeet;
    */
    
    nParts = 5;
    
    for(int i;i<nParts;i ++){
        ofPoint partCenter(0,0,0);
        partsPos[i] = partCenter;
        partsPosInit[i]= partCenter;

        ofVec3f tempVector(0,0,0);
        partsVec[i] = tempVector;
        partsVecInit[i] = tempVector;
    }
    prepareExplodedParts();
    //endmove


    goExplode.addListener(this, &ofApp::explodeButtonPressed);
    
    //gui setups
    gui.setup(params);
    gui.add(displayModel.setup("display model", false) );
    gui.add(displayParts.setup("display parts", false) );
    gui.add(explodeParts.setup("explode parts", false) );
    gui.add(explosionRadius.setup("explode radius", 1000, 10, 5000));
    gui.add(explosionSpeed.setup("explosion interperlation", 0.01, 0, 1));
    gui.add(goExplode.setup("Change explosion now tnks"));

    
    fragShader = initFragShader();
    

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
        //ofRotateX( cos( ofGetElapsedTimef() * 2.3) * sin( ofGetElapsedTimef() ) * RAD_TO_DEG );
        //ofRotateY( sin( ofGetElapsedTimef() ) * RAD_TO_DEG );
        //ofTranslate(chairOffset.get());
        
        /*
        if(explodeParts){
            for(int i = 0; i < nParts; i++){

                ofPushMatrix();
         
                //float time = ofGetElapsedTimef();    //Get time in seconds
                //float angle = time * 10; //Compute angle. We rotate at speed
                //10 degrees per second
                //ofRotate( angle, 0, 1, 0 );    //Rotate the coordinate system
         
                 
                ofTranslate(chairPartsPos[i].x, chairPartsPos[i].y);
                chairParts[i].drawFaces();
                ofPopMatrix();
            }
        }else{
            chairModel.drawFaces();
        }*/
        
    
    ofSetColor( 241,212,55 );
    ofPushMatrix(); {
        ofTranslate(5, 0, 0 );
        //ofRotate(180, 1, 0, 0 );
        
        ofTranslate(guiChairOffset.get());
        //ofRotateX( cos( ofGetElapsedTimef() * 2.3) * sin( ofGetElapsedTimef() ) * RAD_TO_DEG );
        //ofRotateY( sin( ofGetElapsedTimef() ) * RAD_TO_DEG );
        
        ofRotateX(guiChairRotation.get().x);
        ofRotateY(guiChairRotation.get().y);
        ofRotateZ(guiChairRotation.get().z);
        //make adjustable scale
        //ofScale( 0.015, 0.015, 0.015 );
        ofScale(guiChairScale.get().x, guiChairScale.get().y, guiChairScale.get().z);

        
        if(isDepthPass) { //true if displayModel is true

            //move out of this block?
            if(explodeParts){
                //float angle = (sin( ofGetElapsedTimef() ) * RAD_TO_DEG)/50; //Compute angle. We rotate at speed

                for(auto & part : parts){
                    part.draw();
                }
            }else{

                //put the parts back together
                /*
                float angle = 10; //Compute angle. We rotate at speed
                for(int i = 0; i < nParts; i++){
                    ofVec3f tempVec = partsPos[i].getInterpolated(partsPosInit[i], explosionSpeed);
                    //chairParts[i].setPosition(chairPartsPos[i].x, chairPartsPos[i].y, chairPartsPos[i].z);
                    parts[i].setPosition(tempVec.x, tempVec.y, tempVec.z);
                    partsPos[i] = tempVec;
                    
                    //ofPoint axis = ofPoint(1.0, 0.0, 0.0);
                    int numRotation = parts[i].getNumRotations();
                    parts[i].stopAllAnimations();
                    
                }
                 */
                    
            }
            
            if(displayParts){
                for(int i = 0; i < nParts; i++){
                  //  parts[i].drawFaces();
                }
            }else{
              //  chairModel.drawFaces();
            }
        }
        //chairMesh.draw();
    } ofPopMatrix();
    

    
    // floor //
    ofSetColor( 142,187,151 );

    fragShader.begin();
    fragShader.setUniform1f("u_width", 800.0);
    fragShader.setUniform1f("u_height", 600.0);
    fragShader.setUniform1f("u_time", ofGetElapsedTimef());
    

    ofDrawBox( 0, 5, 0, 250, 2, 250 );
    fragShader.end();
    
    
    // wall //
    //ofDrawBox(0, -8, 10, 80, 30, 2 );
    
    
    //add spheres of light for debugging
    //ofDrawSphere( light.getPosition(), 1 );
    
    

    ofSetColor(255);
    

}

//--------------------------------------------------------------
void ofApp::prepareExplodedParts() {
/*
    //init explosion field
    for (int i=0; i<nParts; i++) {     //Scan all the parts
        ofPoint partExpCenter( ofRandom( -1, 1 ),
                           ofRandom( -1, 1 ),
                           ofRandom( -1, 1 ) );
        partExpCenter.normalize(); //Normalize vector's length to 1
        partExpCenter *= explosionRadius;      //Now the center vector has
        partsPosExplode[i] = partExpCenter;
        
        
        ofVec3f partExpVec(ofRandom( -1, 1 ),
                        ofRandom( -1, 1 ),
                        ofRandom( -1, 1 ));
        partExpVec.normalize();
        partsVecExplode[i] = partExpVec;
    }

*/
    for(auto & part : parts ){
        ofPoint partExpCenter( ofRandom( -1, 1 ),
                              ofRandom( -1, 1 ),
                              ofRandom( -1, 1 ) );
        
        part.offset = partExpCenter;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        prepareExplodedParts();
    }
}

            
//--------------------------------------------------------------
void ofApp::explodeButtonPressed(){
    prepareExplodedParts();
}


//--------------------------------------------------------------
ofShader ofApp::initFragShader(){

    ofShader fragShader;
    string initString = STRINGIFY(

          #ifdef GL_ES
          precision mediump float;
          #endif
          
          //uniform vec2 u_resolution;
                                  
          //uniform vec2 u_mouse;
          uniform float u_time;
          uniform float u_width;
          uniform float u_height;
                                  
          vec2 random2(vec2 st){
              st = vec2( dot(st,vec2(127.1,311.7)),
                        dot(st,vec2(269.5,183.3)) );
              return -1.0 + 2.0*fract(sin(st)*43758.5453123);
          }
          
          // Value Noise by Inigo Quilez - iq/2013
          // https://www.shadertoy.com/view/lsf3WH
          float noise(vec2 st) {
              vec2 i = floor(st);
              vec2 f = fract(st);
              
              vec2 u = f*f*(3.0-2.0*f);
              
              return mix( mix( dot( random2(i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
                              dot( random2(i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                         mix( dot( random2(i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ), 
                             dot( random2(i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
          }
          
          void main() {
              //vec2 st = gl_FragCoord.xy/u_resolution.xy;
              vec2 st = vec2(gl_FragCoord.x/u_width, gl_FragCoord.y/u_height);
              //st.x *= u_resolution.x/u_resolution.y;
              st.x *= u_width/u_height;
              vec3 color = vec3(0.0);
              
              float t = 1.0;
              // Uncomment to animate
              t = abs(1.0-sin(u_time*.1))*5.;
              // Comment and uncomment the following lines:
              st += noise(st*2.)*t; // Animate the coordinate space
              color = vec3(1.) * smoothstep(.18,.2,noise(st)); // Big black drops
              //color += smoothstep(.15,.2,noise(st*10.)); // Black splatter
              color -= smoothstep(.35,.4,noise(st*10.)); // Holes on splatter
              
              gl_FragColor = vec4(1.-color,1.0);
          }

    );
    /*
    
    //redefine the initString with a simple example
    initString = STRINGIFY(
 //        uniform vec2 u_resolution;
                           uniform float u_width;
                           uniform float u_height;
//       uniform float u_time;
          
          void main(){
              vec2 st = vec2(gl_FragCoord.x/u_width, gl_FragCoord.y/u_height);
              //st.x *= width/height;
              st.x *= u_width/u_height;
              vec3 color = vec3(0.0);
              float d = 0.0;
              
              // Remap the space to -1. to 1.
              st = st *2.-1.;
              
              // Make the distance field
              d = length( abs(st)-.3 );
              // d = length( min(abs(st)-.3,0.) );
              // d = length( max(abs(st)-.3,0.) );
              
              // Visualize the distance field
              gl_FragColor = vec4(vec3(fract(d*10.0)),1);
          }

    );
    initString = STRINGIFY(
           uniform float myWidth;
           uniform float myHeight;
           
           void main(){
                float windowWidth = myWidth;
                float windowHeight = myHeight;
                
                float r = gl_FragCoord.x / windowWidth;
                float g = gl_FragCoord.y / windowHeight;
                float b = 0.7;
                float a = 0.5;
                gl_FragColor = vec4(r, g, b, a);
           }
    );
    */
    
    fragShader.setupShaderFromSource( GL_FRAGMENT_SHADER, initString);
    fragShader.linkProgram();
    
    return fragShader;
}

//--------------------------------------------------------------
ofShader ofApp::beginFragShader(ofShader fragShader){
    fragShader.begin();
    //fragShader.setUniform1f("u_time", ofGetElapsedTimef() );
    return fragShader;
}

//--------------------------------------------------------------
void ofApp::exit(){
    goExplode.removeListener(this, &ofApp::explodeButtonPressed);
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
