//
//  Vertex.cpp
//  PoorWand
//
//  Created by Andlat on 2018-11-16.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include "Vertex.hpp"

using namespace std;

Vertex::Vertex()
{
}
Vertex::Vertex(float x, float y, float z, shared_ptr<JointGroup> group)
: mGroup(group)
{
    mBuff = glm::vec3(x, y, z);
}
Vertex::Vertex(glm::vec3 buff, std::shared_ptr<JointGroup> group)
: Vertex(buff.x, buff.y, buff.z, group)
{
}

glm::vec3 Vertex::getBuff(){ return mBuff; }
void Vertex::setBuff(glm::vec3 buff){
    mBuff = buff;
    /*mBuff[0] = buff[0];
    mBuff[1] = buff[1];
    mBuff[2] = buff[2];*/
}

/*
float* Vertex::getNormal(){ return mNormal; };
void Vertex::setNormal(float normal[3]){
    this->setNormal(normal[0], normal[1], normal[2]);
};
void Vertex::setNormal(float i, float j, float k){
    mNormal[0] = i;
    mNormal[1] = j;
    mNormal[2] = k;
}

float* Vertex::getUV(){ return mUV; };
void Vertex::setUV(float uv[2]){
    this->setUV(uv[0], uv[1]);
};
void Vertex::setUV(float s, float t){
    mUV[0] = t;
    mUV[1] = s;
}
*/
shared_ptr<JointGroup> Vertex::getGroup(){ return mGroup; }
void Vertex::setGroup(shared_ptr<JointGroup> group){ mGroup = group; }

/*
string Vertex::buff_to_string(){
    return to_string(mBuff[0]) + ' ' + to_string(mBuff[1]) + ' ' + to_string(mBuff[2]) + ' ' + to_string(mNormal[0]) + ' ' + to_string(mNormal[1]) + ' ' +   to_string(mNormal[2]) + ' ' + to_string(mUV[0]) + ' ' + to_string(mUV[1]);
}*/
