//
//  Game.hpp
//  PoorWand
//
//  Created by Andlat on 2018-06-09.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <memory>
#include <chrono>

#include "Window.hpp"
#include "VBOManager.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Hero.hpp"
#include "MovingModel.hpp"

class Game{
public:
    Game(std::shared_ptr<Window> window);
    ~Game();
    
    long getTimeDelta();
    
    void Init();
    void Loop();
private:
    void TrackTimeDelta();
    
    std::shared_ptr<Shader> CreateBasicShader(std::shared_ptr<ShaderProgram> program, std::string vert_shader_path, GLuint type);
    
    GLuint VAO;
    std::unique_ptr<VBOManager> mVBOMan;
    
    const std::shared_ptr<Window> mWindow;
    
    std::chrono::high_resolution_clock::time_point mLastFrameTime;
    long mTimeDelta;
    
    //Temp vars for testing
    std::shared_ptr<ShaderProgram> program;
    std::shared_ptr<Hero> hero;
    ModelID heroID;
    std::shared_ptr<MovingModel> wall;
};

#endif /* Game_hpp */
