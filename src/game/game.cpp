/**************************************************************************
 *   game.cpp  --  This file is part of Netris.                           *
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

#include "game.h"

Game::Game() :
    rng_distribution(0,6) {
    this->piece = new Piece(0);
    this->blocks.resize(240);

    //this->update_slots();

    // load synthesizer for sound effects
    Synthesizer::get().play(0);

    // load fonts
    FontWriter::get().add_font("./assets/fonts/retro.ttf",
                                16,              // font size
                                0.43f, 0.25f,    // sdf settings
                                50,              // start char
                                73               // number of chars
                                );
}

void Game::draw() {
    glActiveTexture(GL_TEXTURE1);
    SpriteManager::get().bind_sprites(0);

    for(auto block = this->blocks.begin(); block != this->blocks.end(); block++) {
        if(block->get()) {
            block->get()->draw();
        }
    }

    if(piece != NULL) {
        this->piece->draw();
    }

    SpriteManager::get().unbind_sprites();

    // draw font
    this->draw_text();
}

void Game::update() {
    // perform collision detection
    if(this->piece->check_colission_translate(this->slots, glm::vec2(0,-1))) {
        if(this->piece->is_high()) {
            std::cout << "Game over" << std::endl;
            exit(0);
            return;
        }
        // play collision sound
        Synthesizer::get().play(1);
        this->launch_new_piece();
        return;
    }

    // if no collision update piece
    this->piece->translate(glm::vec2(0,-1));
}

void Game::update_slots() {
    this->slots.reset();

    for(unsigned int i=0; i<this->blocks.size(); i++) {
        if(blocks[i].get() != nullptr) {
            this->slots.set(i);
        }
    }
}

void Game::launch_new_piece() {
    // store current piece in blocks
    for(auto block = this->piece->get_blocks().begin(); block != this->piece->get_blocks().end(); block++) {
        this->blocks[block->slot_idx()] = std::unique_ptr<Block>(new Block(*block));
        this->slots.set(block->slot_idx());
    }

    delete this->piece;

    // check for lines
    this->check_lines();

    // make new piece
    int type = this->rng_distribution(this->rng_engine);
    this->piece = new Piece(type);
}

void Game::handle_key_down(int key, int scancode, int action, int mods) {
    if(key == 'A' && (action == GLFW_REPEAT || action == GLFW_PRESS) && mods == 0) {
        this->translate_piece(glm::vec2(-1,0));
        return;
    }

    if(key == 'D' && (action == GLFW_REPEAT || action == GLFW_PRESS) && mods == 0) {
        this->translate_piece(glm::vec2(1,0));
        return;
    }

    if(key == 'S' && (action == GLFW_REPEAT || action == GLFW_PRESS) && mods == 0) {
        this->translate_piece(glm::vec2(0,-1));
        return;
    }

    if(key == 'Q' && (action == GLFW_REPEAT || action == GLFW_PRESS) && mods == 0) {
        this->rotate_piece(M_PI / 2.0f);
        return;
    }

    if(key == 'E' && (action == GLFW_REPEAT || action == GLFW_PRESS) && mods == 0) {
        this->rotate_piece(-M_PI / 2.0f);
        return;
    }
}

void Game::translate_piece(const glm::vec2& dir) {
    if(this->piece->check_colission_translate(this->slots, dir)) {
        // if direction is down, trigger update
        if(dir == glm::vec2(0,-1)) {
            this->update();
        }
        return;
    }

    // if no collision update piece
    this->piece->translate(dir);
}

void Game::rotate_piece(float angle) {
    if(this->piece->check_colission_rotate(this->slots, angle)) {
        return;
    }
    // if no collision update piece
    this->piece->rotate(angle);
}

void Game::check_lines() {
    std::vector<unsigned int> lines_to_remove;

    for(unsigned int i=0; i<22; i++) {
        for(unsigned int j=0; j<10; j++) {
            if(!this->slots.test(i * 10 + j)) {
                break;
            }

            if(j == 9) { // remove line
                lines_to_remove.push_back(i);
            }
        }
    }

    if(lines_to_remove.size() == 0) {
        return;
    }

    for(auto line_nr = lines_to_remove.begin(); line_nr != lines_to_remove.end(); line_nr++) {
        for(unsigned int j=0; j<10; j++) {
            Block* ptr = this->blocks[(*line_nr) * 10 + j].release();
            delete ptr;
        }
    }

    for(unsigned int i=(lines_to_remove.back()+1) * 10; i<this->blocks.size(); i++) {
        if(this->blocks[i].get()) {
            this->blocks[i].get()->translate(0, -(float)lines_to_remove.size());
            std::swap(blocks[i], blocks[i - lines_to_remove.size() * 10]);
        }
    }

    this->update_slots();
}

void Game::draw_text() {
    FontWriter::get().write_text(0, 300.0f, 300.0f, 0.5f, glm::vec3(1,1,1), "Test");
}
