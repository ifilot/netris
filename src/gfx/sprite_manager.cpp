/**************************************************************************
 *   sprite_manager.cpp  --  This file is part of Netris.                 *
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

#include "sprite_manager.h"

SpriteManager::SpriteManager() {
    // load shader
    this->shader = std::unique_ptr<Shader>(new Shader("assets/shaders/sprite"));
    this->shader->add_attribute(ShaderAttribute::POSITION, "position");
    this->shader->add_attribute(ShaderAttribute::TEXTURE_COORDINATE, "texcoord");
    this->shader->add_uniform(ShaderUniform::MAT4, "mvp", 1);
    this->shader->add_uniform(ShaderUniform::TEXTURE, "tex", 1);
    this->shader->set_texture_id(1); // corresponds to GL_TEXTURE1

    this->shader->bind_uniforms_and_attributes();

    // load texture
    this->load_texture("assets/png/blocks.png", 0);
    this->load_texture("assets/png/border.png", 1);

    // load sprites BLOCKS
    std::vector<glm::vec2> uv;
    uv.push_back(glm::vec2(0.5f/128.f,0.5f/128.f));
    uv.push_back(glm::vec2(15.5f/128.f,0.5f/128.f));
    uv.push_back(glm::vec2(15.5f/128.f,15.5f/16.f));
    uv.push_back(glm::vec2(0.5f/128.f,15.5f/16.f));

    for(unsigned int i=0; i<7; i++) {
        this->sprites.push_back(Sprite(&uv[0][0]));

        for(unsigned int j=0; j<uv.size(); j++) {
            uv[j] += glm::vec2(16.f/128.f, 0.0f);
        }
    }

    // load sprites BORDER
    uv.clear();
    uv.push_back(glm::vec2(0.5f/48.f,0.5f/48.f));
    uv.push_back(glm::vec2(15.5f/48.f,0.5f/48.f));
    uv.push_back(glm::vec2(15.5f/48.f,15.5f/48.f));
    uv.push_back(glm::vec2(0.5f/48.f,15.5f/48.f));

    for(unsigned int i=0; i<3; i++) {
        for(unsigned int j=0; j<3; j++) {
            this->sprites.push_back(Sprite(&uv[0][0]));
            for(unsigned int k=0; k<uv.size(); k++) {
                uv[k] += glm::vec2(16.f/48.f, 0.0f);
            }
        }
        for(unsigned int k=0; k<uv.size(); k++) {
            uv[k] += glm::vec2(-1.f, 16.f / 48.f);
        }
    }
}

void SpriteManager::load_texture(const std::string& filename, unsigned int id) {
    glActiveTexture(GL_TEXTURE1);

    glGenTextures(1, &this->textures[id]);
    glBindTexture(GL_TEXTURE_2D, this->textures[id]);

    std::vector<uint8_t> pixels;
    png_uint_32 width, height;
    int col, bit_depth;

    PNG::load_image_buffer_from_png(AssetManager::get().get_root_directory() + filename,
                                    pixels,
                                    &width,
                                    &height,
                                    &col,
                                    &bit_depth,
                                    true);  // automatically invert the image

    switch(col) {
        case PNG_COLOR_TYPE_RGB:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);
        break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
        break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);
}
