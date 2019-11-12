//
//  MovingModel.cpp
//  PoorWand
//
//  Created by Andlat on 2018-11-25.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include "MovingModel.hpp"

#include <glm/geometric.hpp>
#include <iostream>

using namespace std;

MovingModel::MovingModel()
: Model::Model()
{
}
MovingModel::MovingModel(float speed)
: Model::Model(), mSpeed(speed)
{    
}

MovingModel::~MovingModel()
{
}

void MovingModel::Move(glm::vec3 dir, long ms_time_delta){
    float time_delta = (float)ms_time_delta/1000000.f;
    dir = glm::normalize(dir);
    
    glm::vec3 translation = dir * (mSpeed * time_delta);
    this->Translate(translation);
}


void MovingModel::setSpeed(float speed){ mSpeed = speed; }
float MovingModel::getSpeed(){ return mSpeed; }
