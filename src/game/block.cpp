/**************************************************************************
 *   block.cpp  --  This file is part of Netris.                          *
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

#include "block.h"

Block::Block(const glm::vec2& _pos, const Sprite* _sprite) {
    this->pos = _pos;
    this->sprite = _sprite;
}

void Block::draw(const glm::mat4& _mvp) {
    const glm::mat4 mvp = glm::translate(_mvp, glm::vec3(this->pos, 0.0f));
    SpriteManager::get().get_shader()->set_uniform(0, &mvp[0][0]);
    this->sprite->draw();
}

void Block::translate(float x, float y) {
    this->pos[0] +=x;
    this->pos[1] +=y;
}
