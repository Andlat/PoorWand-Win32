//
//  Hero.cpp
//  PoorWand
//
//  Created by Andlat on 2019-01-03.
//  Copyright © 2019 poorwand. All rights reserved.
//

#include "Hero.hpp"
#include "KeyboardS.hpp"

#include <iostream>

using namespace glm;

Hero::Hero()
: ControlledModel::ControlledModel()
{
    this->setSpeed(2.f);
    
    this->InitControls();
}

Hero::~Hero(){
}

long Hero::getTimeDelta(){ return mFrameTimeDelta; }

void Hero::InitControls(){    
    InitOnPressState(GLFW_KEY_UP);
    InitOnPressState(GLFW_KEY_DOWN);
    InitOnPressState(GLFW_KEY_LEFT);
    InitOnPressState(GLFW_KEY_RIGHT);
}

void Hero::ActivateFrameControls(long frameTimeDelta){
    mFrameTimeDelta = frameTimeDelta;
    
    MoveIfState(GLFW_KEY_UP, vec3(0, 1, 0));
    MoveIfState(GLFW_KEY_DOWN, vec3(0, -1, 0));
    MoveIfState(GLFW_KEY_LEFT, vec3(-1, 0, 0));
    MoveIfState(GLFW_KEY_RIGHT, vec3(1, 0, 0));
}

void Hero::MoveIfState(int state_name, vec3 direction){
    if(this->readState(state_name))
        this->Move(direction, this->getTimeDelta());
}
