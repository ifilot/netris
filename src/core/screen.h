/**************************************************************************
 *   screen.h  --  This file is part of Netris.                           *
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

#ifndef _SCREEN_H
#define _SCREEN_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

/**
 * @class Screen class
 *
 * @brief class handling screen settings
 *
 */
class Screen {
private:
    unsigned int width;       //!< width of the screen
    unsigned int height;      //!< height of the screen
    bool flag_focus;          //!< whether screen is in focus

public:
    /**
     * @fn          get
     *
     * @brief       get a reference to the screen
     *
     * @return      reference to the screen object (singleton pattern)
     */
    static Screen& get() {
        static Screen screen_instance;
        return screen_instance;
    }

    inline unsigned int get_width() const {
        return this->width;
    }

    inline unsigned int get_height() const {
        return this->height;
    }

    inline void set_width(unsigned int _width) {
        this->width = _width;
    }

    inline void set_height(unsigned int _height) {
        this->height = _height;
    }

    inline bool in_focus() const {
        return this->flag_focus;
    }

    inline void set_focus(bool focus) {
        this->flag_focus = focus;
    }

private:
    Screen();

    // Singleton pattern
    Screen(Screen const&)          = delete;
    void operator=(Screen const&)  = delete;
};

#endif //_SCREEN_H
