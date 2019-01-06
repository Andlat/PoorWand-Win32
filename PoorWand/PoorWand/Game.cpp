//
//  Game.cpp
//  PoorWand
//
//  Created by Andlat on 2018-06-09.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma clang diagnostic pop

#include <SOIL2/SOIL2.h>

#include "Game.hpp"

#include "Constants.h"
#include "misc.hpp"
#include "MovingModel.hpp"
#include "Hero.hpp"
#include "ModelLoader.hpp"
#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "KeyboardS.hpp"

using namespace std;

Game::Game(shared_ptr<Window> window)
: mWindow(window)
{
    mLastFrameTime = std::chrono::high_resolution_clock::now();
}

Game::~Game(){
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

long Game::getTimeDelta(){
    return mTimeDelta;
}

void Game::TrackTimeDelta(){
    using namespace std::chrono;
    auto currentTime = high_resolution_clock::now();
    
    mTimeDelta = duration_cast<microseconds>(currentTime - mLastFrameTime).count();
    
    mLastFrameTime = currentTime;
}

void Game::Loop(){
    shared_ptr<Hero> hero = ModelLoader().Parse<Hero>(PATH::MODELS+"sphere_tex_bones.dat");
    hero->Construct(0);
    hero->setSpeed(3.f);
    
    shared_ptr<MovingModel> wall1 = ModelLoader().Parse<MovingModel>(PATH::MODELS+"cube1.dat");
    wall1->Construct(1);
    
    shared_ptr<MovingModel> wall2 = ModelLoader().Parse<MovingModel>(PATH::MODELS+"cube1.dat");
    wall2->Construct(1);

    shared_ptr<MovingModel> wall3 = ModelLoader().Parse<MovingModel>(PATH::MODELS+"cube1.dat");
    wall3->Construct(1);
    
    shared_ptr<MovingModel> wall4 = ModelLoader().Parse<MovingModel>(PATH::MODELS+"cube1.dat");
    wall4->Construct(1);
    
    wall1->StaticTranslate(glm::vec3(3, -2, 0));
    wall2->StaticTranslate(glm::vec3(-3, 2, 0));
    wall3->StaticTranslate(glm::vec3(3, 2, 0));
    wall4->StaticTranslate(glm::vec3(-3, -2, 0));
    
    vector<float> buff = hero->getBuffer();
    wall1->AppendToGlobalBuffer(buff);
    wall2->AppendToGlobalBuffer(buff);
    wall3->AppendToGlobalBuffer(buff);
    wall4->AppendToGlobalBuffer(buff);
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //Set buffer data
    const unsigned buff_byte_size = (unsigned)buff.size()*FLOAT_SIZE();
    glBufferData(GL_ARRAY_BUFFER, buff_byte_size, &buff[0], GL_DYNAMIC_DRAW);
    
    cout << buff.size() << endl;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_ATTR::STRIDE*FLOAT_SIZE(), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GL_ATTR::STRIDE*FLOAT_SIZE(), (GLvoid*)(3*FLOAT_SIZE()));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, GL_ATTR::STRIDE*FLOAT_SIZE(), (GLvoid*)(6*FLOAT_SIZE()));
    //glVertexAttribIPointer(3, 1, GL_INT, GL_ATTR::STRIDE*FLOAT_SIZE(), (GLvoid*)(8*sizeof(GL_INT)));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, GL_ATTR::STRIDE*FLOAT_SIZE(), (GLvoid*)(8*FLOAT_SIZE()));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    
    //Create shaders
    ShaderProgram program = ShaderProgram();
     try{
         Shader vshader(GL_VERTEX_SHADER), fshader(GL_FRAGMENT_SHADER);
        
         vshader.Load(PATH::SHADERS+"basic.v.glsl");
         fshader.Load(PATH::SHADERS+"basic.f.glsl");
         
         vshader.Compile();
         fshader.Compile();

         program.Attach(&vshader)->Attach(&fshader);
         
         program.Link();
         
         program.Detach(&vshader)->Detach(&fshader);
         vshader.Delete();
         fshader.Delete();
     }catch(Shader::ShaderException e){
         cerr << e.what() << endl;
         return;//Exit from game
     }
    glUseProgram(program.get());

    cout << "ERROR: " << to_string(glGetError()) << endl;
    
    //Temporary camera
    //hero->Translate(glm::vec3(5, 4, 0));//->Scale(0.75);
    
    Camera camera = Camera(0.1f, 100.f, (float)mWindow->getWidth()/(float)mWindow->getHeight(), C_PI_4);
    camera.setPosition(glm::vec3(0, 0, 10));
    camera.Follow(hero, false);
    
    hero->LoadTexture(true, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
    
    while(!glfwWindowShouldClose(mWindow->get())){
        TrackTimeDelta();
        
        //Execute the hero's movements
        hero->ActivateFrameControls(getTimeDelta());
        
        glClearColor(0.8f, 0, 0.5f, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //Send texture //TODO texture manager
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, hero->getTexture());
        glUniform1i(glGetUniformLocation(program.get(), "tex"), GL_TEXTURE0-GL_TEXTURE0);
        
        //Send cameras
        const glm::mat4 mvp[] = {camera.Construct(hero->getModelMat()), camera.Construct(wall1->getModelMat())};
       
        glUniformMatrix4fv(glGetUniformLocation(program.get(), "MVP"), 2, GL_FALSE, glm::value_ptr(mvp[0]));
       
        glDrawArrays(GL_TRIANGLES, 0, ((unsigned)buff.size()/GL_ATTR::STRIDE));
        //cout << getTimeDelta() << endl;
        
        glfwSwapBuffers(mWindow->get());
        glfwPollEvents();
        
        //break;
    }
}
