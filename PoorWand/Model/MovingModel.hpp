//
//  MovingModel.hpp
//  PoorWand
//
//  Created by Andlat on 2018-11-25.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef MovingModel_hpp
#define MovingModel_hpp
#include "Model.hpp"

class MovingModel : public Model {
public:
    MovingModel();
    MovingModel(float speed);
    virtual ~MovingModel() override;
    
    void Move(glm::vec3 dir, long ms_time_delta);
    
    void setSpeed(float speed);
    float getSpeed();
private:
    float mSpeed = 1.f;
};

#endif /* MovingModel_hpp */
