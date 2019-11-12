//
//  ModeldLoader.cpp
//  PoorWand
//
//  Created by Andlat on 2018-11-29.
//  Copyright © 2018 poorwand. All rights reserved.
//

#ifndef ModelLoader_inl
#define ModelLoader_inl

#include <memory>
#include <fstream>
#include <string>

#include "MovingModel.hpp"
#include "Hero.hpp"

template <typename T>
std::shared_ptr<T> ModelLoader::Parse(std::string filepath){
    using namespace std;
    
    shared_ptr<T> model = make_shared<T>();
    
    ifstream file;
    file.exceptions(ifstream::failbit);
    
    try{
        file.open(filepath, ios::binary);
        string line;
        
		try {
			while (getline(file, line)) {
				ParseLine(model, line);
				++mLineCount;
			}
		}catch(ifstream::failure e){}//Ignore failbit from getline, because it will set it when it reaches the eof

        file.close();
    }catch(ifstream::failure e){
        cerr << "Failed to load model: " << filepath << '\n' << e.what() << endl;
        return nullptr;
    }
    
    //model->Construct(0);
    return model;
}

template std::shared_ptr<MovingModel> ModelLoader::Parse<MovingModel>(std::string filepath);
template std::shared_ptr<Hero> ModelLoader::Parse<Hero>(std::string filepath);
//template std::shared_ptr<StaticModel> ModelLoader::Parse<StaticModel>(std::string filepath);

#endif /* ModelLoader_inl */
