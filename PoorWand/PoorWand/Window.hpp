//
//  Window.hpp
//  PoorWand
//
//  Created by Andlat on 2018-06-09.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <exception>

#include <GL/glew.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma cland diagnostic pop


class Window{
public:
    Window(const short w, const short h, const char* title);
    ~Window();
    
    GLFWwindow* get();
    
    int getWidth(), getHeight();
    
    /** Window Exceptions **/
    class exception : std::exception {
    public:
        exception() : mWhat("Window exception") {}
        exception(const char* msg) : mWhat(msg) {}
        
        virtual const char* what() const throw() { return mWhat; }
    private:
        const char* mWhat;
    };
private:
    void init(const short w, const short h);
    
    GLFWwindow* mWindow = nullptr;
    
    int mPxWidth, mPxHeight;
    const char* mTitle;
};

#endif /* Window_hpp */
