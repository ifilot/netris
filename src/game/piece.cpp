/**************************************************************************
 *   piece.cpp  --  This file is part of Netris.                          *
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

#include "piece.h"

Piece::Piece(unsigned int _type) {
    switch(_type) {
        case 0:
            this->add_block(0,0,0);
            this->add_block(-1,0,0);
            this->add_block(-1,-1,0);
            this->add_block(0,-1,0);
        break;
        case 1:
            this->add_block(0,0,1);
            this->add_block(-1,0,1);
            this->add_block(-2,0,1);
            this->add_block(1,0,1);
        break;
        case 2:
            this->add_block(0,0,2);
            this->add_block(-1,-1,2);
            this->add_block(0,-1,2);
            this->add_block(1,0,2);
        break;
        case 3:
            this->add_block(0,0,3);
            this->add_block(-1,0,3);
            this->add_block(0,-1,3);
            this->add_block(1,-1,3);
        break;
        case 4:
            this->add_block(0,0,4);
            this->add_block(-1,0,4);
            this->add_block(-1,-1,4);
            this->add_block(1,0,4);
        break;
        case 5:
            this->add_block(0,0,5);
            this->add_block(-1,0,5);
            this->add_block(1,-1,5);
            this->add_block(1,0,5);
        break;
        case 6:
            this->add_block(0,0,6);
            this->add_block(-1,0,6);
            this->add_block(0,-1,6);
            this->add_block(1,0,6);
        break;
    }

    type = _type;
}

void Piece::draw() {
    for(auto block = this->blocks.begin(); block != this->blocks.end(); block++) {
        block->draw();
    }
}

void Piece::add_block(float x, float y, unsigned int bt) {
    this->blocks.push_back(Block(glm::vec2(5+x,22+y), SpriteManager::get().get_sprite_pointer(bt)));
}

void Piece::translate(const glm::vec2& dir) {
    for(auto block = this->blocks.begin(); block != this->blocks.end(); block++) {
        block->translate(dir);
        block->align();
    }
}

void Piece::rotate(float angle) {
    if(type == 0) {
        return;
    }

    const glm::mat2 rot(std::cos(angle), -std::sin(angle),
                        std::sin(angle),  std::cos(angle));
    const glm::vec2 center = this->blocks.front().get_pos();

    for(auto block = this->blocks.begin(); block != this->blocks.end(); block++) {
        block->set_pos(rot * (block->get_pos() - center) + center);
        block->align();
    }
}

bool Piece::check_colission_translate(const std::bitset<240>& slots, const glm::vec2& dir) {
    for(auto block = this->blocks.begin(); block != this->blocks.end(); block++) {
        const glm::vec2 newpos = block->get_pos() + dir;
        if(newpos[0] < 0.0f || newpos[0] > 9 || newpos[1] < 0) {
            return true;
        }

        if(slots.test(block->slot_idx() + dir[1] * 10 + dir[0])) {
            return true;
        }
    }

    return false;
}

bool Piece::check_colission_rotate(const std::bitset<240>& slots, float angle) {
    if(type == 0) {
        return true;
    }

    const glm::mat2 rot(std::cos(angle), -std::sin(angle),
                        std::sin(angle),  std::cos(angle));
    const glm::vec2 center = this->blocks.front().get_pos();

    for(auto block = this->blocks.begin(); block != this->blocks.end(); block++) {

        const glm::vec2 newpos = rot * (block->get_pos() - center) + center;

        if(newpos[0] < 0.0f || newpos[0] > 9 || newpos[1] < 0) {
            return true;
        }

        if(slots.test(newpos[1] * 10 + newpos[0])) {
            return true;
        }
    }
    return false;
}

bool Piece::is_high() {
    for(auto block = this->blocks.begin(); block != this->blocks.end(); block++) {
        if(block->get_pos()[1] > 21) {
            return true;
        }
    }

    return false;
}
