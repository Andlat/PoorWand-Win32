//
//  ShaderProgram.hpp
//  PoorWand
//
//  Created by Andlat on 2018-11-21.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <GL/glew.h>

#include "Shader.hpp"

class ShaderProgram{
public:
    ShaderProgram();
    
    ShaderProgram* Attach(Shader* const shader);
    ShaderProgram* Detach(Shader* const shader);
    ShaderProgram* Link();
    
    void Delete();
    
    const GLuint get();
    
private:
    GLuint mProgram;
    
};

#endif /* ShaderProgram_hpp */
