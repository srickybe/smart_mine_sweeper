/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OBJLoader2.h
 * Author: john
 *
 * Created on 24 juillet 2021, 20:48
 */

#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <boost/shared_array.hpp>
#include <memory>
#include <cassert>
#include <fstream>

#include "Model.h"
#include "Vector3D.h"


namespace ngn {

    class ModelLoader {
    public:

        ModelLoader();
        std::shared_ptr<Model> loadModel(char const * filePath);
    };

    
    ModelLoader::ModelLoader() {

    }

    
    std::shared_ptr<Model> ModelLoader::loadModel(const char* filePath) {
        std::string file = filePath;
        std::ifstream in(file.c_str());
        assert(in);

        std::shared_ptr<Model> model(new Model());
        std::shared_ptr<std::vector<Vector3D>> points(new std::vector<Vector3D> ());
        model->setPoints(points);
        std::shared_ptr<MaterialManager> materialManager;
        std::string str("  ");
        int bufferSize = 1024;
        boost::shared_array<char> buffer(new char[bufferSize]);

        while (in.getline(buffer.get(), bufferSize, '\n')) {
            str[0] = buffer[0];
            str[1] = buffer[1];
        }

        return model;
    }
}

#endif /* MODEL_LOADER_H */

