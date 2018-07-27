//
//  Window.cpp
//  PoorWand
//
//  Created by Andlat on 2018-06-09.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include "Window.hpp"
#include <iostream>
Window::Window(const short w, const short h, const char* title) /* throws exception */
: mTitle(title)
{
    init(w, h);
}

Window::~Window(){
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

GLFWwindow* Window::get(){ return mWindow; }

void Window::init(const short w, const short h) /* throws exception */ {
    if(!glfwInit())
        throw Window::exception("Failed to init glfw.");
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//OpenGL 3.3
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//For OS X / MAC OS
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//Use OpenGL core
    
    mWindow = glfwCreateWindow(w, h, mTitle, nullptr, nullptr);
    if(!mWindow)
        throw Window::exception("Failed to create window.");
    
    glfwGetFramebufferSize(mWindow, &mPxWidth, &mPxHeight);
    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(1);
    
    //Init glew
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw Window::exception("Failed to init GLEW.");
    
    glViewport(0, 0, mPxWidth, mPxHeight);
}
