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

#ifndef _LIGHT_H
#define _LIGHT_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "camera.h"

class Light {
private:
    glm::vec3 position;

public:
    static Light& get() {
        static Light light_instance;
        return light_instance;
    }

    inline const glm::vec3& get_position() const {
        return this->position;
    }

    void update();

private:
    Light();

    Light(Light const&)          = delete;
    void operator=(Light const&)  = delete;
};

#endif //_LIGHT_H
