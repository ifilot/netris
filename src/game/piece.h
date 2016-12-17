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

#ifndef _PIECE_H
#define _PIECE_H

#include <bitset>

#include "game/block.h"
#include "gfx/sprite_manager.h"

class Piece {
private:
    std::vector<Block> blocks;
    unsigned int type;

public:
    Piece(unsigned int _type);

    void draw();

    void add_block(float x, float y, unsigned int bt);

    void translate(const glm::vec2& dir);

    void rotate(float angle);

    bool check_colission_translate(const std::bitset<240>& slots, const glm::vec2& dir);

    bool check_colission_rotate(const std::bitset<240>& slots, float angle);

    bool is_high();

    inline const std::vector<Block>& get_blocks() const {
        return this->blocks;
    }

private:
};

#endif //_PIECE_H
