//
//  Constants.h
//  PoorWand
//
//  Created by Andlat on 2018-11-20.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef Constants_h
#define Constants_h

#define OSX 0x1
#define WIN32 0x2

#define TARGET WIN32

#define C_PI 3.14159265359
#define C_PI_2 1.57079632679
#define C_PI_4 0.7853981634
#define C_PI_6 0.5235987756
#define C_2_PI_3 2.09439510239

#define C_4_THIRD 1.33333333333

#include <GL/glew.h>
#include <string>

constexpr char FLOAT_SIZE(){ return sizeof(GL_FLOAT); };

namespace PATH{
	
#if TARGET == OSX
	const std::string RES = "/Users/andlat/PoorWand/PoorWand/PoorWand/res/";
#elif TARGET == WIN32
	const std::string RES = "C:/Users/BigPatate/opengl_test/opengl_test/res/";
#endif
	const std::string
		MODELS = RES+"models/",
		TEX = MODELS+"textures/",
		SHADERS = RES+"shaders/";
};

namespace GL_ATTR{
    const short STRIDE = 9;
}

#endif /* Constants_h */
