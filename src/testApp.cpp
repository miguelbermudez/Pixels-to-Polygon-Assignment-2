#include "testApp.h"
#include "ofMath.h"


//--------------------------------------------------------------
void testApp::setup(){
    //ofBackground(64);
    
    //create a company
    Company cAmazon;
    cAmazon.name = "amazon";
    
    readAndParseCSV(cAmazon);
    cAmazon.texture = cAmazon.makeTexture(512, 512); 
    
    cout << cAmazon << endl;  //debugging
    test = cAmazon.texture;
    cAmazon.printStockHistory();
    

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    test.draw(1,1,512,512);
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
long testApp::convertDate(string dateString)
{
    tm timeinfo;
    tm *myTimeInfo;
    time_t rawtime;

    //this is all ugly, gah
    
    
    const char * cString = dateString.c_str();
    sscanf(cString, "%4d-%2d-%2d", &timeinfo.tm_year,&timeinfo.tm_mon,&timeinfo.tm_mday);
    timeinfo.tm_year = timeinfo.tm_year - 1900;
    timeinfo.tm_mon = timeinfo.tm_mon - 1;
    
    //get current time and then modify it according to our parsed date
    time(&rawtime);
    myTimeInfo = localtime(&rawtime);
    
    //modify our time info with what we got from the parsed date
    myTimeInfo->tm_year = timeinfo.tm_year;
    myTimeInfo->tm_mon = timeinfo.tm_mon;
    myTimeInfo->tm_mday = timeinfo.tm_mday;

    //don't really need to do this but we were getting random numbers for hours, min, sec. 
    myTimeInfo->tm_hour = 0;
    myTimeInfo->tm_min = 0;
    myTimeInfo->tm_sec = 0;
    
    //convert our modified time info back into rawtime (so confusing...)
    rawtime = mktime(myTimeInfo);

    //printf("year: %d; month: %d; day: %d;\n", timeinfo.tm_year, timeinfo.tm_mon, timeinfo.tm_mday);   //debugging 
    //printf("hour: %d; minute: %d; second: %d\n",  timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);  //debugging
    //printf("week day: %d; year day: %d\n", timeinfo.tm_wday, timeinfo.tm_yday);                         //debugging
    
    if (rawtime == -1) {
        cout << "Time Struct not valid!" << endl;
    }
    
    //cout <<"Converted Time: "<< (long)rawtime << endl; //debugging
    
    return (long)rawtime;
    
}

//--------------------------------------------------------------
void testApp::readAndParseCSV(Company &c) 
{
    string line;
    int pos;
    int index = 0; 
    int lineIndex = 0;
    float entryMaxOpen = 0.0;
    float entryMinOpen = INT_MAX;
    float entryMaxClose = 0.0;
    float entryMinClose = INT_MAX;

    ifstream in("data/csv/amazon.csv");
    if (!in.is_open())
    {
        printf("can't open the file");
        return;
    }
    
    while ( getline( in, line ) ) {
        index = 0;
        // init stock entry
        stock_entry entry = STOCK_ENTRY_DEFAULT;
        // skip the first line
        if ( lineIndex > 0) {
            while ( (pos = line.find(',')) >= 0 || index == 6 ) {
                string field = line.substr(0, pos);
                line = line.substr(pos+1);
                //array->push_back(field);
                switch (index) {
                    case STOCK_DATE:
                        //remove all the quotation marks
                        //fyi: string parsing and scrubbing is FUGLY in C
                        //field.erase( remove(field.begin(), field.end(), '\"'), field.end() );
                        //convert string date into long date (e.g time in seconds since the epoch)
                        entry.date = convertDate(field);
                        //lets remember human date for error checking, just in case
                        entry.humanDate = field;
                        
                        break;
                    case STOCK_OPEN:
                        entry.open = atof(field.c_str());
                        //find max and min open prices for entry
                        if (entry.open >= entryMaxOpen) entryMaxOpen = entry.open;
                        if (entry.open <= entryMinOpen) entryMinOpen = entry.open;
                        entry.maxOpen = entryMaxOpen;
                        entry.minOpen = entryMinOpen;
                        
                        break;
                    case STOCK_HIGH:
                        entry.high = atof(field.c_str());
                        break;
                    case STOCK_LOW:
                        entry.low = atof(field.c_str());
                        break;
                    case STOCK_CLOSE:
                        entry.close = atof(field.c_str());
                        //find max and min open prices for entry
                        if (entry.close >= entryMaxClose) entryMaxClose = entry.close;
                        if (entry.close <= entryMinClose) entryMinClose = entry.close;
                        entry.maxClose = entryMaxClose;
                        entry.minClose = entryMinClose;

                        break;
                    case STOCK_VOLUME:
                        entry.volume = atoi(field.c_str());
                        break;
                    case STOCK_ADJCLOSE:
                        entry.adjClose = atof(field.c_str());
                        break;
                    default:
                        break;
                }
                //cout << index << ": " << field << endl;    //debugging
                
                index++;
                //cout << "\tline: " << line << ", index: " << index << endl;   //debugging
            }
        }
        if(entry.date != 0) {
            c.history.push_back(entry);
        }
        cout << endl;
        lineIndex++;
    }
    
    return;
}