//
//  misc.cpp
//  PoorWand
//
//  Created by Andlat on 2018-11-09.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include "misc.hpp"

using namespace std;

vector<string> misc::explode(const string s, const char del){
    auto exploded = vector<string>();
    string part;
    
    for(unsigned i = 0; i < s.length(); ++i){
        char c = s[i];
        
        if(c != del){
            part += c;
        }else{
            if(!part.empty()){
                exploded.push_back(part);
                part.clear();
            }
        }
    }
    
    exploded.push_back(part);//Add the last part
    return exploded;
}
