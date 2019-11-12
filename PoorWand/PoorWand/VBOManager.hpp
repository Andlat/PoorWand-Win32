//
//  VBOManager.hpp
//  PoorWand
//
//  Created by Andlat on 2019-01-08.
//  Copyright © 2019 poorwand. All rights reserved.
//

#ifndef VBOManager_hpp
#define VBOManager_hpp

#include <GL/glew.h>

#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <utility>
#include <unordered_map>

#include "Model.hpp"
#include "GlobalTypedefs.h"

class VBOManager{
public:
    struct ModelInfo{
        //TODO why the fuck do I need an empty constructor to be able to use this struct as a return type ???
        ModelInfo(){
            std::cout << "\n\n\n******************\nWTF???????????\n********************\n\n\n" << std::endl;
        }
        ModelInfo(unsigned long bufferOffset, unsigned data_size_bytes){
            this->bufferOffset = bufferOffset;
            this->data_size_bytes = data_size_bytes;
        }
        
        unsigned long bufferOffset;
        unsigned data_size_bytes;
    };

public:
    VBOManager();
    VBOManager(int memoryMb);
    ~VBOManager();
    
    VBOManager* Bind();
    void Delete();
    
    ModelID addModel(std::shared_ptr<Model> model);
    /** Return False if the model_id was not found in this VBO. True if succeeded to remove model. **/
    bool removeModel(ModelID &model_id, bool compact=false);
    void Compact();
    
    ModelInfo getModelInfo(ModelID model_id);
    /** Return offset of last added model in bytes **/
    unsigned long getMemoryOffset();
    
private:
    void init();
    
    void ReserveMemory();
    void addMemory(unsigned mem_to_add_bytes = MEMORY_JUMP);
    
    GLuint VBO;
    
    static ModelID mModelUniqueID;
    
    const static unsigned short MEMORY_JUMP = 1;
    unsigned mMemoryMb = 1;
    /**
     * mMemoryOffsetBytes Track the end of the data in the buffer
     * mMemoryUsedBytes Tracks the amount of memory used until the offset. Difference with offset is that it doesn't count empty pools
     */
    long mMemoryUsedBytes = 0, mMemoryOffsetBytes = 0;
    
    std::unordered_map<ModelID, ModelInfo> mModelsInfo = std::unordered_map<ModelID, ModelInfo>();
    
    //TODO Maybe could have used a map here instead of this, since they are ordered by their key. Which an ordered map would do automatically.
    typedef std::pair<unsigned long, unsigned> PoolPair;//pair<offset_in_buffer, size_in_bytes>
    /** Comparator for the empty pools' set. Will keep the pools ordered **/
    struct PoolCmp{ bool operator()(const PoolPair &a, const PoolPair &b){ return a.first < b.first; } };
    std::set<PoolPair, PoolCmp> mEmptyPools = std::set<PoolPair, PoolCmp>();
};


#endif /* VBOManager_hpp */
