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

class Game{
public:
    Game(std::shared_ptr<Window> window);
    ~Game();
    
    long getTimeDelta();
    void Loop();
private:
    GLuint VAO, VBO;
    
    void TrackTimeDelta();
    
    const std::shared_ptr<Window> mWindow;
    
    std::chrono::high_resolution_clock::time_point mLastFrameTime;
    long mTimeDelta;
};

#endif /* Game_hpp */
