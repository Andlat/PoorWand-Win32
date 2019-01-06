//
//  ControlledModel.hpp
//  PoorWand
//
//  Created by Andlat on 2019-01-03.
//  Copyright © 2019 poorwand. All rights reserved.
//

#ifndef ControlledModel_hpp
#define ControlledModel_hpp

#include "MovingModel.hpp"

#include <GL/glew.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include <unordered_map>

class ControlledModel : public MovingModel{
public:
    ControlledModel();
    virtual ~ControlledModel() override;

    virtual void ActivateFrameControls(long frameTimeDelta) =0;
    
    void addState(int name, bool state);
    void removeState(int name);
    void assignState(int name, bool state);
    bool readState(int name);
protected:
    virtual void InitControls() =0;
    
    void InitOnPressState(int key_state_name);
private:
    std::unordered_map<int, bool> mStates = {
        {GLFW_KEY_UP, 0},
        {GLFW_KEY_DOWN, 0},
        {GLFW_KEY_LEFT, 0},
        {GLFW_KEY_RIGHT, 0}
    };
};

#endif /* ControlledModel_hpp */
