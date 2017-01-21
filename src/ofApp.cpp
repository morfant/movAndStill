#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // IMAGES
    infoDrawing[0].load("images/infoDrawing_0.jpg");
    infoDrawing[1].load("images/infoDrawing_1.jpg");
    infoDrawing[2].load("images/infoDrawing_2.jpg");
    infoDrawing[3].load("images/infoDrawing_3.jpg");
//    infoDrawing[4].load("images/infoDrawing_3.jpg");
    
    // CAMERA
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
    
    if (!imageMode) {
        // first video update - NOT WORKING!!
        if (curTimef == 0.0f){
            vidGrabber.update();
            ofLog(OF_LOG_NOTICE, "first video updated!");
        }
        
        if (stillCutMode) {
            // Insert interval between frames
            curTimef = ofGetElapsedTimef();
            timeDiff = curTimef - prevTimef;
            if (timeDiff >= stillCutInterval) {
                vidGrabber.update();
                prevTimef = curTimef;
            }
        } else {
            vidGrabber.update();
        }
    } else if (imageMode) {
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (!imageMode) {
        vidGrabber.draw(20, 20);
    
    } else if (imageMode) {
        infoDrawing[curImageIdx].draw(0, 0, ofGetWidth(), ofGetHeight());
//        infoDrawing[curImageIdx].draw(0, 0);
    }
    
    
    ofSetHexColor(0xffffff);
    ofDrawBitmapString(stillCutMode_str, margin_left, ofGetHeight() - margin_bottom);
    ofDrawBitmapString(ofToString(roundf(timeDiff*100)/100) + " / " + ofToString(stillCutInterval) +
                       " curImgIdx: " + ofToString(curImageIdx), margin_left + 250, ofGetHeight() - margin_bottom);
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
//        stillCutMode = !stillCutMode;
        imageMode = false;
        stillCutMode = true;
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
    
    
    if (key == 'i' || key == 'I') {
//        imageMode = !imageMode;
        if (!imageMode) {
            stillCutMode = false;
            imageMode = true;
        
            if (curImageIdx < IMAGE_IDX_MAX){
                curImageIdx++;
            }
            
            if (imageMode) {
                imageMode_str = "imageMode : true";
            } else {
                imageMode_str = "imageMode : false";
            }
            
            ofLog(OF_LOG_NOTICE, imageMode_str);
        }
    }


    if (key == 'v' || key == 'V'){
        imageMode = false;
        stillCutMode = false;
        
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
