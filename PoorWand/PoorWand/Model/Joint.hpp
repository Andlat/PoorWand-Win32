//
//  Joint.hpp
//  PoorWand
//
//  Created by Andlat on 2018-11-09.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef Joint_hpp
#define Joint_hpp

#include <vector>
#include <memory>


#include <glm/glm.hpp>


class Joint{
public:
    Joint();
    Joint(glm::mat4 transform);
    Joint(glm::mat4 transform, std::vector<std::shared_ptr<Joint>> children);
    
    const std::vector<std::shared_ptr<Joint>>& getChildren();
    void addChild(std::shared_ptr<Joint> joint);
    
    glm::mat4 getTransform();
    void setTransform(glm::mat4 transform);
private:
    glm::mat4 mTransform = glm::mat4();
    
    std::vector<std::shared_ptr<Joint>> mChildren = std::vector<std::shared_ptr<Joint>>();
};

#endif /* Joint_hpp */
