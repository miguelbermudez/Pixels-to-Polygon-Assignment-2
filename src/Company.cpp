//
//  Company.cpp
//  FinancialDataGeometry
//
//  Created by Miguel Bermudez on 2/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Company.h"
#include "gNoise.h"


//------------------------------------------------------------
Company::Company() 
{
    history.clear();
}

//------------------------------------------------------------
void Company::printStockHistory() 
{
    vector<stock_entry>::iterator it;
    int index = 0;
    
    if (!history.empty()) {
        for (it=history.begin(); it < history.end(); it++) {
            stock_entry se = *it;
            cout << "\tEntry: " << index << endl;
            cout << "\t\tDate: " << se.date << endl;
            cout << "\t\tOpen: " << se.open << endl;
            cout << "\t\t\tMax Open: " << se.maxOpen << endl;
            cout << "\t\t\tMin Open: " << se.minOpen << endl;
            cout << "\t\tHigh: " << se.high << endl;
            cout << "\t\tLow: " << se.low << endl;
            cout << "\t\tClose: " << se.close << endl;
            cout << "\t\t\tMax Close: " << se.maxClose << endl;
            cout << "\t\t\tMin Close: " << se.minClose << endl;
            cout << "\t\tVolume: " << se.volume << endl;
            cout << "\t\tAdjClose: " << se.adjClose << endl;
            cout << "\t\tHumanDate: " << se.humanDate << endl;
            
            cout << endl;
            index++;
        }        
    }
}

//------------------------------------------------------------
// http://www.dreamincode.net/forums/topic/66480-perlin-noise/
ofTexture Company::makeTexture(int texWidth, int texHeight) 
{
    int octaves = 3;
    //controls the roughness of the picture
    double roughness = 0.25;
    double zoom = 75.0;
    
    unsigned char *pixels;
    pixels = new unsigned char [texWidth * texHeight];
    
    int entryIndex = 0;
    //loop through pixels to populate texture data
    for (int y=0; y<texHeight; y++) {
        for (int x=0; x<texWidth; x++) {
            double getnoise = 0;
            for (int a=0; a<octaves; a++) {
                //This increases the frequency with every loop of the octave.
                double frequency = pow((double)2, a);   
                //This decreases the amplitude with every loop of the octave.
                double amplitude = pow(roughness, a);

                double xNoiseParam = (x * frequency) / zoom;
                double yNoiseParam = (y / zoom) * frequency;

                double stockEntryContrib;    
                
                if (entryIndex  <= history.size()-1 ) {
                    stockEntryContrib = getMappedValueFor(STOCK_CLOSE, entryIndex);
                    entryIndex++;
                    //cout << "entry Index: " << entryIndex << endl; //debugging
                }
                
                xNoiseParam += stockEntryContrib;
                yNoiseParam += stockEntryContrib;
                
                //getnoise += noise2(((double)x)*frequency/zoom,((double)y)/zoom*frequency)*amplitude;
                //getnoise +=  ofNoise(xNoiseParam, yNoiseParam) * amplitude;
                getnoise += gNoise::noise(xNoiseParam, yNoiseParam) * amplitude ;

            }
            //It gives a decimal value, you know, between the pixels. Like 4.2 or 5.1
            int color = (int)( (getnoise*128.0) + 128.0 ); //Convert to 0-256 values.
            //color -= 72;
            if (color > 255) color = 255;
            if (color < 0) color = 0;
            //cout << "color: " << color << "\tx: " << x << "\ty: " << y << endl;   //debugging
            
            int pixelIndex = x + y * texWidth;
            //pixels[pixelIndex] = (unsigned char)( (1.0/255.0) * color );
            pixels[pixelIndex] = (unsigned char) color;
        }
    }
    
    
    ofTexture heightMapTexture;
    
    heightMapTexture.allocate(texWidth, texHeight, GL_LUMINANCE);
    heightMapTexture.loadData(pixels, texWidth, texHeight, GL_LUMINANCE);

    return heightMapTexture;

}

//------------------------------------------------------------
double Company::getMappedValueFor( int field, int index ) 
{
    
    stock_entry entry = history[index];
    
    double value = 0;
    float mappedToUpperLimit = 1.0;
    float mappedToLowerLimit = -1.0;
    
    switch (field) {
        case STOCK_CLOSE:
            value = ofMap(entry.close, entry.minClose, entry.maxClose, mappedToLowerLimit, mappedToUpperLimit);
            break;
        case STOCK_OPEN:
            value = ofMap(entry.open, entry.minOpen, entry.maxOpen, mappedToLowerLimit, mappedToUpperLimit);
            break;
            
        default:
            break;
    }
    return value;   
    
}

//------------------------------------------------------------
string Company::toString() const 
{
    stringstream ss;
    ss << "Company -- " << name  << "\n" << "\t Stock Entries: " << (int)history.size() << endl;
    return ss.str();
}


//------------------------------------------------------------
ostream &operator<<(ostream &o, const Company &company) {
	o << company.toString();
	return o;
}