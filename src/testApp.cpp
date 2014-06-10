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
    
    ofBackground(ofColor::white);
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    static const std::string labels[49] = {"", "right wrist",
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
        "left wrist" };

    if (dir.size() > 0){
        images[curr].draw(0,0);
        
        stringstream ss;
        ss << dir.getPath(curr) + ".pts" << endl;
        ss << "total number of points: " << points[curr].size();
        ss << labels[points[curr].size()];
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
        case 'u':
            if (points[curr].size() > 0)
                points[curr].erase(points[curr].end());
            break;
        case 'f':
            if (dir.numFiles() > 0)
                curr = (curr + 1) % dir.numFiles();
            if (images.size() <= curr) {
                string filePath = dir.getPath(curr);
                images.push_back(ofImage());
                images.back().loadImage(filePath);
            
                points.push_back(vector<ofVec2f>());
            }
            break;
        case 'e':
            if (points[curr].size() > 0)
                exportFile();
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    if (button == 0) {
        ofVec2f v(x,y);
        points[curr].push_back(v);
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
