//
//  communication.cpp
//  version_1
//
//  Created by Julien Van Haeren on 07-03-17.
//
//

#include "communication.hpp"

void communication::setup(){
    
    
    std::vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();
    
    ofLogNotice("ofApp::setup") << "Connected Devices: ";
    
    for (std::size_t i = 0; i < devicesInfo.size(); ++i)
    {
        ofLogNotice("ofApp::setup") << "\t" << devicesInfo[i];
    }
    
    if (!devicesInfo.empty())
    {
        // Connect to the first matching device.
        bool success = device.setup(devicesInfo[0], 9600);
        
        if(success)
        {
            ofLogNotice("ofApp::setup") << "Successfully setup " << devicesInfo[0];
        }
        else
        {
            ofLogNotice("ofApp::setup") << "Unable to setup " << devicesInfo[0];
        }
        // Connect to the first matching device.
        bool success2 = device2.setup(devicesInfo[1], 9600);
        
        if(success2)
        {
            ofLogNotice("ofApp::setup") << "Successfully setup " << devicesInfo[1];
        }
        else
        {
            ofLogNotice("ofApp::setup") << "Unable to setup " << devicesInfo[1];
        }

    }
    else
    {
        ofLogNotice("ofApp::setup") << "No devices connected.";
    }
    
    
    
}

void communication::update(){
    
    
    // The serial device can throw exeptions.
    try
    {
        // Read all bytes from the device;
        uint8_t buffer[1024];
        
        while (device.available() > 0)
        {
            std::size_t sz = device.readBytes(buffer, 1024);
            
            for (std::size_t i = 0; i < sz; ++i)
            {
                std::cout << buffer[i];
            }
        }
        
    }
    catch (const std::exception& exc)
    {
        ofLogError("ofApp::update") << exc.what();
    }
}

void communication::draw(){
    
    
    
    ofDrawBitmapStringHighlight("Connected to " + device.getPortName(), ofVec2f(20, 20));
    ofDrawBitmapStringHighlight("See Console.", ofVec2f(20, 45));
    
    
    
    ofDrawBitmapString(motor1, 20, 150);
    ofDrawBitmapString(motor2, 20, 200);
    ofDrawBitmapString(motor3, 20, 250);
    ofDrawBitmapString(bSendSerialMessage, 100, 80);
    
    
    if(bSendSerialMessage){
        if(d==0){
            ofLogNotice("communication::sendData") << "Motor 1 adjusted :" + ofToString(motor1-prev1);
            ofLogNotice("communication::sendData") << "Motor 2 adjusted :" + ofToString(motor2-prev2);
            ofLogNotice("communication::sendData") << "Motor 3 adjusted :" + ofToString(motor3-prev3);
            
            byte1 = motor1-prev1;
            byte2 = motor2-prev2;
            byte3 = motor3-prev3;
            
            prev1 = motor1;
            prev2 = motor2;
            prev3 = motor3;
            
            device2.writeByte(byte1);
            device.writeByte(byte2);
            
            d++;
        }
    }
    if(plus){
        if (d == 0) {
            device2.writeByte(10);
            d++;
        }
    }
    if(minus){
        if (d == 0) {
            device2.writeByte(-10);
            d++;
        }
    }

    
}

void communication::sendData(int a, int b, int c){
    d=0;
    

    if(ofGetMouseX()>20 && ofGetMouseX()<85){
        if(ofGetMouseY()>65 && ofGetMouseY()<95){
            bSendSerialMessage = true;
        }
    }

    if(ofGetMouseX()>20 && ofGetMouseX()<85){
        if(ofGetMouseY()>105 && ofGetMouseY()<135){
            plus = true;
        }
    }

    if(ofGetMouseX()>20 && ofGetMouseX()<85){
        if(ofGetMouseY()>145 && ofGetMouseY()<175){
            minus = true;
        }
    }
    

    
    motor1 = a;
    motor2 = b;
    motor3 = c;
    
    
//    ofDrawBitmapString(motor1, 20, 150);
//    ofDrawBitmapString(motor2, 20, 200);
//    ofDrawBitmapString(motor3, 20, 250);
    
    
//    device.writeByte(1);
 
    
    ofLogNotice("communication::sendData") << "Motor 1 :" + ofToString(motor1);
    ofLogNotice("communication::sendData") << "Motor 2 :" + ofToString(motor2);
    ofLogNotice("communication::sendData") << "Motor 3 :" + ofToString(motor3);
}

void communication::mouseReleased(int x, int y, int button){
    
    bSendSerialMessage = false;
    plus = false;
    minus = false;
    
}










