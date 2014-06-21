#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    dir.allowExt("jpg");
    int nFiles = dir.listDir("imgs");
    curr = 0;
    
    if(nFiles) {
        string filePath = dir.getPath(curr);
        images.push_back(ofImage());
        images.back().loadImage(filePath);
            
            points.push_back(vector<ofVec2f>());
    } else printf("??? where the fuck is the folder 'imgs'??\n");
    highlighted = false;
    ofBackground(ofColor::white);
}

//--------------------------------------------------------------
void testApp::update(){
    if (points[curr].size() > 0) {
        highlighted = false;
        for (int i = 0; i < points[curr].size(); i++) {
            if (sqrt(((mouseX - points[curr][i].x) * (mouseX - points[curr][i].x)) + ((mouseY - points[curr][i].y) * (mouseY - points[curr][i].y)) < 7)) {
            hlIndex = i;
            highlighted = true;
            } else if (i == points[curr].size() - 1) { hlIndex == -1; }
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    static const std::string labels[48] = {"right wrist",
        "pinkie right base",
        "pinkie right lower joint",
        "pinkie right upper joint",
        "pinkie right tip",
        "pinkie top tip",
        "pinkie left tip",
        "pinkie left upper joint",
        "pinkie left lower joint",
        "pinkie left base",
        "pinkie ring crotch",
        "ring right base",
        "ring right lower joint",
        "ring right upper joint",
        "ring right tip",
        "ring top tip",
        "ring left tip",
        "ring left upper joint",
        "ring left lower joint",
        "ring left base",
        "ring middle crotch",
        "middle right base",
        "middle right lower joint",
        "middle right upper joint",
        "middle right tip",
        "middle top tip",
        "middle left tip",
        "middle left upper joint",
        "middle left lower joint",
        "middle left base",
        "middle index crotch",
        "index right base",
        "index right lower joint",
        "index right upper joint",
        "index right tip",
        "index top tip",
        "index left tip",
        "index left upper joint",
        "index left lower joint",
        "index left base",
        "index thumb crotch",
        "thumb right joint",
        "thumb right tip",
        "thumb top tip",
        "thumb left tip",
        "thumb left joint",
        "thumb left base",
        "left wrist"};

    if (dir.size() > 0){
        ofSetColor(255,255,255);
        images[curr].draw(0,0);
        
        images[curr].drawSubsection(0, 200, 100, 100, mouseX - 25, mouseY - 25, 50, 50);
        
        stringstream ss;
        ss << dir.getPath(curr) + ".pts" << endl;
        ss << "total number of points: " << points[curr].size() << endl;
        if (hlIndex >= 0) {
            ss << labels[hlIndex] << endl;
        } else { ss << "" << endl; }
        ofDrawBitmapString(ss.str().c_str(), 20, 20);
    }
    if (points[curr].size() > 0) {
        drawPoints(points[curr]);

    }
}

void testApp::drawPoints(vector<ofVec2f> pts){
    float cx;
    float cy;
    float  r;
    if (pts.size() > 0) {
        for (int i = 0; i < pts.size(); i++) {
            cx = pts[i].x;
            cy = pts[i].y;
            r  = 5;
            
            // draw ring around closest ellipse
            if (highlighted == true) {
                ofNoFill();
                ofSetColor(255, 0, 0);
                ofEllipse(pts[hlIndex].x, pts[hlIndex].y, 9, 9);
            }
            
            // draw actual point
            ofSetColor(255, 255, 255);
            ofFill();
            ofEllipse(cx, cy, r, r);
            if (0 < i) {
                ofLine(pts[i-1].x, pts[i-1].y, cx, cy);
            }
        }
    }
}

void testApp::exportFile(){
    string path = dir.getPath(curr) + ".pts";
    ofstream text;
    text.open(ofToDataPath(path).c_str());
    text << points[curr].size() << endl;
    for (int i = 0; i < points[curr].size(); i++) {
        text << points[curr][i].x << " " << points[curr][i].y << endl;
    }
    text.close();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch(key) {
        case 'u': //undo
            if (points[curr].size() > 0)
                points[curr].erase(points[curr].end());
            break;
        case 'f': //increment the files
            dragged = false;
            highlighted = false;
            if (dir.numFiles() > 0)
                curr = (curr + 1) % dir.numFiles();
            if (images.size() <= curr) {
                string filePath = dir.getPath(curr);
                images.push_back(ofImage());
                images.back().loadImage(filePath);
            
                points.push_back(vector<ofVec2f>());
            }
            break;
        case 'e': //export current file
            if (points[curr].size() > 0)
                exportFile();
            break;
        case 'w': //export all
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if (dragged == true) {
        points[curr][hlIndex].x = x;
        points[curr][hlIndex].y = y;
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if (highlighted == true) {
        dragged = true;
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    if (button == 0) {
        if (dragged == true) {
            dragged = false;
        } else {
            ofVec2f v(x,y);
            points[curr].push_back(v);
        }
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
