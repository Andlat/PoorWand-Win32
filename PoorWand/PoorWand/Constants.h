//
//  Constants.h
//  PoorWand
//
//  Created by Andlat on 2018-11-20.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef Constants_h
#define Constants_h

#include <GL/glew.h>
#include <string>

#define C_PI 3.14159265359
#define C_PI_2 1.57079632679
#define C_PI_4 0.7853981634
#define C_PI_6 0.5235987756
#define C_2_PI_3 2.09439510239

#define C_4_THIRD 1.33333333333

constexpr char FLOAT_SIZE(){ return sizeof(GL_FLOAT); };

namespace PATH{
const std::string
    RES = "/Users/andlat/PoorWand/PoorWand/PoorWand/res/",
    MODELS = RES+"models/",
    TEX = MODELS+"textures/",
    SHADERS = RES+"shaders/";
};

namespace GL_ATTR{
    const short STRIDE = 9;
}

#endif /* Constants_h */
