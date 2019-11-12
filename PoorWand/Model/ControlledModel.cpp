//
//  ControlledModel.cpp
//  PoorWand
//
//  Created by Andlat on 2019-01-03.
//  Copyright © 2019 poorwand. All rights reserved.
//

#include "ControlledModel.hpp"
#include "KeyboardS.hpp"

ControlledModel::ControlledModel()
: MovingModel::MovingModel()
{
}

ControlledModel::~ControlledModel(){
}

void ControlledModel::InitOnPressState(int key_state_name){
    KeyboardS& keyboard = KeyboardS::Instance();
    
    //On press
    keyboard.addKey(key_state_name, GLFW_PRESS, [this, key_state_name](GLFWwindow* w, int mods){ this->assignState(key_state_name, 1); });
    
    //On release
    keyboard.addKey(key_state_name, GLFW_RELEASE, [this, key_state_name](GLFWwindow* w, int mods){ this->assignState(key_state_name, 0); });
}

void ControlledModel::addState(int name, bool state){
    mStates.insert({name, state});
}
void ControlledModel::removeState(int name){
    mStates.erase(name);
}
void ControlledModel::assignState(int name, bool state){
    mStates[name] = state;
}
bool ControlledModel::readState(int name){
    return mStates[name];
}
