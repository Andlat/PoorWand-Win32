//
//  TextureManager.hpp
//  PoorWand
//
//  Created by Andlat on 2019-01-26.
//  Copyright © 2019 poorwand. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
#include <memory>
#include <utility>

#include <GL/glew.h>

#include "GlobalTypedefs.h"
#include "Model.hpp"

class TextureManager{
public:
    TextureManager();
    
    bool addModel(ModelID model, std::string tex_path);
    void removeModel(ModelID model);
    
    //std::set<ModelID> Order();
private:
    static GLint mTextureUnits;
    
    /**
     * A texture unit
     */
    struct Unit{
        Unit();
        
        GLuint texture;
        char unit;
    private:
        static char mTextureCount;
    };
    
    /**
     * Vector the size of the number of texture units. Available units are nullptr.
     */
    std::vector<std::shared_ptr<Unit>> mUnits = std::vector<std::shared_ptr<Unit>>();
    
    
    /** Associate a path to a texture **/
    std::unordered_map<std::string, GLuint> mLoadedTextures = std::unordered_map<std::string, GLuint>();
    
    /**
     * Associate a Model to a texture. This is only for unbound textures
     **/
    typedef std::pair<ModelID, GLuint> ModelTexturePair;
    struct ModelTextureCmp{
        bool operator()(const ModelTexturePair &a, const ModelTexturePair &b){
            return a.second < b.second;
        }
    };
    std::set<ModelTexturePair, ModelTextureCmp> mUBModelTextures = std::set<ModelTexturePair, ModelTextureCmp>();
    //std::unordered_map<ModelID, GLuint> mUBModelTextures = std::unordered_map<ModelID, GLuint>();
    
    
    
    /**
     * Associate a model to a texture and to the unit the texture's bound to. This is only for models having bound textures.
     **/
    typedef std::pair<ModelID, std::shared_ptr<Unit>> ModelUnitPair;
    struct ModelUnitCmp{ bool operator()(const ModelUnitPair &a, const ModelUnitPair &b){ return a.second->unit < b.second->unit; } };//Order by unit
    std::set<ModelUnitPair, ModelUnitCmp> mBModelUnit = std::set<ModelUnitPair, ModelUnitCmp>();
    //std::map<ModelID, std::shared_ptr<Unit>> mBModelUnit = std::map<ModelID, std::shared_ptr<Unit>>();
    
    /**
     * Load a texture in memory
     * @return texture int from OpenGL for the loaded texture
     **/
    GLuint LoadTexture(const std::string& texPath, GLfloat mag_filter, GLfloat min_filter, bool genMipmaps=true);
    
    /**
     * Bind a texture to a texture unit
     * @return Unit where the texture was bound. Returns nullptr if not more texture units are available
     */
    std::shared_ptr<Unit> Bind(GLuint texture);
    
    /**
     * Find to which unit the texture is bound
     * @return Unit were the texture is bound or nullptr if the texture is not bound
     */
    std::shared_ptr<Unit> isTexBound(GLuint texture);
};

#endif /* TextureManager_hpp */
