/**************************************************************************
 *   netris.cpp  --  This file is part of Netris.                         *
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

#include "core/asset_manager.h"
#include "core/display.h"
#include "core/screen.h"
#include "core/settings.h"

int main(int argc, char* argv[]) {

    // AssetManager needs to be loaded
    AssetManager::get().init(argv[0]);

    // load screen settings
    const unsigned int width = Settings::get().get_float_from_keyword("settings.screen.resolution_x");
    const unsigned int height = Settings::get().get_float_from_keyword("settings.screen.resolution_y");
    Screen::get().set_resolution_x(width);
    Screen::get().set_resolution_y(height);

    Screen::get().set_width(width);
    Screen::get().set_height(height);

    Visualizer::get().run(argc, argv);

    return 0;
}
