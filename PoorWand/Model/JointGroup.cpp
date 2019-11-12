//
//  JointGroup.cpp
//  PoorWand
//
//  Created by Andlat on 2018-11-12.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include "JointGroup.hpp"

using namespace std;

JointGroup::JointGroup()
{
}

void JointGroup::addJoint(shared_ptr<Joint> joint, float weight){
    mJoints.push_back(joint);
    mWeights.push_back(weight);
}
const vector<shared_ptr<Joint>>& JointGroup::getJoints(){ return mJoints; }
shared_ptr<Joint> JointGroup::getJoint(unsigned index){ return mJoints[index]; }

const vector<float>& JointGroup::getWeights(){ return mWeights; }
float JointGroup::getWeight(unsigned index){ return mWeights[index]; }
