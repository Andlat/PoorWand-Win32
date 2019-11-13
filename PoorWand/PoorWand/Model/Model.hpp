//
//  Model.hpp
//  PoorWand
//
//  Created by Andlat on 2018-11-09.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <GL/glew.h>


#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>


#include <SOIL2/SOIL2.h>

#include <vector>
#include <memory>
#include <string>

#include "Joint.hpp"
#include "JointGroup.hpp"
#include "Vertex.hpp"

class Model{
    //friend class ModelLoader;
public:
    Model();
    virtual ~Model() =0;
    
    /** Construct the model's OpenGL buffer **/
    std::vector<float> Construct(float mvp_index);
    std::vector<float> getBuffer();
    
    void AppendToGlobalBuffer(std::vector<float>& global_buffer);
    
    void addJoint(std::shared_ptr<Joint> joint, int parentIndex);
    const std::vector<std::shared_ptr<Joint>>& getJoints();
    std::shared_ptr<Joint> getJointsTree();
    
    void addJointGroup(std::shared_ptr<JointGroup> group);
    const std::vector<std::shared_ptr<JointGroup>>& getJointGroups();
    
    void addVertex(std::shared_ptr<Vertex> vertex);
    const std::vector<std::shared_ptr<Vertex>>& getVertices();
    
    void addNormal(std::shared_ptr<glm::vec3> normal);
    const std::vector<std::shared_ptr<glm::vec3>>& getNormals();
    
    void addUV(std::shared_ptr<glm::vec2> uv);
    const std::vector<std::shared_ptr<glm::vec2>>& getUVs();
    
    void setTexturePath(std::string path);
    std::string getTexturePath();
    GLuint getTexture();
    bool isTextLoaded();
    
    typedef GLfloat GLfilter;
    bool LoadTexture(bool genMipmaps, GLfilter mag_filter, GLfilter min_filter);
    
    Model* StaticTranslate(glm::vec3 translation);
    Model* Translate(glm::vec3 translation);
    Model* Scale(float scale);
    
    glm::mat4 getModelMat();
    glm::vec4 getTransformVec();
    
    glm::vec3 getTranslation();
    
private:
	std::vector<float> mBuffer;// = std::vector<float>();
    
    std::vector<std::shared_ptr<Vertex>> mVertices = std::vector<std::shared_ptr<Vertex>>();
    std::vector<std::shared_ptr<glm::vec3>> mNormals = std::vector<std::shared_ptr<glm::vec3>>();
    std::vector<std::shared_ptr<glm::vec2>> mUVs = std::vector<std::shared_ptr<glm::vec2>>();
    //std::vector<unsigned> mVertexIndices = std::vector<unsigned>();//TODO maybe. For glDrawElements
    
    std::vector<std::shared_ptr<Joint>> mJoints = std::vector<std::shared_ptr<Joint>>();
    std::vector<std::shared_ptr<JointGroup>> mJointGroups = std::vector<std::shared_ptr<JointGroup>>();
    
    std::shared_ptr<Joint> mJointsTree = std::make_shared<Joint>();
    
    std::string mTexturePath = "";
    GLuint mTexture;
    bool mIsTexLoaded = false;
    
    //Model transformation matrices
    glm::mat4 mTranslationMat = glm::mat4(1.f),
            mScaleMat = glm::mat4(1.f);
    glm::vec3 mTotalTranslation = glm::vec3();
};

#endif /* Model_hpp */
