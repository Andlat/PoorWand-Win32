//
//  ShaderProgram.cpp
//  PoorWand
//
//  Created by Andlat on 2018-11-21.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include "ShaderProgram.hpp"

#include <string>

ShaderProgram::ShaderProgram(){
    mProgram = glCreateProgram();
}

ShaderProgram* ShaderProgram::Attach(Shader* const shader){
    glAttachShader(mProgram, shader->get());

    return this;
}
ShaderProgram* ShaderProgram::Detach(Shader* const shader){
    glDetachShader(mProgram, shader->get());
    
    return this;
}

ShaderProgram* ShaderProgram::Link(){
    glLinkProgram(mProgram);
    
    GLint success;
    glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
    if(!success){
        char info[1024];
        glGetProgramInfoLog(mProgram, 1024, nullptr, info);
        throw Shader::ShaderException(std::string("Failed to link program: ") + std::string(info));
        
    }
    return this;
}

void ShaderProgram::Delete(){
    glDeleteProgram(mProgram);
}

const GLuint ShaderProgram::get(){ return mProgram; }
