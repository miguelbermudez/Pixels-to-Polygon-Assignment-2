//
//  Company.cpp
//  FinancialDataGeometry
//
//  Created by Miguel Bermudez on 2/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Company.h"


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
            cout << "\t\tHigh: " << se.high << endl;
            cout << "\t\tLow: " << se.low << endl;
            cout << "\t\tClose: " << se.close << endl;
            cout << "\t\tVolume: " << se.volume << endl;
            cout << "\t\tAdjClose: " << se.adjClose << endl;
            cout << "\t\tHumanDate: " << se.humanDate << endl;
            cout << endl;
            index++;
        }        
    }
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