//
//  kinematics.hpp
//  version_1
//
//  Created by Julien Van Haeren on 07-03-17.
//
//

#ifndef kinematics_hpp
#define kinematics_hpp

#include <stdio.h>
#include <ofMain.h>
//#include "ofApp.h"
#include "communication.hpp"

class kinematics{
public:
    
    communication communication;
    
    void setup();
    void update();
    void draw();
    void inverse();
    void direct(float a, float b);
    void drawaxes();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
   
    
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
    
    
    int ix, iy, n, draai1, draai2, draai3;
    float Xl1, Yl1, D, Xc, Yc, Xwc, Ywc, L1, L2, L31, L32, L3, fi, theta, theta1, theta2, theta3, angle2, Xcw, Ycw, Xcwd, Ycwd, angle4, angle6,  b, c, A, B, C, Xc8, Xcw8, Yc8, Ycw8, hoek, byte, dist_str, distance, dist, travelteller, travel, a, q, qOld, h, j;
    
//    bool bSendSerialMessage;
    
//    ofx::IO::SerialDevice device;
};

#endif /* kinematics_hpp */
