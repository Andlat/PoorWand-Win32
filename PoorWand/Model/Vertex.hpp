//
//  Vertex.hpp
//  PoorWand
//
//  Created by Andlat on 2018-11-16.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <memory>
#include <string>

#include "JointGroup.hpp"

class Vertex{
public:
    Vertex();
    Vertex(float x, float y, float z, std::shared_ptr<JointGroup> group);
    Vertex(glm::vec3 buff, std::shared_ptr<JointGroup> group);
    
    glm::vec3 getBuff();
    void setBuff(glm::vec3 buff);
    
    /*
    float* getBuff();
    void setBuff(float buff[3]);
    
    float* getNormal();
    void setNormal(float normal[3]);
    void setNormal(float i, float j, float k);
    
    float* getUV();
    void setUV(float uv[2]);
    void setUV(float s, float t);
    */
    std::shared_ptr<JointGroup> getGroup();
    void setGroup(std::shared_ptr<JointGroup> group);
    
    //std::string buff_to_string();
private:
    //float mBuff[3] = {0, 0, 0};/*, mNormal[3] = {0, 0, 0}, mUV[2] = {0, 0};*/
    
    glm::vec3 mBuff = glm::vec3();
    
    std::shared_ptr<JointGroup> mGroup = std::make_shared<JointGroup>();
};

#endif /* Vertex_hpp */
