//
//  Keyboard.cpp
//  PoorWand
//
//  Created by Andlat on 2018-12-12.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include "KeyboardS.hpp"
#include <iostream>
using namespace std;

KeyboardS::KeyboardS(){
    mCallbacks = vector<shared_ptr<Callback>>();
    mEvents = std::vector<std::function<void(void)>>();
}

KeyboardS& KeyboardS::Instance(){
    static KeyboardS instance;
    return instance;
}

KeyboardS& KeyboardS::Instance(GLFWwindow* window){
    Instance().bindWindow(window);
    return Instance();
}


void KeyboardS::bindWindow(GLFWwindow* window){
    glfwSetKeyCallback(window, MainCallback);
}

void KeyboardS::addKey(int key, int action, std::function<void(GLFWwindow*, int)> callback){
    mCallbacks.push_back(make_shared<Callback>(key, action, callback));
}

void KeyboardS::addEvent(std::function<void(void)> fn){
    mEvents.push_back(fn);
}

void MainCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    for(auto callback : KeyboardS::Instance().mCallbacks){
        if(key == callback->key && action == callback->action){
            callback->callback(window, mods);
        }
    }
    
    //Execute non binding callbacks
    for(auto event : KeyboardS::Instance().mEvents){
        event();
    }
}
