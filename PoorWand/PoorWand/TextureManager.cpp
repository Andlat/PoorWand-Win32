//
//  TextureManager.cpp
//  PoorWand
//
//  Created by Andlat on 2019-01-26.
//  Copyright © 2019 poorwand. All rights reserved.
//

#include "TextureManager.hpp"

#include <iostream>

using namespace std;

GLint TextureManager::mTextureUnits = -1;
TextureManager::TextureManager(){
    if(mTextureUnits == -1)//Get number of texture units in the gpu
        glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &mTextureUnits);
    
    mUnits.reserve(mTextureUnits);
}

char TextureManager::Unit::mTextureCount = 0;
TextureManager::Unit::Unit(){//Constructor for a texture unit
    if(mTextureCount < mTextureUnits){
        unit = GL_TEXTURE0 + mTextureCount;
        ++mTextureCount;
    }else{//Error. Trying to create more texture units than available in the gpu
        unit = -1;
    }
}

bool TextureManager::addModel(ModelID model, std::string tex_path){
    if(tex_path.empty()) return false;
    
    GLuint texture;
    bool isTexAlreadyBound = false;
    
    shared_ptr<Unit> unit = nullptr;
    
    auto it = mLoadedTextures.find(tex_path);
    
    if(it == mLoadedTextures.end()){//Not in set. Is a new texture
        texture = LoadTexture(tex_path, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, true);//Load the new texture
        
        mLoadedTextures.insert({tex_path, texture});//Load the texture
        
    }else{//Texture already stored in texture manager
        texture = mLoadedTextures.at(tex_path);
        
        //Check if the texture is bound
        unit = this->isTexBound(texture);
        if(unit != nullptr){//Tex is already bound
            isTexAlreadyBound = true;
        }
    }
    
    //Texture is loaded but not bound
    if(!isTexAlreadyBound){
        unit = this->Bind(texture);//Try to bind the texture
        if(unit == nullptr){//No texture units available
            //Associate model to its texture, which isn't loaded in a unit yet
            mUBModelTextures.insert(ModelTexturePair(model, texture));
        }
    }
    
    //Associate model to a bound unit
    mBModelUnit.insert(ModelUnitPair(model, unit));

    return true;
}

void TextureManager::removeModel(ModelID model){
    
}

shared_ptr<TextureManager::Unit> TextureManager::Bind(GLuint texture){
    //Find an empty unit
    shared_ptr<Unit> freeUnit = nullptr;
    for(auto unit : mUnits){
        if(unit == nullptr){
            freeUnit = unit;
            break;
        }
    }
    
    //If found a free unit, bind a texture to it
    if(freeUnit != nullptr){
        glActiveTexture(freeUnit->unit);
        glBindTexture(GL_TEXTURE_2D, freeUnit->texture);
    }
    
    return freeUnit;//Will be nullptr if no texture unit available
}

shared_ptr<TextureManager::Unit> TextureManager::isTexBound(GLuint texture){
    for(auto unit : mUnits){
        if(unit->texture == texture){
            return unit;
        }
    }
    return nullptr;
}

 GLuint TextureManager::LoadTexture(const std::string& texPath, GLfloat mag_filter, GLfloat min_filter, bool genMipmaps/*=true*/){
     GLuint texture;
     
     int width, height;
     unsigned char* image = SOIL_load_image(texPath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

     glGenTextures(1, &texture);
     glBindTexture(GL_TEXTURE_2D, texture);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

     SOIL_free_image_data(image);

     if(genMipmaps) glGenerateMipmap(GL_TEXTURE_2D);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

     return texture;
}
