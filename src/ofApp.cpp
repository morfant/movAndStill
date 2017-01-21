#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camWidth = 320;  // try to grab at this size.
    camHeight = 240;

    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();

    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(camWidth, camHeight);

//    videoInverted.allocate(camWidth, camHeight, OF_PIXELS_RGB);
//    videoTexture.allocate(videoInverted);
    ofSetVerticalSync(true);
}


//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0, 0, 0);
    
    
    curTimef = ofGetElapsedTimef();
    timeDiff = curTimef - prevTimef;
    if (timeDiff >= stillCutInterval) {
        vidGrabber.update();
        prevTimef = curTimef;
    }

//    if(vidGrabber.isFrameNew()){
//        ofPixels & pixels = vidGrabber.getPixels();
//        for(int i = 0; i < pixels.size(); i++){
//            videoInverted[i] = 255 - pixels[i];
//        }
//        videoTexture.loadData(videoInverted);
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    vidGrabber.draw(20, 20);
//    videoTexture.draw(20 + camWidth, 20, camWidth, camHeight);
    
    
    
    ofSetHexColor(0xffffff);
    ofDrawBitmapString(stillCutMode_str, margin_left, ofGetHeight() - margin_bottom);
    ofDrawBitmapString(ofToString(roundf(timeDiff*100)/100) + " / " + ofToString(stillCutInterval), margin_left + 250, ofGetHeight() - margin_bottom);
//    ofDrawBitmapString(ofToString(stillCutInterval), margin_left + 500, ofGetHeight() - margin_bottom);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // in fullscreen mode, on a pc at least, the 
    // first time video settings the come up
    // they come up *under* the fullscreen window
    // use alt-tab to navigate to the settings
    // window. we are working on a fix for this...

    // Video settings no longer works in 10.7
    // You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343
    if(key == 's' || key == 'S'){
        stillCutMode = !stillCutMode;
        if (stillCutMode) {
            stillCutMode_str = "stillCutMode : true";
        } else {
            stillCutMode_str = "stillCutMode : false";
        }
        
        
        ofLog(OF_LOG_NOTICE, stillCutMode_str);
    }
    
    
    if (key == '+' || key == '=') {
        if (stillCutInterval <= (INTERVAL_MAX - INTERVAL_STEP)) stillCutInterval+=INTERVAL_STEP;
    }
    
    if (key == '_' || key == '-') {
        if (stillCutInterval >= (INTERVAL_MIN + INTERVAL_STEP)) stillCutInterval-=INTERVAL_STEP;
    }
    
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
void ofApp::mouseEntered(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
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
