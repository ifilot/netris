/**************************************************************************
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation, version 3                              *
 *                                                                        *
 *   This program is distributed in the hope that it will be useful, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    *
 *   General Public License for more details.                             *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program; if not, write to the Free Software          *
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA            *
 *   02110-1301, USA.                                                     *
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
    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    std::vector<uint8_t> pixels;

    png_uint_32 width, height;
    int col, bit_depth;

    PNG::load_image_buffer_from_png(AssetManager::get().get_root_directory() + "assets/png/blocks.png",
                                    pixels,
                                    &width,
                                    &height,
                                    &col,
                                    &bit_depth);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);

    // load sprites
    std::vector<glm::vec2> uv;
    uv.push_back(glm::vec2(0,0));
    uv.push_back(glm::vec2(16.f/128.f,0));
    uv.push_back(glm::vec2(16.f/128.f,1.0));
    uv.push_back(glm::vec2(0.0,1.0));
    for(unsigned int i=0; i<7; i++) {
        this->sprites.push_back(Sprite(&uv[0][0]));

        for(unsigned int j=0; j<uv.size(); j++) {
            uv[j] += glm::vec2(16.f/128.f, 0.0f);
        }
    }
}
