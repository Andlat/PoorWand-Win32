//
//  Game.cpp
//  PoorWand
//
//  Created by Andlat on 2018-06-09.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include "Game.hpp"

#include <thread>

using namespace std;

Game::Game(shared_ptr<Window> window)
: mWindow(window)
{
}

Game::~Game(){
}

void Game::Loop(){
    while(!glfwWindowShouldClose(mWindow->get())){
        glClearColor(0.8f, 0, 0.5f, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        
        glfwSwapBuffers(mWindow->get());
        glfwPollEvents();
    }
}
