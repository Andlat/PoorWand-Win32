//
//  ModelLoader.hpp
//  PoorWand
//
//  Created by Andlat on 2018-11-09.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef ModelLoader_hpp
#define ModelLoader_hpp

#include <string>
#include <fstream>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "Model.hpp"
#include "Vertex.hpp"

class ModelLoader{
public:
    ModelLoader();
    
    template <typename T>
    std::shared_ptr<T> Parse(std::string file);
    
private:
    void ParseLine(std::shared_ptr<Model> model, const std::string &line);
    
    unsigned mLineCount = 0, mGroupLine=0, mVertLine=0, mNormalLine=0, mUVLine=0;
    
    std::vector<std::shared_ptr<Vertex>> mVertices = std::vector<std::shared_ptr<Vertex>>();
    std::vector<glm::vec3> mNormals = std::vector<glm::vec3>();
    std::vector<glm::vec2> mUVs = std::vector<glm::vec2>();
};

#include "ModelLoader.inl"
#endif /* ModelLoader_hpp */
