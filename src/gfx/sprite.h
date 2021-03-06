/**************************************************************************
 *   sprite.h  --  This file is part of Netris.                           *
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

#ifndef _SPRITE_H
#define _SPRITE_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Sprite {
private:
    GLuint vao;
    GLuint vbo[3];

public:
    Sprite(float* uv);

    void draw() const;

private:
};

#endif //_SPRITE_H
