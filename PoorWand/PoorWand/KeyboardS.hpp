//
//  Keyboard.hpp
//  PoorWand
//
//  Created by Andlat on 2018-12-12.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef Keyboard_hpp
#define Keyboard_hpp

#include <GL/glew.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include <memory>
#include <functional>
#include <vector>
#include <utility>

/**
 * Keyboard singleton class. Works with GLFW and can only bind it to one window
 **/
class KeyboardS{
public:
    static KeyboardS& Instance();
    static KeyboardS& Instance(GLFWwindow* window);
    
    void bindWindow(GLFWwindow* window);
    
    //Forbid copying of the singleton
    KeyboardS(KeyboardS const&) =delete;
    void operator=(KeyboardS const&) =delete;
    
    struct Callback{
        Callback(int key, int action, std::function<void(GLFWwindow*, int)> callback){
            this->key = key;
            this->action = action;
            this->callback = callback;
        }
        
        int key;
        int action;
        std::function<void(GLFWwindow*, int)> callback;
    };
    
    /**
     * @param key Key associated to the callback. GLFW_KEY_*
     * @param action Action done with the key GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT
     * @param callback Callback function to do when the key and action match. function(GLFWwindow* window, int mods) mods is modifier keys like GLFW_MOD_SUPER
     */
    void addKey(int key, int action, std::function<void(GLFWwindow*, int)> callback);
    
    /**
     * @param fn Function to call when polling events. This function is not binded to any key and will be called on each poll (on each frame).
     **/
    void addEvent(std::function<void(void)> fn);
private:
    KeyboardS();
    
    friend void MainCallback(GLFWwindow*, int, int, int, int);
    
    std::vector<std::shared_ptr<Callback>> mCallbacks;
    std::vector<std::function<void(void)>> mEvents;//Callbacks not binded to keys
    
};

void MainCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif /* Keyboard_hpp */
