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

#include "block.h"

Block::Block(const glm::vec2& _pos, const Sprite* _sprite) {
    this->pos = _pos;
    this->sprite = _sprite;
}

void Block::draw() {
    glm::mat4 mvp = glm::translate(Camera::get().get_projection() * Camera::get().get_view(), glm::vec3(this->pos + glm::vec2(1,1),0.0f));
    SpriteManager::get().get_shader()->set_uniform(0, &mvp[0][0]);
    this->sprite->draw();
}

void Block::translate(float x, float y) {
    this->pos[0] +=x;
    this->pos[1] +=y;
}
