#pragma once

#include <iostream>
#include <fstream>
#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void drawPoints(vector<ofVec2f> pts);
        void exportFile();
    
        ofDirectory dir;
        vector<ofImage> images;
        vector< vector<ofVec2f> >  points;
        string path;        // path to images
        int curr;           // current image index
        bool highlighted;   // is something highlighted
        bool dragged;       // dragging things
        int hlIndex;        // highlight index
    
};

/*
  time sheet:
    WHAT DAY?           START       END         TIME
    MARCH 16 2014       03:00P      03:10P      010MIN
    MARCH 20 2014       11:20A      12:39P      079MIN
    MARCH 28 2014       11:00A      11:30A      030MIN
    MARCH 29 2014       12:51P      01:04P      013MIN
    APRIL 03 2014       11:25P      12:10A      045MIN
    APRIL 04 2014       10:54A      12:19P      085MIN
    APRIL 04 2014       12:35P      12:57P      022MIN
                                                ======
                                                284MIN
    --------------------------------------------------
 
    APRIL 08 2014       11:20A
*/
