//
//  Joint.cpp
//  PoorWand
//
//  Created by Andlat on 2018-11-09.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include "Joint.hpp"

#include <iostream>

using namespace std;

Joint::Joint()
{}
Joint::Joint(glm::mat4 transform)
: mTransform(transform)
{
}
Joint::Joint(glm::mat4 transform, vector<std::shared_ptr<Joint>> children)
: mTransform(transform), mChildren(children)
{
}

const vector<std::shared_ptr<Joint>>& Joint::getChildren(){
    return mChildren;
}
void Joint::addChild(std::shared_ptr<Joint> joint){
    mChildren.push_back(joint);
}

glm::mat4 Joint::getTransform(){
    return mTransform;
}
void Joint::setTransform(glm::mat4 transform){
    mTransform = transform;
}
