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

#ifndef _SPRITE_MANAGER
#define _SPRITE_MANAGER

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "core/shader.h"
#include "gfx/sprite.h"
#include "util/pngfuncs.h"

/**
 * @class Camera class
 * @brief class handling the sprite manager
 */
class SpriteManager {
private:
    std::vector<Sprite> sprites;
    std::unique_ptr<Shader> shader;

    GLuint texture;

public:

    /**
     * @brief       get a reference to the sprite manager object
     *
     * @return      reference to the sprite manager object (singleton pattern)
     */
    static SpriteManager& get() {
        static SpriteManager sprite_manager;
        return sprite_manager;
    }

    inline const Sprite* get_sprite_pointer(unsigned int idx) const {
        return &this->sprites[idx];
    }

    void bind_sprites() {
        glBindTexture(GL_TEXTURE_2D, this->texture);
        this->shader->link_shader();
        this->shader->set_uniform(1, NULL); // set texture id
    }

    void unbind_sprites() {
        this->shader->unlink_shader();
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);
    }

    inline Shader* get_shader() const {
        return this->shader.get();
    }

private:
    /**
     * @brief       sprite manager constructor
     *
     * @return      sprite manager instance
     */
    SpriteManager();

    SpriteManager(SpriteManager const&)          = delete;
    void operator=(SpriteManager const&)  = delete;
};

#endif // _SPRITE_MANAGER
