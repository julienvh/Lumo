#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxIO.h"
#include "ofxSerial.h"
#include "kinematics.hpp"
#include "communication.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    void buildButton();

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
    
//    ofx::IO::SerialDevice dev ice;
    
    
    ofxPanel gui;
    
    ofParameterGroup parameterGroup;
    
    kinematics kinematics;
    
//    communication communication;
    
    bool bSendSerialMessage;
    
    


};


#ifndef _TEST_APP
#define _TEST_APP
#include “ofMain.h”
#include “ofxOpenCv.h”
#include “ofxCv.h”

class testApp : public ofBaseApp{
public:
    void setup(); //to setup a font fo this project
    void update();
    void draw(); //to draw the font on screen
    void keyPressed(int);                         //On KEY Press Events will be defined here
    void mouseMoved(int, int);            // On Mouse Move Events will be defined here
    void mousePressed(int x, int y, int button); //On Mouse Press Events will be defined here
    ofVideoGrabber movie;                          // movie object for capturing Video from Cam
    ofxCvColorImage rgb;                           //rgb object for storing color image data
    ofxCvGrayscaleImage filtered,red,green,blue;  //objects for storing grayscale image data
    ofxCvContourFinder contours;                         //object to store contours of the filtered image
    int w,h;
    
};

#endif
Now in testApp.cpp following code will be written :

#include “testApp.h”

int circleX, circleY,i, red, green, blue;
//————————————————————–
void testApp::setup(){
    ofSetFrameRate(100);
    ofBackground(150,50,10);
    w = 640;
    h = 480;
    movie.initGrabber(w, h, true);
    //reserve memory for cv images
    rgb.allocate(w, h);
    filtered.allocate(w, h);
    red.allocate(w,h);
    green.allocate(w,h);
    blue.allocate(w,h);
}

//————————————————————–
void testApp::update(){
    
    movie.update();
    
    if (movie.isFrameNew()) {
        
        //copy webcam pixels to rgb image
        rgb.setFromPixels(movie.getPixels(), w, h);
        
        //mirror horizontal
        rgb.mirror(false, true);
        
        //store the three channels as grayscale images
        
        rgb.convertToGrayscalePlanarImages(red, green, blue);
        
        green+=blue;   // adding green and blue channels then will subtract from red chanel to filter out only red
        red -=green;
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filtered.getPixels()[i] = ofInRange(red.getPixels()[i],0,40) ? 0 : 255;
        }
        
        filtered.flagImageChanged();
        //run the contour finder on the filtered image to find blobs with a certain hue
        contours.findContours(filtered, 50, w*h/2, 1, false);
    }
    
}

//————————————————————–

void testApp::draw(){
    ofSetColor(255,255,255);
    
    //draw all cv images
    red.draw(0,0);
    filtered.draw(0,480);
    contours.draw(0,480);
    
    ofSetColor(255, 255, 0);
    ofFill();
    
    //draw red circles for found blobs
    for (int i=0; i<contours.nBlobs; i++) {
        ofCircle(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y, 5);
    }
}

//—————————————————————
void testApp::keyPressed(int key){
    if(key == 115)
    {
        i– ;
    }
    if(key == 119)
    {
        i++ ;
    }
}

void testApp::mouseMoved(int x, int y){
    cout << “mouseMoved: ” << x << “, ” << y << endl;
    circleX = x;
    circleY = y;
}

void testApp::mousePressed(int x, int y, int button){
    //calculate local mouse x,y in image
    int mx = x % w;
    int my = y % h;
    
}
Now in Last main.cpp this code will be written :

#include “testApp.h”
#include “ofAppGlutWindow.h”

//————————————————————–
int main(){
    //ofAppGlutWindow window; // create a window
    // set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
    ofSetupOpenGL(1024, 768, OF_WINDOW);
    ofRunApp(new testApp()); // start the app
}
