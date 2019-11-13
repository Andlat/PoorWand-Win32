//
//  Camera.hpp
//  PoorWand
//
//  Created by Andlat on 2018-11-24.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <memory>


#include <glm/matrix.hpp>
#include <glm/vec3.hpp>


#include "Constants.h"
#include "MovingModel.hpp"

using namespace std;

class Camera{
public:
    Camera();
    Camera(float near, float far, float aspectRatio, float lens);
    
    void setTarget(glm::vec3 target);
    void setPosition(glm::vec3 pos);
    
    void setClip(float near, float far);
    void setLens(float lens_rad);
    
    /**
      Follow a model
     
      @arg model Model to follow. Can also pass nullptr to stop following
      @arg move Move the camera with model
      **/
    void Follow(std::shared_ptr<MovingModel> model);
    void Follow(std::shared_ptr<MovingModel> model, bool move);
    
    glm::mat4 Construct(glm::mat4 modelMat);
private:
    /**
      Making the assumption that each model starts at a position of (0,0,0)
     **/
    void Follow();

    const glm::vec3 mHead = glm::vec3(0, 1, 0);
    glm::vec3 mTarget = glm::vec3(), mPosition = glm::vec3(0, 0, 1);
    
    float mNear = 0.1f, mFar = 100.f, mAspectRatio = C_4_THIRD, mLens = C_PI_4;
    glm::mat4 mProjection;
    bool mRecalcProjection = false;//Keeps track if the perspective has to be recalculated. Only when a parameter of the perspective is changed.
    
    std::shared_ptr<MovingModel> mModel2Follow = nullptr;
    bool mMoveWithModel = false, mPosSetByFollow = false;
    glm::vec3 mOrgPos = glm::vec3();
};

#endif /* Camera_hpp */
