/**************************************************************************
 *   frame.h  --  This file is part of Netris.                            *
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

#ifndef _FRAME_H
#define _FRAME_H

#include "gfx/sprite_manager.h"
#include "game/block.h"

class Frame {
private:
    std::vector<Block> tiles;

public:

    static Frame& get() {
        static Frame frame_instance;
        return frame_instance;
    }

    void draw();

private:
    Frame();

    // Singleton pattern
    Frame(Frame const&)          = delete;
    void operator=(Frame const&)  = delete;
};

#endif //_FRAME_H
