//
//  kinematics.cpp
//  version_1
//
//  Created by Julien Van Haeren on 07-03-17.
//
//

#include "kinematics.hpp"



void kinematics::setup(){
    
    communication.setup();
    
    //  GUI setup met parameters voor de 2d representatie van de lamp
    
    lineParameters.setName("controls");
    lineParameters.add(angle.set("bottom angle",-180,-180,-80));
    lineParameters.add(angle3.set("middel angle",-5,-80,30));
    lineParameters.add(angle5.set("top angle",0,-45,45));
    lineParameters.add(length1.set("bottom length",200,0,300));
    lineParameters.add(length2.set("middel length",200,0,300));
    lineParameters.add(x.set("x",0,-180,1800));
    lineParameters.add(y.set("y",0,-180,1800));
    lineParameters.add(targetx.set("targetx",362,500,800));
    lineParameters.add(targety.set("targety",183,50,350));

}

void kinematics::update(){
    
}

void kinematics::draw(){
    
    communication.update();
    communication.draw();
    drawaxes();
    inverse();
    
    
    
    
}

void kinematics::drawaxes(){
    
    //  Teken het assenstelsel
    
    ofSetLineWidth(1);
    ofSetColor(255,255,255);
    ofDrawLine(originX-400, originY, originX+400, originY);
    ofDrawLine(originX, originY-400, originX, originY+400);
}

void kinematics::inverse(){
    
    //  Bereken de benodigde hoeken vanuit een gegeven eindpositie

    
    L31= 30;
    L32= 40;
    L3 = sqrt((L31*L31) + (L32*L32));
    
    
    Yc = (targety - originY)*-1;
    Xc = (originX - targetx + L3)*-1;
    Xwc = Xc;
    Ywc = Yc;
    
    //  Dit is eigenlijk het rekenwerk, wordt verderop vertaald naar daadwerkelijke draaiingshoeken

    D = (pow(Xwc, 2)+pow(Ywc, 2)-pow(L1, 2)-pow(L2, 2))/(2*L1*L2);
    theta3 = atan2((sqrt(1-pow(D,2))),D);
    theta2 = (atan2(Xwc, Ywc)) - atan2( (sin(theta3)*L2), L1 + (cos(theta3)*L2));

    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 5);
    
    //
    
    theta2 = theta2 / (pi/180);
    theta2 = -90 + theta2;
    theta3 = theta3 / (pi/180);
    theta3 = theta3 +theta2;
    
    
    direct(theta2, theta3);
    
}
void kinematics::direct(float a, float b){
    
    //  Nu gaan we de berekende waarden gebruiken om een representatie te tekeken met lijnen
    
    angle2 = a * (pi/180) ;
    angle4 = b * (pi/180) ;
    angle6 = angle5 * 0.01745329252;
    
    L1 = length1;
    L2 = length2;
    L31= 30;
    L32= 40;
    L3 = sqrt((L31*L31) + (L32*L32));
    
    //  Pythagoras om te berekeken wat de posities van de lijnpunten zijn
    
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
    
    //  Lijnen tekeken
    
    
    ofSetLineWidth(10);
    
    ofSetColor(255,0,0);
    ofDrawLine(originX, originY , originX+Xc, originY+Yc);
    
    ofSetColor(0,255,0);
    ofDrawLine(originX+Xc, originY+Yc, originX+Xc+Xcw, originY+Yc+Ycw);
    
    ofSetColor(0,0,255);
    ofSetLineWidth(30);
    ofDrawLine(originX+Xc+Xcw, originY+Yc+Ycw,  originX+Xc+Xcw+Xcwd, originY+Yc+Ycw+Ycwd);
    
    //  Hulplijnen tekeken
    
    ofSetColor(255,255,255);
    ofSetLineWidth(1);
    ofDrawLine(originX, originY, originX+Xc+Xcw+Xcwd, originY+Yc+Ycw+Ycwd);
    ofDrawLine(originX, originY, originX+Xc+Xcw, originY+Yc+Ycw);
    ofSetColor(0, 0, 0);
    ofDrawLine(originX, originY, originX-300, originY);
    ofDrawLine(originX, originY , originX+Xc8, originY+Yc8);
    ofDrawLine(originX+Xc, originY+Yc, originX+Xc+Xcw8, originY+Yc+Ycw8);
    
    //  Hier kunnen/moeten restricties ingezet worden
    
    if((a+180<0)||(a+180>120)){
        ofSetColor(255,0,0);
        ofDrawBitmapString("NEE", originX,originY);
    }
    if((b-a<30)||(b-a>170)){
        ofSetColor(255,0,0);
        ofDrawBitmapString("NEE", originX,originY);
    }
    
    ofFill();
    
    //  Hoeken vertalen naar hoeken op basis van de beginpositie voor de onderste arm, de andere armen op basis van de arm voor diegene. Afronden voor het verzenden via een seriele verbinding naar arduino
    
    draai1 = int((a+180)+0.5f);
    draai2 = int((b-draai1)+0.5f);
    draai3 = int((angle5-draai2)+0.5f);
    
    //  Hoeken tonen op scherm
    
    ofDrawBitmapString(draai1, 200, 200);
    ofDrawBitmapString(draai2, 200, 300);
    ofDrawBitmapString(draai3, 200, 400);

    
    
//    communication.sendData(draai1, draai2, draai3);
    
    //  Stuur de hoeken door naar de communicatie class
    
    
}



void kinematics::mouseDragged(int x, int y, int button){
    targetx = x;
    targety = y;
//    communication.sendData(draai1, draai2, draai3);
}
void kinematics::mousePressed(int x, int y, int button){
    communication.sendData(draai1, draai2, draai3);

}
void kinematics::mouseReleased(int x, int y, int button){
    communication.mouseReleased(x, y, button);
}



