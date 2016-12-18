/**************************************************************************
 *   frame.cpp  --  This file is part of Netris.                          *
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

#include "frame.h"

Frame::Frame() {
    this->tiles.push_back(Block(glm::vec2(-1.f,-1.f), SpriteManager::get().get_sprite_pointer(7)));
    this->tiles.push_back(Block(glm::vec2(10.f,-1.f), SpriteManager::get().get_sprite_pointer(9)));

    for(unsigned int i=1; i<11; i++) {
        this->tiles.push_back(Block(glm::vec2((float)(i - 1),-1.f), SpriteManager::get().get_sprite_pointer(8)));
    }

    for(unsigned int i=0; i<23; i++) {
        this->tiles.push_back(Block(glm::vec2(-1.f, (float)i), SpriteManager::get().get_sprite_pointer(10)));
    }

    for(unsigned int i=0; i<23; i++) {
        this->tiles.push_back(Block(glm::vec2(10.f, (float)i), SpriteManager::get().get_sprite_pointer(12)));
    }

    for(unsigned int i=11; i<40; i++) {
        for(unsigned int j=0; j<23; j++) {
            this->tiles.push_back(Block(glm::vec2((float)i, (float)j - 1.0f), SpriteManager::get().get_sprite_pointer(11)));
        }
    }
}

void Frame::draw() {
    glActiveTexture(GL_TEXTURE1);
    SpriteManager::get().bind_sprites(1);

    for(auto tile = this->tiles.begin(); tile != this->tiles.end(); tile++) {
        tile->draw();
    }

    SpriteManager::get().unbind_sprites();
}
