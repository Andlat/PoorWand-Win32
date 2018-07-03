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

#include "Window.hpp"

class Game{
public:
    Game(std::shared_ptr<Window> window);
    ~Game();
    
    void Loop();
private:
    const std::shared_ptr<Window> mWindow;
};

#endif /* Game_hpp */
