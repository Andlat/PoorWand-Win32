//
//  Shader.hpp
//  PoorWand
//
//  Created by Andlat on 2018-11-21.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <GL/glew.h>

#include <string>

class Shader{
public:
    class ShaderException : std::exception{
        friend class Shader;
        friend class ShaderProgram;
    public:
        const char* what() const noexcept override;
    private:
        ShaderException(const std::string msg);
        const std::string mMsg;
    };
    
    Shader(GLuint type);/** throws ShaderException **/
    
    Shader* Load(const std::string& path);/** throws ShaderException **/
    Shader* Compile();/** throws ShaderException **/
    void Delete();
    
    const GLuint get();
private:
    GLuint mShader;
    std::string mSource;
};

#endif /* Shader_hpp */
