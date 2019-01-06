//
//  JointGroup.hpp
//  PoorWand
//
//  Created by Andlat on 2018-11-12.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef JointGroup_hpp
#define JointGroup_hpp

#include <vector>
#include <memory>

#include "Joint.hpp"

class JointGroup{
public:
    JointGroup();
    
    void addJoint(std::shared_ptr<Joint> joint, float weight);
    
    const std::vector<std::shared_ptr<Joint>>& getJoints();
    std::shared_ptr<Joint> getJoint(unsigned index);
    
    const std::vector<float>& getWeights();
    float getWeight(unsigned index);
private:
    std::vector<std::shared_ptr<Joint>> mJoints = std::vector<std::shared_ptr<Joint>>();
    std::vector<float> mWeights = std::vector<float>();
};

#endif /* JointGroup_hpp */
