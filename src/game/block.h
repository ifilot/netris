/**************************************************************************
 *   block.h  --  This file is part of Netris.                            *
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

#ifndef _BLOCK_H
#define _BLOCK_H

#include <glm/glm.hpp>
#include <cmath>

#include "gfx/sprite_manager.h"

class Block {
private:
    glm::vec2 pos;
    const Sprite* sprite;

public:
    Block(const glm::vec2& _pos, const Sprite* _sprite);

    void draw(const glm::mat4& mvp);

    void translate(float x, float y);

    inline void translate(const glm::vec2& dir) {
        this->translate(dir[0], dir[1]);
    }

    inline void set_pos(const glm::vec2& _pos) {
        this->pos = _pos;
    }

    inline const glm::vec2& get_pos() const {
        return this->pos;
    }

    inline void align() {
        this->pos[0] = round(this->pos[0]);
        this->pos[1] = round(this->pos[1]);
    }

    inline unsigned int slot_idx() const {
        return (unsigned int)(pos[1]) * 10 + (unsigned int)(pos[0]);
    }

private:

};

#endif // _BLOCK_H
