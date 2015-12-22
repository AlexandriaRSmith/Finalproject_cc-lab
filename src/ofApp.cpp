#include "ofApp.h"
#include "ofxInkSim.h"
#include "ofxInkSim.h"


void ofApp::setup()
{
    inkSim.setup();
  //  gui.setup(inkSim.getUniformInfo());
  // moodmachine.setSpeed(1.0);
    
    
    
    soundStream.listDevices();
    
    //if you want to set a different device id
    //soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    
    int bufferSize = 256;
    
    volHistory.assign(400, 0.0);
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    drawCounter		= 0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 2);
    //soundStream.setup(app, OutputChannels,InputChannels, sampleRate, bufferSize, nBuffers);
    
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // 256 samples per buffer
    // 2 num buffers (latency)
    
   // inkSim.setDrawMode(ofxInkSim::WATERFLOW);
    
    
   // inkSim.stroke(&brush, 5, 5, 5);
    
}
    //----------------------------
void ofApp::update()
{
    inkSim.update();

    //lets scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    //Record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger then the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
    
    
}
    

    
    
    //----------------------------

void ofApp::draw()
{
    inkSim.draw();
    gui.draw();
    
    
ofDrawBitmapStringHighlight("press 1 to start", 10, ofGetHeight() - 40);
    ofDrawBitmapStringHighlight("press 2 to stop", 10, ofGetHeight() - 20);

    
}
    //--------------------------------------------------------------
    void ofApp::audioIn(float * input, int bufferSize, int nChannels){
        float curVol = 0.0;
        
        // samples are "interleaved"
        int numCounted = 0;
        
        //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
        for (int i = 0; i < bufferSize; i++){
            left[i]		= input[i*2]*0.5;
            right[i]	= input[i*2+1]*0.5;
            
            curVol += left[i] * left[i];
            curVol += right[i] * right[i];
            numCounted+=2;
        }
        
        curVol /= (float)numCounted;
        
        // this is how we get the root of rms
        curVol = sqrt( curVol );
        
        smoothedVol *= 0.93;
        smoothedVol += 0.07 * curVol;
        

        
        bufferCounter++;
        
        float color = ofMap(scaledVol, 0.0, 0.17, 255, 10);
        ofColor c = color;

        
        cout << "scaledVol:  "<< scaledVol<< endl;

        if(scaledVol < 0.1){
            
            inkSim.setDrawMode(ofxInkSim::WATERFLOW);


            float color = ofMap(scaledVol, 0.0, 0.17, 235, 10);
            ofColor c = color;
            float tempX = ofMap(scaledVol, 0.0, 0.17,ofRandomWidth(), ofRandomHeight());
            float tempY = ofMap(scaledVol, 0.0, 0.17,ofRandomWidth(), ofRandomHeight());
            
          
    
          //  inkSim.stopStroke(&brush);


        }
        
        if(scaledVol > 0.1){
            inkSim.setDrawMode(ofxInkSim::INKFLOW);

            float color = ofMap(scaledVol, 0.0, 0.17, 250, 10);
            ofColor c = color;
            //  inkSim.stopStroke(&brush);
          //  inkSim.stroke(&brush, 5, 5, getInkColor(color));

            
            
        }
        

    }

    
    //------------

void ofApp::mouseDragged(int x, int y, int button)
{
    //ofColor c = moodmachine;
    /*
    float color = ofMap(scaledVol, 0.0, 0.17, 10, 235);
    ofColor c = color;
    float tempX = ofMap(scaledVol, 0.0, 0.17,ofRandomWidth(), ofRandomHeight());
    float tempY = ofMap(scaledVol, 0.0, 0.17,ofRandomWidth(), ofRandomHeight());


  
     inkSim.stroke(&brush, tempX, tempY, getInkColor(color));
    
*/
}
//----------------------------

void ofApp::mouseReleased(int x, int y, int button)
{
    //inkSim.stopStroke(&brush);
}
//----------------------------

void ofApp::keyPressed(int key)
{
    
    
  
  
    if (key == '1')
    {
        //float tempX = oldX + (ofGetWidth() * 0.05);
        // float tempY = oldY + (ofGetHeight() * 0.05);
        //  ofRandom(tempX, tempY);
        
        //  float ofRandom(-30, 20)
        
        float color = ofMap(scaledVol, 0.0, 0.17, 10, 235);
        ofColor c = color;
        float oldX = ofMap(scaledVol, 0.0, 0.17, ofRandomWidth(), ofRandomHeight());
        
        
        //pick random value within 5% 10% within the random range, see the wave form so you can view //the relationship between the sound and visual representation
        float oldY = ofMap(scaledVol, 0.0, 0.17,ofRandomWidth(), ofRandomHeight());
        
        float tempX = oldX + (ofGetWidth() * 0.05);
        float tempY = oldY + (ofGetHeight() * 0.05);
        
        float brushSize = 500;
        
        
        inkSim.stroke(&brush, tempX, tempY, getInkColor(color));
    

    }
   
   
    else if (key == '2')
    {
        inkSim.stopStroke(&brush);

       // inkSim.setDrawMode(ofxInkSim::INKSURF);
    }/*
    else if (key == '3')
    {
        inkSim.setDrawMode(ofxInkSim::INKFLOW);
    }
    else if (key == '4')
    {
        inkSim.setDrawMode(ofxInkSim::WATERFLOW);
    }
    else if (key == 'd')
    {
        inkSim.toggleDebug();
    }
      
        */
    
    if (key == ' ')
    {
        gui.toggleVisible();
    }
    else if (key == 'r')
    {
        gui.resetToDefault();
    }
    else if (key == 'c')
    {
        inkSim.clear();
    }
     
   
}
//----------------------------

void ofApp::keyReleased(int key){

}
//----------------------------

void ofApp::mouseMoved(int x, int y){
    
    


}

//----------------------------

void ofApp::mousePressed(int x, int y, int button){
    



}
//----------------------------

void ofApp::windowResized(int w, int h){

}
//----------------------------

void ofApp::gotMessage(ofMessage msg){
}
//----------------------------

void ofApp::dragEvent(ofDragInfo dragInfo){

}

//----------------------------
