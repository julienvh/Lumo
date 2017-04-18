#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    communication.setup();
    kinematics.setup();
    parameterGroup.add(kinematics.lineParameters);
    gui.setup(parameterGroup);
    gui.setPosition(1024-10-gui.getWidth(), 10);
}

//--------------------------------------------------------------
void ofApp::update(){
//    communication.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    kinematics.draw();
    gui.draw();
    buildButton();
    
//    communication.draw();
    
    
}

void ofApp::buildButton(){
    
    // Knoppen opzetten
    
    ofSetColor(0, 204, 204);
    if(ofGetMouseX()>20 && ofGetMouseX()<85){
        if(ofGetMouseY()>65 && ofGetMouseY()<95){
            ofSetColor(255,0,0);
        }
    }
    
    ofDrawRectangle(20, 65, 65, 30);
    
    ofSetColor(255,0,0);
    if(ofGetMouseX()>20 && ofGetMouseX()<85){
        if(ofGetMouseY()>105 && ofGetMouseY()<135){
            ofSetColor(0,204,204);
        }
    }
    ofDrawRectangle(20, 105, 65, 30);
    
    ofSetColor(255,0,0);
    if(ofGetMouseX()>20 && ofGetMouseX()<85){
        if(ofGetMouseY()>145 && ofGetMouseY()<175){
            ofSetColor(0,204,204);
        }
    }
    ofDrawRectangle(20, 145, 65, 30);
    
    ofSetColor(255,255,255);
    
    ofDrawBitmapString("EXECUTE", 25, 85);
    ofDrawBitmapString("+10", 40, 125);
    ofDrawBitmapString("-10", 40, 165);
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    kinematics.mouseDragged(x, y, button);
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
   
    
    // button press doorsturen
    

            kinematics.mousePressed(x, y, button);
    
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    kinematics.mouseReleased(x, y, button);
    
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
