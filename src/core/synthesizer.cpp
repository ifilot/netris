/**************************************************************************
 *   synthesizer.cpp  --  This file is part of Netris.                    *
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

#include "synthesizer.h"

Synthesizer::Synthesizer() {
    alutInit(NULL, 0);
    alGetError();

    this->load_sound_data("music/theme.wav");
    this->load_sound_data("effects/block_hit.wav");

    this->set_listener();

    // set an exit procedure
    atexit(Synthesizer::kill_synthesizer);
}

void Synthesizer::load_sound_data(const std::string& filename) {
    // Load wav data into a buffer.

    this->buffers.push_back(0);
    this->buffers.back() = alutCreateBufferFromFile((AssetManager::get().get_root_directory() + "assets/wav/" + filename).c_str());
    if(alGetError() != AL_NO_ERROR) {
        std::cerr << "An error was detecting loading the sound file" << std::endl;
        return;
    }

    // Bind the buffer with the source.

    this->sources.push_back(0);
    alGenSources(1, &this->sources.back());

    if(alGetError() != AL_NO_ERROR) {
        std::cerr << "An error was detecting loading the sound source" << std::endl;
        return;
    }

    ALfloat source_position[] = { 0.0, 0.0, 0.0 };
    ALfloat source_velocity[] = { 0.0, 0.0, 0.0 };

    alSourcei (this->sources.back(), AL_BUFFER,   this->buffers.back()   );
    alSourcef (this->sources.back(), AL_PITCH,    1.0      );
    alSourcef (this->sources.back(), AL_GAIN,     1.0      );
    alSourcefv(this->sources.back(), AL_POSITION, source_position);
    alSourcefv(this->sources.back(), AL_VELOCITY, source_velocity);
    alSourcei (this->sources.back(), AL_LOOPING,  false     );

    // Do another error check and return.

    if(alGetError() == AL_NO_ERROR) {
        return;
    }

    return;
}

void Synthesizer::set_listener() {
    // Position of the Listener.
    ALfloat listener_position[] = { 0.0, 0.0, 0.0 };

    // Velocity of the Listener.
    ALfloat listener_velocity[] = { 0.0, 0.0, 0.0 };

    // Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
    // Also note that these should be units of '1'.
    ALfloat listener_orientation[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

    alListenerfv(AL_POSITION,    listener_position);
    alListenerfv(AL_VELOCITY,    listener_velocity);
    alListenerfv(AL_ORIENTATION, listener_orientation);
}

void Synthesizer::delete_buffers_and_sources() {
    for(auto buffer = this->buffers.begin(); buffer != this->buffers.end(); buffer++) {
        alDeleteBuffers(1, &(*buffer));
    }

    for(auto source = this->sources.begin(); source != this->sources.end(); source++) {
        alDeleteSources(1, &(*source));
    }

    this->buffers.clear();
    this->sources.clear();
}

void Synthesizer::kill_synthesizer() {
    Synthesizer::get().delete_buffers_and_sources();
    alutExit();
}

Synthesizer::~Synthesizer() {
    this->delete_buffers_and_sources();
    alutExit();
}
