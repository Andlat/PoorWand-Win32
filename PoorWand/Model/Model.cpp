//
//  Model.cpp
//  PoorWand
//
//  Created by Andlat on 2018-11-09.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include "Model.hpp"

#include <memory>
#include <iostream>

#include "Constants.h"

using namespace std;

Model::Model()
{
}

Model::~Model(){
}

vector<float> Model::Construct(float mvp_index){
	mBuffer.clear();

    const unsigned size = (unsigned)mVertices.size();
    for(unsigned i=0; i < size; ++i){
        auto vertex = mVertices[i]->getBuff();
        auto normal = mNormals[i];
        auto uv = mUVs[i];

        float node[] = {vertex.x, vertex.y, vertex.z, normal->x, normal->y, normal->z, uv->s, uv->t, mvp_index};
        mBuffer.insert(mBuffer.end(), begin(node), end(node));
    }
    return mBuffer;
}
vector<float> Model::getBuffer(){ return mBuffer; }

void Model::addJoint(shared_ptr<Joint> joint, int parentIndex){
    if(parentIndex == -1){//If root joint, create it
        mJointsTree = joint;
    }else{//If children, find its parent and add it to the parent's children
        mJoints[parentIndex]->addChild(joint);
    }
    
    mJoints.push_back(joint);
}

void Model::AppendToGlobalBuffer(vector<float>& global_buffer){
    global_buffer.insert(global_buffer.end(), mBuffer.begin(), mBuffer.end());
}

shared_ptr<Joint> Model::getJointsTree(){ return mJointsTree; }
const vector<shared_ptr<Joint>>& Model::getJoints(){ return mJoints; }

void Model::addJointGroup(shared_ptr<JointGroup> group){
    mJointGroups.push_back(group);
}
const vector<shared_ptr<JointGroup>>& Model::getJointGroups(){ return mJointGroups; }

void Model::addVertex(shared_ptr<Vertex> vertex){ mVertices.push_back(vertex); }
const vector<shared_ptr<Vertex>>& Model::getVertices(){ return mVertices; }

void Model::addNormal(shared_ptr<glm::vec3> normal){
    mNormals.push_back(normal);
}
const std::vector<std::shared_ptr<glm::vec3>>& Model::getNormals(){ return mNormals; }

void Model::addUV(shared_ptr<glm::vec2> uv){
    mUVs.push_back(uv);
}
const std::vector<std::shared_ptr<glm::vec2>>& Model::getUVs(){ return mUVs; }

void Model::setTexturePath(string path){
    mTexturePath = path;
    mIsTexLoaded = false;
}
string Model::getTexturePath(){ return PATH::TEX + mTexturePath; }
GLuint Model::getTexture(){ return mTexture; }
bool Model::isTextLoaded(){ return mIsTexLoaded; }
bool Model::LoadTexture(bool genMipmaps, GLfloat mag_filter, GLfloat min_filter){
    if(!mIsTexLoaded && !mTexturePath.empty()){
        int width, height;
        unsigned char* image = SOIL_load_image(getTexturePath().c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        
        glGenTextures(1, &mTexture);
        glBindTexture(GL_TEXTURE_2D, mTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        
        SOIL_free_image_data(image);
        
        if(genMipmaps) glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
        
        mIsTexLoaded = true;
        return true;
    }
    return false;
}

Model* Model::StaticTranslate(glm::vec3 translation){
    for(unsigned i=0; i < mBuffer.size(); i+=9){
        mBuffer[i] += translation.x;
        mBuffer[i+1] += translation.y;
        mBuffer[i+2] += translation.z;
    }
    return this;
}

Model* Model::Translate(glm::vec3 translation){
    mTranslationMat = glm::translate(mTranslationMat, translation);
    
    //Keep track of the total translation of the model
    mTotalTranslation += translation;
    
    return this;
}
Model* Model::Scale(float scale){
    mScaleMat = glm::scale(mScaleMat, glm::vec3(scale, scale, scale));
    
    return this;
}

glm::mat4 Model::getModelMat(){ return mTranslationMat * mScaleMat; }
glm::vec4 Model::getTransformVec(){ return this->getModelMat() * glm::vec4(); }
glm::vec3 Model::getTranslation(){ return mTotalTranslation; }
