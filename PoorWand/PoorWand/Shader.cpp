//
//  Shader.cpp
//  PoorWand
//
//  Created by Andlat on 2018-11-21.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include "Shader.hpp"

#include <string>
#include <fstream>

using namespace std;

Shader::ShaderException::ShaderException(const string msg)
: mMsg(msg)
{
}
const char* Shader::ShaderException::what() const noexcept{
    return mMsg.c_str();
}

Shader::Shader(GLuint type)/** throws ShaderException **/
{
    //Validate shader type and throw exception if bad
    if(type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER){
        throw ShaderException(string("Bad shader type. Accepted are GL_VERTEX_SHADER: ") + to_string(GL_VERTEX_SHADER) + string(" or GL_FRAGMENT_SHADER: ") + to_string(GL_FRAGMENT_SHADER) + string(". Provided: ") + to_string(type));
    }
    //Create the appropriate shader
    mShader = glCreateShader(type);
}
 
Shader* Shader::Load(const string& path)/** throws ShaderException **/
{
    ifstream source;
    source.exceptions(ifstream::failbit);
    
    try{
        source.open(path);
        string line;
        
        mSource.clear();
		try {
			while (getline(source, line)) {
				mSource += line + '\n';
			}
		}
		catch (ifstream::failure e) {}//Ignore failbit from getline, because it will set it when it reaches the eof
        
        source.close();
    }catch(ifstream::failure e){
        throw ShaderException(string("Failed to load shader; ") + e.what());
    }
    return this;
}
#include <iostream>
Shader* Shader::Compile()/** throws ShaderException **/
{
    const char* source = mSource.c_str();
    glShaderSource(mShader, 1, &source, nullptr);
    
    glCompileShader(mShader);
    
    //Check compilation success
    GLint success;
    glGetShaderiv(mShader, GL_COMPILE_STATUS, &success);
    if(!success){
        char info[1024];
        glGetShaderInfoLog(mShader, 1024, nullptr, info);
        throw ShaderException(string("Failed to compile shader: ") + string(info));
    }
    
    return this;
}
void Shader::Delete(){
    glDeleteShader(mShader);
}

const GLuint Shader::get(){ return mShader; }
