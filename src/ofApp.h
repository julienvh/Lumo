#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxIO.h"
#include "ofxSerial.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void drawAxes();
    void direct(float a, float b);
    void inverse();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void sendSerial(float send);
    
    ofx::IO::SerialDevice device;
    
    ofxPanel gui;
    ofParameterGroup parameterGroup;
    ofParameterGroup lineParameters;
    ofParameter<int> angle;
    ofParameter<int> angle3;
    ofParameter<int> angle5;
    ofParameter<int> x;
    ofParameter<int> y;
    ofParameter<int> targetx;
    ofParameter<int> targety;
    ofParameter<int> length1;
    ofParameter<int> length2;
    
    int originX = 1024/2;
    int originY = 768/2;
    
    int d, prev;
    
    
    int ix, iy, n;
    float Xl1, Yl1, D, Xc, Yc, Xwc, Ywc, L1, L2, L31, L32, L3, fi, theta, theta1, theta2, theta3, angle2, Xcw, Ycw, Xcwd, Ycwd, angle4, angle6,  b, c, A, B, C, Xc8, Xcw8, Yc8, Ycw8, hoek, byte, dist_str, distance, dist, travelteller, travel, a, q, qOld, h, j;
    
    bool bSendSerialMessage;
    
};
