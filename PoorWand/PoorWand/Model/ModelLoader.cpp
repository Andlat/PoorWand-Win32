//
//  ModelLoader.cpp
//  PoorWand
//
//  Created by Andlat on 2018-11-09.
//  Copyright © 2018 poorwand. All rights reserved.
//


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


#include <fstream>
#include <string>
#include <iostream>
#include <memory>

#include "ModelLoader.hpp"

#include "Model.hpp"
#include "Joint.hpp"
#include "JointGroup.hpp"
#include "misc.hpp"

using namespace std;

ModelLoader::ModelLoader()
{
}

void ModelLoader::ParseLine(shared_ptr<Model> model, const string &line){
    auto line_array = misc::explode(line, ' ');
    const char type = line_array[0].c_str()[0];
    switch(type){
        case 'j':
        {
            float mat_buff[16];
            for(char i=1; i < 17; ++i){
                mat_buff[i-1] = stof(line_array[i]);
            }
            
            glm::mat4 transform = glm::make_mat4(mat_buff);
            
            model->addJoint(make_shared<Joint>(transform), stof(line_array[17]));
        }
            break;
        case 'g':
            if(mGroupLine == 0) mGroupLine = mLineCount;
        {
            auto group = make_shared<JointGroup>();
            
            const unsigned size = (unsigned)line_array.size();
            for(unsigned i=1; i < size; ++i){
                const unsigned joint_index = stoi(line_array[i]);
                const float weight = stof(line_array[++i]);
                group->addJoint(model->getJoints()[joint_index], weight);
            }
            
            model->addJointGroup(group);
            break;
        }
        case 'v':
            if(mVertLine == 0) mVertLine = mLineCount;
        {
            auto vertex = make_shared<Vertex>(stof(line_array[1]), stof(line_array[2]), stof(line_array[3]), model->getJointGroups().at(stoi(line_array[4])-mGroupLine));
            
            mVertices.push_back(vertex);
        }
            break;
        case 'n':
            if(mNormalLine == 0) mNormalLine = mLineCount;
            mNormals.push_back(glm::vec3(stoi(line_array[1]), stoi(line_array[2]), stoi(line_array[3])));
            break;
        case 'u':
            if(mUVLine == 0) mUVLine = mLineCount;
            
            mUVs.push_back(glm::vec2(stof(line_array[1]), stof(line_array[2])));
            break;
        case 'f':
            for(char i=1; i <= 3; ++i){
                vector<string> face_array = misc::explode(line_array[i], '/');
                
                unsigned v_i = stoi(face_array[0])-mVertLine,
                        n_i = stoi(face_array[1])-mNormalLine,
                        uv_i = stoi(face_array[2])-mUVLine;
                
                
                //shared_ptr<Vertex> vertex = mVertices[v_i];
                //glm::vec3* normal = &mNormals[n_i];
                //glm::vec2* uv = &mUVs[uv_i];
                
                model->addVertex(mVertices[v_i]);
                model->addNormal(make_shared<glm::vec3>(mNormals[n_i]));
                model->addUV(make_shared<glm::vec2>(mUVs[uv_i]));
                
                //vertex->setNormal((*normal)[0], (*normal)[1], (*normal)[2]);
                //cout << (*normal)[0] <<  (*normal)[1] << (*normal)[2] << endl;
                //vertex->setNormal(1, 1, 1);
                //vertex->setUV((*uv)[0], (*uv)[1]);
            
                //model->addVertex(vertex);
                
                //cout << model->getVertices().size() << "   " << model->getVertices().back()->buff_to_string() << endl;
            }
            break;
        case 't':
            model->setTexturePath(line_array[1]);
            break;
    }
}
