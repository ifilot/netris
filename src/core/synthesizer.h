/**************************************************************************
 *   synthesizer.h  --  This file is part of Netris.                      *
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

#ifndef _SYNTHESIZER_H
#define _SYNTHESIZER_H

#include "core/asset_manager.h"

#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <cstring>
#include <string>
#include <vector>

class Synthesizer {
private:
    ALCdevice* device;
    std::vector<ALuint> buffers;
    std::vector<ALuint> sources;

public:
    static Synthesizer& get() {
        static Synthesizer synthesizer_instance;
        return synthesizer_instance;
    }

    static void kill_synthesizer();

    inline void play(unsigned int sound_id) {
        alSourcePlay(this->sources[sound_id]);
    }

    ~Synthesizer();

private:
    Synthesizer();

    void load_sound_data(const std::string& filename);

    void set_listener();

    void delete_buffers_and_sources();

    void load_mp3(const std::string filename);

    // Singleton pattern
    Synthesizer(Synthesizer const&) = delete;
    void operator=(Synthesizer const&)  = delete;
};

#endif //_SYNTHESIZER_H
