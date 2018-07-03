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
#include "Game.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    shared_ptr<Window> window;
    unique_ptr<Game> game;
    
    try{
        window = make_shared<Window>(800, 500, "PoorWand");
    }catch(Window::exception &ex){
        cerr << ex.what() << endl;
        return -1;
    }
    
    game = make_unique<Game>(window);
    game->Loop();
    cout << "Game started" << endl;
    
    return 0;
}
