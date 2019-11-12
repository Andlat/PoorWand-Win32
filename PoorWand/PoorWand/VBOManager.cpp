//
//  VBOManager.cpp
//  PoorWand
//
//  Created by Andlat on 2019-01-08.
//  Copyright © 2019 poorwand. All rights reserved.
//

#include "VBOManager.hpp"

#include <iostream>
#include <vector>
#include <set>
#include <stdexcept>

#include "Constants.h"
#include "misc.hpp"

using namespace std;

ModelID VBOManager::mModelUniqueID = 0;
VBOManager::VBOManager(){
    init();
}
VBOManager::VBOManager(int memoryMb)
: mMemoryMb(memoryMb)
{
    init();
}
void VBOManager::init(){
    glGenBuffers(1, &(this->VBO));
    
    this->Bind();
    ReserveMemory();//reserve memory in bytes
}

VBOManager::~VBOManager(){
    this->Delete();
}
void VBOManager::Delete(){ glDeleteBuffers(1, &(this->VBO)); }

VBOManager* VBOManager::Bind(){
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    return this;
}

void VBOManager::ReserveMemory(){
    cout << "reserved: " <<  misc::Mb2Bytes(mMemoryMb) << endl;
    glBufferData(GL_ARRAY_BUFFER, misc::Mb2Bytes(mMemoryMb), nullptr, GL_DYNAMIC_DRAW);
}
void VBOManager::addMemory(unsigned mem_to_add_Mb/*= MEMORY_JUMP*/){
    unsigned multiplier = mem_to_add_Mb / MEMORY_JUMP  + 1;

    //Copy current data in the buffer
    const auto current_mem = misc::Mb2Bytes(mMemoryMb);
    float current_data[current_mem/FLOAT_SIZE()];
    glGetBufferSubData(GL_ARRAY_BUFFER, 0, current_mem, &current_data[0]);
    
    //Reserve the new memory
    mMemoryMb += MEMORY_JUMP * multiplier;
    this->ReserveMemory();
    
    //Feed the current data into the new buffer
    glBufferSubData(GL_ARRAY_BUFFER, 0, current_mem, &current_data[0]);
}

ModelID VBOManager::addModel(std::shared_ptr<Model> model){
    vector<float> buff = model->getBuffer();
    const unsigned buff_size_bytes = (unsigned)buff.size() * FLOAT_SIZE();
    
    //Check if the reserved memory in OpenGL is big enough
    if(buff_size_bytes > misc::Mb2Bytes(mMemoryMb)){
        this->addMemory(misc::Bytes2Mb((unsigned)buff_size_bytes));
    }
    
    //Copy the model's buffer to OpenGL's buffer
    glBufferSubData(GL_ARRAY_BUFFER, mMemoryOffsetBytes, buff_size_bytes, &buff[0]);
    
    mModelsInfo.insert({++mModelUniqueID, ModelInfo(mMemoryOffsetBytes, buff_size_bytes)});//Keep track of the model's properties infside the buffer, by its unique id
    
    //Track offsets and memory
    mMemoryOffsetBytes += buff_size_bytes;//Track the end of the data in the buffer
    mMemoryUsedBytes += buff_size_bytes;//Tracks the amount of memory used until the offset. Difference is that it doesn't count empty pools
    
    return mModelUniqueID;
}

bool VBOManager::removeModel(ModelID &model_id, bool compact/*=false*/){
    ModelInfo* info = nullptr;
    try{ info = &mModelsInfo.at(model_id); }catch(std::out_of_range& ex){ return false; }//Return false if couldn't find element
    cout << " INFOR : " << info->bufferOffset << " : " << info->data_size_bytes << endl;
    mEmptyPools.insert(PoolPair(info->bufferOffset, info->data_size_bytes));
    mModelsInfo.erase(model_id);
    
    model_id = 0;//Reset the id
    
    if(compact){
        this->Compact();
    }
    
    return true;
}

/**
 * The implementation uses a naive solution which uses the least memory, but uses also the most cycles (2x as most as the solution which uses the most memory, but is the fastest, I think?). Look at physical note for more info.
 */
void VBOManager::Compact(){
    //The empty pools are already sorted with std::set and comparator VBOManager::PoolCmp

    unsigned long packed_offset=0;
    set<PoolPair>::iterator it, prev = mEmptyPools.end();
    for(it = mEmptyPools.begin(); it != mEmptyPools.end();){
        
        unsigned long data_start, data_end;
        unsigned size;
        
        //First pool
        if(prev == mEmptyPools.end()){
            packed_offset = it->first;
            cout << "PACKED OFF : " << packed_offset << endl;
            
            //TODO VERIFY IF THIS PART BELOW WORKS
        }else if(mEmptyPools.size() > 1){//Data between 2 pools. Only enter block if there is more than 1 pool
            //Size of the data between 2 pools
            //Offset Pool 2 - (Offset Pool 1 + Size Pool 1)
            data_end = it->first;
            data_start = prev->first + prev->second;
            size = unsigned(data_end - data_start);
            cout << "IN BETWEENE" << endl;
            if(size > 0){
                float buff[size];
                glGetBufferSubData(GL_ARRAY_BUFFER, data_start, size, &buff[0]);
                glBufferSubData(GL_ARRAY_BUFFER, packed_offset, size, &buff[0]);
            }
            packed_offset += size;
        }
        
        //THIS PART BELOW WORKS
        prev=it;//Keep track of the previous iterator
        //Check if last pool.
        if(++it == mEmptyPools.end()){//The set's iterator is incremented here.
            //Move the last piece of data between the last empty pool and the unpacked offset
            cout << "it.fisrt " << prev->first << "  it.second " << prev->second << endl;
            data_start = prev->first + prev->second;
            data_end = this->mMemoryOffsetBytes;
            size = unsigned(data_end - data_start);
            cout << "SIZE: " << size << " : START: " << data_start << endl;
            if(size > 0){
                float buff_last[size];
                glGetBufferSubData(GL_ARRAY_BUFFER, data_start, size, &buff_last[0]);
                glBufferSubData(GL_ARRAY_BUFFER, packed_offset, size, &buff_last[0]);
            }
            //Set the memory offset to the new packed one. The function is finished now.
            mMemoryOffsetBytes = packed_offset + size;
        }
    }
    
    mEmptyPools.clear();
}

VBOManager::ModelInfo VBOManager::getModelInfo(ModelID model_id){
    return mModelsInfo[model_id];
}
unsigned long VBOManager::getMemoryOffset(){ return mMemoryOffsetBytes; }





