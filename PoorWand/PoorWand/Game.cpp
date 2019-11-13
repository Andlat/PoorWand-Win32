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
#include <cmath>


#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>


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
#include "TextureManager.hpp"

using namespace std;

Game::Game(shared_ptr<Window> window)
: mWindow(window)
{
    mLastFrameTime = std::chrono::high_resolution_clock::now();
}

Game::~Game(){
    mVBOMan->Delete();
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

shared_ptr<Shader> Game::CreateBasicShader(shared_ptr<ShaderProgram> program, string shader_path, GLuint type){
    if(type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER) return nullptr;
    
    shared_ptr<Shader> shader = nullptr;
    try{
        shader = make_shared<Shader>(type);
        
        shader->Load(shader_path);
        
        shader->Compile();
        
        program->Attach(shader.get())->Link();
        
    }catch(Shader::ShaderException e){
        cerr << e.what() << endl;
        return nullptr;//Exit from game
    }
    
    return shader;
}

void Game::Init(){
    //Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    //Create VBO
    mVBOMan = make_unique<VBOManager>();
    
    //Set attribs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_ATTR::STRIDE*FLOAT_SIZE(), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GL_ATTR::STRIDE*FLOAT_SIZE(), (GLvoid*)(3*FLOAT_SIZE()));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, GL_ATTR::STRIDE*FLOAT_SIZE(), (GLvoid*)(6*FLOAT_SIZE()));
    //glVertexAttribIPointer(3, 1, GL_INT, GL_ATTR::STRIDE*FLOAT_SIZE(), (GLvoid*)(8*sizeof(GL_INT)));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, GL_ATTR::STRIDE*FLOAT_SIZE(), (GLvoid*)(8*FLOAT_SIZE()));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    
    
    //Load models and create map
    hero = ModelLoader().Parse<Hero>(PATH::MODELS+"guy3.dat");
	if (hero != nullptr) {
		hero->Construct(0);
		hero->setSpeed(5.f);
		cout << "joints: " << misc::to_string(hero->getJoints()) << endl;
		cout << "HERO LOADDED" << endl;

		wall = ModelLoader().Parse<MovingModel>(PATH::MODELS+"cube1.dat");
		if(wall != nullptr)
			wall->Construct(1);
			
		heroID = mVBOMan->addModel(hero);
		hero->LoadTexture(true, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);//For now, all the models use the same texture
		
		//Exemple creating multiple static objects with only one model and one camera
		for(unsigned x=0; x < 2; ++x){
			glm::vec3 pos(3 * pow(-1.f, x%2), 0.f, 0.f);

			for(unsigned y=0; y < 2; ++y){
				pos.y = 2 * pow(-1.f, y%2);

				wall->StaticTranslate(pos);
				mVBOMan->addModel(wall);

				//Replace wall to origin. Shouldn't do it like this, since StaticTranslate uses a lot of clock cycles, but for a demo, it's ok
				wall->StaticTranslate(pos *= -1);
			}
		}
		TextureManager l;
		//l.addModel(hero);
		


		//Create Shaders
		program = make_shared<ShaderProgram>();
		auto vshader = this->CreateBasicShader(program, PATH::SHADERS+"basic.v.glsl", GL_VERTEX_SHADER);
		auto fshader = this->CreateBasicShader(program, PATH::SHADERS+"basic.f.glsl", GL_FRAGMENT_SHADER);
		program->Detach(vshader.get());
		program->Detach(fshader.get());
		vshader->Delete();
		fshader->Delete();

		cout << "VBO Manager memory offset: " << mVBOMan->getMemoryOffset() << endl;
		cout << "ERROR: " << to_string(glGetError()) << endl;
	}

	//COUT BUFFER DATA
	float* data = new float[mVBOMan->getMemoryOffset()/FLOAT_SIZE()];
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, mVBOMan->getMemoryOffset(), data);
	for (int i = 0; i < mVBOMan->getMemoryOffset() / (FLOAT_SIZE()); ++i) {
		cout << data[i] << ' ';
	}
	delete data;
	cout << "STRIDES: " << mVBOMan->getMemoryOffset() / (FLOAT_SIZE() * GL_ATTR::STRIDE) << endl;
}



void Game::Loop(){
    //Temporary camera
    hero->Translate(glm::vec3(5, 4, 0));//->Scale(0.75);
    
    //TEST VBOMAN->REMOVEMODEL
    KeyboardS& keyboard = KeyboardS::Instance();
    keyboard.addKey(GLFW_KEY_O, GLFW_PRESS, [this](GLFWwindow* window, int mods){
        cout << "HELLO " << endl;
        this->mVBOMan->removeModel(this->heroID, true);//TODO ERROR WHEN COMPACTING
    });
    
    Camera camera = Camera(0.1f, 100.f, (float)mWindow->getWidth()/(float)mWindow->getHeight(), C_PI_4);
    camera.setPosition(glm::vec3(0, 0, 15));
    //camera.Follow(hero, false); TODO TEST THIS AGAIN> MIGHT NOT BE WORKING
    
    glUseProgram(program->get());
    
    //Send texture. Every model is using the same texture //TODO texture manager
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, hero->getTexture());
    
    while(!glfwWindowShouldClose(mWindow->get())){
        TrackTimeDelta();
        
        //Execute the hero's movements
        if(heroID != 0){
            hero->ActivateFrameControls(getTimeDelta());
        }
        
        glClearColor(0.8f, 0, 0.5f, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(program->get(), "tex"), GL_TEXTURE0-GL_TEXTURE0);
    
        //Send cameras
        const glm::mat4 mvp[] = {camera.Construct(hero->getModelMat()), camera.Construct(wall->getModelMat())};
       
        glUniformMatrix4fv(glGetUniformLocation(program->get(), "MVP"), 2, GL_FALSE, glm::value_ptr(mvp[0]));
		cout << glm::to_string(mvp[0]) << endl;
        glDrawArrays(GL_TRIANGLES, 0, mVBOMan->getMemoryOffset()/(FLOAT_SIZE() * GL_ATTR::STRIDE));

        //cout << getTimeDelta() << endl;
        
        glfwSwapBuffers(mWindow->get());
        glfwPollEvents();
        
        //break;
    }
    
    program->Delete();
}
