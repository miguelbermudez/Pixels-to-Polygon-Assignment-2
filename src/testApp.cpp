#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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

//--------------------------------------------------------------
void testApp::readAndParseCSV() 
{
    stock_entry stock;
    string line;
    int pos;
    int index; 
    int lineIndex;
    
    ifstream in("data/test.csv");
    if (!in.is_open())
    {
        printf("can't open the file");
        return;
    }
    
    index = 0;
    lineIndex = 1;
    
    while ( getline( in, line ) ) {
        index = 0;
        while ( (pos = line.find(',')) >= 0 || index == 6 ) {
            string field = line.substr(0, pos);
            line = line.substr(pos+1);
                //array->push_back(field);
            cout << index << ": " << field << endl;    //debugging
            
            index++;
                //cout << "\tline: " << line << ", index: " << index << endl;   //debugging
        }  
        cout << endl;
        cout << "Line: " << lineIndex << endl; //debugging
        lineIndex++;
    }
    return;
}