//
//  main.cpp
//  PoorWand
//
//  Created by Andlat on 2018-06-08.
//  Copyright © 2018 poorwand. All rights reserved.
//

#include <iostream>
#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>

#include <glm/gtx/string_cast.hpp>
#pragma clang diagnostic pop

#include "Window.hpp"
#include "Game.hpp"
#include "ModelLoader.hpp"
#include "KeyboardS.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    shared_ptr<Window> window;
    unique_ptr<Game> game;
    
    try{
        window = make_shared<Window>(800, 500, "PoorWand");
        
        //Initialize the keyboard
        KeyboardS& keyboard = KeyboardS::Instance();
        keyboard.bindWindow(window->get());
        
        //Quit on super+Q
        keyboard.addKey(GLFW_KEY_Q, GLFW_PRESS, [](GLFWwindow* window, int mods){
            if((mods & GLFW_MOD_SUPER) == GLFW_MOD_SUPER){
                glfwDestroyWindow(window);
                glfwTerminate();
            }
        });
        
        
        
        game = make_unique<Game>(window);
        game->Loop();
    }catch(Window::exception &ex){
        cerr << ex.what() << endl;
        return -1;
    }
    
    return 0;
}

/*
 void unit_test_joints_tree(shared_ptr<Joint> node);
 void unit_test_joint_groups(shared_ptr<Model> model);
 void unit_test_vertices(shared_ptr<Model> model);
 void unit_test_print_vert_buff(shared_ptr<Model> model);
 void unit_test_model_buffer(shared_ptr<Model> model);
 */

/*
void unit_test_joints_tree(shared_ptr<Joint> node){
    cout << glm::to_string(node->getTransform()) << endl;
    
    for(auto child : node->getChildren()){
        unit_test_joints_tree(child);
    }
}

void unit_test_joint_groups(shared_ptr<Model> model){
    const vector<shared_ptr<JointGroup>> groups = model->getJointGroups();
    for(unsigned i = 0; i < groups.size(); ++i){
        auto group = groups.at(i);
        cout << "g ";
        for(unsigned i=0; i < group->getJoints().size(); ++i){
            cout << group->getWeight(i) << " , " << glm::to_string(group->getJoint(i)->getTransform()) << " ; ";
        }
        cout << endl;
    }
}

void unit_test_vertices(shared_ptr<Model> model){
    auto vertices = model->getVertices();
    for(unsigned i=0; i < vertices.size(); ++i){
        const auto vertex = vertices[i];
        float* buff = vertex->getBuff();
        
        cout << "v " << buff[0] << ' ' << buff[1] << ' ' << buff[2] << '\n' << vertex->getGroup()->getWeights()[0] << '\n' << endl;
    }
}

void unit_test_print_vert_buff(shared_ptr<Model> model){
    auto vertices = model->getVertices();
    for(unsigned i=0; i < vertices.size(); ++i){
        const auto vertex = vertices[i];
        
        cout << "vertex: " << vertex->buff_to_string() << endl;
    }
}


void unit_test_model_buffer(shared_ptr<Model> model){
    cout << "Model buffer: ";
    for(float f : model->getBuffer()){
        cout << to_string(f) << ' ';
    }
    cout << endl << endl;
}
*/
