#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    lineParameters.setName("controls");
    lineParameters.add(angle.set("bottom angle",-180,-180,-80));
    lineParameters.add(angle3.set("middel angle",-5,-80,30));
    lineParameters.add(angle5.set("top angle",0,-45,45));
    lineParameters.add(length1.set("bottom length",200,0,300));
    lineParameters.add(length2.set("middel length",200,0,300));
    lineParameters.add(x.set("x",0,-180,1800));
    lineParameters.add(y.set("y",0,-180,1800));
    lineParameters.add(targetx.set("targetx",0,-1200,1200));
    lineParameters.add(targety.set("targety",0,-800,800));
    parameterGroup.add(lineParameters);
    gui.setup(parameterGroup);
    gui.setPosition(1024-10-gui.getWidth(), 10);
    

    
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
    }
    else
    {
        ofLogNotice("ofApp::setup") << "No devices connected.";
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
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
        
        // Send some new bytes to the device to have them echo'd back.
        std::string text = "Frame Number: " + 10;
        
        ofx::IO::ByteBuffer textBuffer(text);
        
        
        
//        device.writeBytes(textBuffer);
//        ofLogNotice("ofApp::setup") << (textBuffer);
        
    }
    catch (const std::exception& exc)
    {
        ofLogError("ofApp::update") << exc.what();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    drawAxes();
    //    direct();
    inverse();
    gui.draw();
 

   
    
//    ofBackgroundGradient(ofColor::white, ofColor::black);
    // Knop opzetten
    
    ofSetColor(0, 204, 204);
    if(ofGetMouseX()>20 && ofGetMouseX()<85){
        if(ofGetMouseY()>65 && ofGetMouseY()<95){
            ofSetColor(255,0,0);
        }
    }
    
    ofDrawRectangle(20, 65, 65, 30);
    ofSetColor(255,255,255);
    ofDrawBitmapString("EXECUTE", 25, 85);
    
    ofDrawBitmapStringHighlight("Connected to " + device.getPortName(), ofVec2f(20, 20));
    ofDrawBitmapStringHighlight("See Console.", ofVec2f(20, 45));
    
}
//--------------------------------------------------------------
void ofApp::drawAxes(){
    ofSetLineWidth(1);
    ofSetColor(255,255,255);
    ofDrawLine(originX-400, originY, originX+400, originY);
    ofDrawLine(originX, originY-400, originX, originY+400);
}
void ofApp::direct(float a, float b){
    angle2 = a * (pi/180) ;
    angle4 = b * (pi/180) ;
    angle6 = angle5 * 0.01745329252;
    
    L1 = length1;
    L2 = length2;
    L31= 30;
    L32= 40;
    L3 = sqrt((L31*L31) + (L32*L32));
    
    Yc = (sin(float(angle2))) *L1;
    Xc = (cos(float(angle2))) *L1;
    Ycw = (sin(float(angle4))) *L2;
    Xcw = (cos(float(angle4))) *L2;
    Yc8 = (sin(float(angle2))) *(L1+100);
    Xc8 = (cos(float(angle2))) *(L1+100);
    Ycw8 = (sin(float(angle4))) *(L2+100);
    Xcw8 = (cos(float(angle4))) *(L2+100);
    Ycwd = (sin(float(angle6))) *L3;
    Xcwd = (cos(float(angle6))) *L3;
    ofSetLineWidth(10);
    
    ofSetColor(255,0,0);
    ofDrawLine(originX, originY , originX+Xc, originY+Yc);
    
    ofSetColor(0,255,0);
    ofDrawLine(originX+Xc, originY+Yc, originX+Xc+Xcw, originY+Yc+Ycw);
    
    ofSetColor(0,0,255);
    ofSetLineWidth(30);
    ofDrawLine(originX+Xc+Xcw, originY+Yc+Ycw,  originX+Xc+Xcw+Xcwd, originY+Yc+Ycw+Ycwd);
    
    ofSetColor(255,255,255);
    ofSetLineWidth(1);
    ofDrawLine(originX, originY, originX+Xc+Xcw+Xcwd, originY+Yc+Ycw+Ycwd);
    ofDrawLine(originX, originY, originX+Xc+Xcw, originY+Yc+Ycw);
    ofSetColor(0, 0, 0);
    ofDrawLine(originX, originY, originX-300, originY);
    ofDrawLine(originX, originY , originX+Xc8, originY+Yc8);
    ofDrawLine(originX+Xc, originY+Yc, originX+Xc+Xcw8, originY+Yc+Ycw8);
    
    
    
    if((a+180<0)||(a+180>120)){
        ofSetColor(255,0,0);
        ofDrawBitmapString("NEE", originX,originY);
    }
    if((b-a<30)||(b-a>170)){
        ofSetColor(255,0,0);
        ofDrawBitmapString("NEE", originX,originY);
    }
    
    ofFill();
    
    ofDrawBitmapString(qOld, 200, 520);
    q = a + 180;
    dist = q-qOld;
    ofDrawBitmapString(dist, 200, 620);
    ofDrawBitmapString(travel, 200, 580);
    ofDrawBitmapString(travelteller, 200, 600);
    int i = (int)(q + 0.5f);
    ofDrawBitmapString(i, 200, 650);

    if(bSendSerialMessage){
        if(d==0){
            device.writeByte(q-prev);
            d++;
            prev = q;
        }
        
    }
    
    qOld = q;
   
    ofDrawBitmapString(q, 200, 500);
    
    
    
    ofDrawBitmapString(Xc+Xcw, 200, 200 );
    ofDrawBitmapString(Yc+Ycw, 300, 200);
    
    ofDrawBitmapString(a+180, 800, 500);
    ofDrawBitmapString(b-a, 800, 525);
    ofDrawBitmapString(angle5-b, 800, 550);
    ofDrawBitmapString(int((a+180)+0.5), 900, 500);
    ofDrawBitmapString(int((b-a)+0.5), 900, 525);
    ofDrawBitmapString(int((angle5-b)+0.5), 900, 550);

}
void ofApp::inverse(){
    a = length1;
    b = length2;
    
    L31= 30;
    L32= 40;
    L3 = sqrt((L31*L31) + (L32*L32));
    
    
    Yc = (targety - originY)*-1;
    Xc = (originX - targetx + L3)*-1;
    Xwc = Xc;
    Ywc = Yc;
    
    D = (pow(Xwc, 2)+pow(Ywc, 2)-pow(L1, 2)-pow(L2, 2))/(2*L1*L2);
    theta3 = atan2((sqrt(1-pow(D,2))),D);
    theta2 = (atan2(Xwc, Ywc)) - atan2( (sin(theta3)*L2), L1 + (cos(theta3)*L2));
    
    ofDrawBitmapString(theta3/ 0.01745329252, 300, 500);
    ofDrawBitmapString(theta2/ 0.01745329252, 300, 550);
    ofDrawCircle(Xc, Yc, 5);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 5);
    
    ofDrawBitmapString(Xc, 400, 500);
    ofDrawBitmapString(Yc, 400, 550);
    
    theta2 = theta2 / (pi/180);
    theta2 = -90 + theta2;
    theta3 = theta3 / (pi/180);
    theta3 = theta3 +theta2;
    
    ofDrawBitmapString(theta3, 500, 600);
    ofDrawBitmapString(theta2, 500, 650);
    ofDrawBitmapString(theta3-theta2, 500, 700);
    
    
    direct(theta2, theta3);
    
}
void ofApp::mouseDragged(int x, int y, int button){
    targetx = x;
    targety = y;
   
}

void ofApp::mousePressed(int x, int y, int button){
    if(ofGetMouseX()>20 && ofGetMouseX()<85){
        if(ofGetMouseY()>65 && ofGetMouseY()<95){
            d = 0;
            bSendSerialMessage= true;
            
        }
    }
    
}

void ofApp::mouseReleased(int x, int y, int button){
    bSendSerialMessage = false;
}
