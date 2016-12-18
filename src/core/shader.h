/**************************************************************************
 *   shader.h  --  This file is part of Netris.                           *
 *                                                                        *
 *   Copyright (C) 2016, Ivo Filot                                        *
 *                                                                        *
 *   Netris is free software: you can redistribute it and/or modify       *
 *   it under the terms of the GNU General Public License as published    *
 *   by the Free Software Foundation, either version 3 of the License,    *
 *   or (at your option) any later version.                               *
 *                                                                        *
 *   Netris is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty          *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.              *
 *   See the GNU General Public License for more details.                 *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program.  If not, see http://www.gnu.org/licenses/.  *
 *                                                                        *
 **************************************************************************/

#ifndef _SHADER_H
#define _SHADER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "core/asset_manager.h"
#include "core/camera.h"

class ShaderUniform {
public:
    ShaderUniform(unsigned int _type, const std::string& _name, unsigned int _size);

    void specify_value(float* val);

    void bind_uniform(GLuint program_id);

    inline const std::string& get_name() const {
        return this->name;
    }

    inline unsigned int get_type() const {
        return this->type;
    }

    inline unsigned int get_size() const {
        return this->size;
    }

    enum {
        MAT4,
        MAT3,
        VEC4,
        VEC3,
        VEC2,
        TEXTURE,
        UINT,
        FLOAT,
        FRAME_MATRIX,
        OFFSET_MATRIX,

        NUM_VAR_TYPES
    };

private:
    unsigned int type;                           //<! type of the variable
    std::string name;                            //<! name of the variable
    unsigned int size;                           //<! size of the uniform
};

class ShaderAttribute {
public:
    ShaderAttribute(unsigned int _type, const std::string& _name);

    enum {
        POSITION,
        NORMAL,
        COLOR,
        TEXTURE_COORDINATE,
        WEIGHT,

        NUM_ATTR_TYPES
    };

    inline const std::string& get_name() const {
        return this->name;
    }

    inline unsigned int get_type() const {
        return this->type;
    }

private:
    unsigned int type;                           //<! type of the variable
    std::string name;                            //<! name of the variable
};

class Shader{
public:
    Shader(const std::string& _filename);

    void add_uniform(unsigned int type, const std::string& name, unsigned int size);

    void add_attribute(unsigned int type, const std::string& name);

    void bind_uniforms_and_attributes();

    void set_uniform(unsigned int uniform_id, const float* val);

    inline long unsigned int get_nr_attributes() const {
        return this->shader_attributes.size();
    }

    inline long unsigned int get_nr_uniforms() const {
        return this->shader_uniforms.size();
    }

    inline void link_shader() {
        glUseProgram(this->m_program);
    }

    inline void unlink_shader() {
        glUseProgram(0);
    }

    inline bool is_loaded() const {
        return flag_loaded;
    }

    inline void set_texture_id(GLuint _texture_id) {
        this->texture_id = _texture_id;
    }

    virtual ~Shader();

protected:

private:
    static const unsigned int NUM_SHADERS = 2;    // set number of shaders
    Shader(const Shader& other) = delete;         // initialization constructor
    void operator=(const Shader& other) = delete; // copy constructor

    GLuint m_program;                           // reference pointer to the program
    GLuint m_shaders[NUM_SHADERS];              // reference array to the shaders

    std::vector<ShaderAttribute> shader_attributes;
    std::vector<ShaderUniform> shader_uniforms; //<! vector holding shader uniforms
    std::vector<GLuint> m_uniforms;             // reference array to the uniforms

    bool flag_loaded;
    GLuint texture_id;
    std::string filename;


};

#endif //_SHADER_H
