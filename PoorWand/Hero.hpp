//
//  Hero.hpp
//  PoorWand
//
//  Created by Andlat on 2019-01-03.
//  Copyright © 2019 poorwand. All rights reserved.
//

#ifndef Hero_hpp
#define Hero_hpp

#include "ControlledModel.hpp"

#include <GL/glew.h>


#include <GLFW/glfw3.h>


#include <glm/vec3.hpp>

class Hero : public ControlledModel {
public:
    Hero();
    ~Hero() override;
    
    void ActivateFrameControls(long frameTimeDelta) override;
    
protected:
    void InitControls() override;
    
private:
    long mFrameTimeDelta = 0;
    long getTimeDelta();
    
    void MoveIfState(int state_name, glm::vec3 direction);
};

#endif /* Hero_hpp */
