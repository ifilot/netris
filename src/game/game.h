/**************************************************************************
 *   game.h  --  This file is part of Netris.                             *
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

#ifndef _GAME_H
#define _GAME_H

#include <bitset>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "gfx/sprite_manager.h"
#include "game/block.h"
#include "game/piece.h"

class Game {
private:
    std::vector<std::unique_ptr<Block>> blocks;
    Piece* piece;
    std::bitset<240> slots;
    std::vector<std::vector<Block>::iterator> block_indices;
    boost::random::mt19937 rng;

public:
    static Game& get() {
        static Game game_instance;
        return game_instance;
    }

    void draw();

    void update();

    void handle_key_down(int key, int scancode, int action, int mods);

private:
    Game();

    void update_slots();

    void launch_new_piece();

    void translate_piece(const glm::vec2& dir);

    void rotate_piece(float angle);

    void check_lines();

    // Singleton pattern
    Game(Game const&)          = delete;
    void operator=(Game const&)  = delete;
};

#endif //_GAME_H
