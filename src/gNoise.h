//
//  gNoise.h
//  FinancialDataGeometry
//
//  Created by Miguel Bermudez on 2/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ofMath.h"

class gNoise 
{
    
public:
    gNoise();
    static double noise(double x, double y);
    
private:
    static inline double findnoise2D(double x, double y);
    static inline double interpolate(double a, double b, double x);

    
};