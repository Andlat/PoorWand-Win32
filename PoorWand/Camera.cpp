//
//  Camera.cpp
//  PoorWand
//
//  Created by Andlat on 2018-11-24.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include "Camera.hpp"

#include <iostream>


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/vec3.hpp>


using namespace std;
Camera::Camera()
{
    mProjection = glm::perspective(mLens, mAspectRatio, mNear, mFar);
}
Camera::Camera(float near, float far, float aspectRatio, float lens)
: mNear(near), mFar(far), mAspectRatio(aspectRatio), mLens(lens)
{
    mProjection = glm::perspective(lens, aspectRatio, near, far);
}

void Camera::setTarget(glm::vec3 target){ mTarget = target; mRecalcProjection = true; }
void Camera::setPosition(glm::vec3 pos){
    mPosition = pos;
    mRecalcProjection = true;
    
    //If following a model, but want to change the camera position
    if(mMoveWithModel && !mPosSetByFollow){
        mOrgPos = pos;
    }else if(mPosSetByFollow){
        mPosSetByFollow = false;
    }
}

void Camera::setClip(float near, float far){
    mNear = near;
    mFar = far;
    mRecalcProjection = true;
}
void Camera::setLens(float lens_rad){ mLens = lens_rad; }

void Camera::Follow(std::shared_ptr<MovingModel> model){
    
    mModel2Follow = model;
    
    //Stop following
    if(model == nullptr){
        mMoveWithModel = false;
        mPosSetByFollow = false;
    }
}
void Camera::Follow(std::shared_ptr<MovingModel> model, bool move){
    mMoveWithModel = move;
    mOrgPos = mPosition;
    
    Follow(model);
}

void Camera::Follow(){
    if(mModel2Follow != nullptr){
        auto target = mModel2Follow->getTranslation();
        this->setTarget(target);
        
        if(mMoveWithModel){
            auto pos = glm::vec3(mOrgPos.x + target.x, mOrgPos.y + target.y, mOrgPos.z + target.z);
            
            mPosSetByFollow = true;
            this->setPosition(pos);
        }
    }
}

glm::mat4 Camera::Construct(glm::mat4 modelMat){
    this->Follow();
    
    if(mRecalcProjection){
        mProjection = glm::perspective(mLens, mAspectRatio, mNear, mFar);
        mRecalcProjection = false;
    }
    
    glm::mat4 view = glm::lookAt(mPosition, mTarget, mHead);
    
	return mProjection * view * modelMat;
}
