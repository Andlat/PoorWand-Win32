//
//  misc.hpp
//  PoorWand
//
//  Created by Andlat on 2018-11-09.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef misc_hpp
#define misc_hpp

#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>

namespace misc{
    std::vector<std::string> explode(std::string s, const char del);
    
    template<typename T> const std::string to_string(const std::vector<T> vec){
        using namespace std;
        ostringstream oss;
        
        if(!vec.empty()){
            copy(vec.begin(), vec.end()-1, ostream_iterator<T>(oss, ","));
            oss << vec.back();
        }
        return oss.str();
    }
}

#endif /* misc_hpp */
