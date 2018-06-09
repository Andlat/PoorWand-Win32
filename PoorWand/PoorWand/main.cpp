//
//  main.cpp
//  PoorWand
//
//  Created by Andlat on 2018-06-08.
//  Copyright © 2018 poorwand. All rights reserved.
//


#include <iostream>
#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma cland diagnostic pop

#include "Window.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    unique_ptr<Window> window;
    try{
        window = make_unique<Window>(800, 500, "TEST");
    }catch(Window::exception &ex){
        cerr << ex.what() << endl;
        return -1;
    }
    
    while(!glfwWindowShouldClose(window->get())){
        glClearColor(0.8f, 0, 0.5f, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window->get());
        glfwPollEvents();
    }
    
    return 0;
}
