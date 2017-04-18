//
//  communication.hpp
//  version_1
//
//  Created by Julien Van Haeren on 07-03-17.
//
//

#ifndef communication_hpp
#define communication_hpp

#include <stdio.h>
#include <ofMain.h>
#include "ofxIO.h"
#include "ofxSerial.h"

class communication{
public:
    void setup();
    void update();
    void draw();
    void sendData(int a, int b, int c);
    void mouseReleased(int a, int b, int button);
    
    ofx::IO::SerialDevice device, device2;
   
    
    
    
    
    int motor1, motor2, motor3;
    int x, d, prev1, prev2, prev3, byte1, byte2, byte3;
    bool bSendSerialMessage, plus, minus; //buttonpressed
    
//    int i; //for loop
};

#endif /* communication_hpp */
