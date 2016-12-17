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

#ifndef _UTIL_PNG_H
#define _UTIL_PNG_H

#include <fstream>
#include <iostream>
#include <vector>
#include <png.h>

namespace PNG {

    void write_image_buffer_to_png(const std::string& filename, const std::vector<uint8_t>& buffer, unsigned int width, unsigned int height, unsigned int col);
    void load_image_buffer_from_png(const std::string& filename, std::vector<uint8_t>& buffer, png_uint_32* width, png_uint_32* height, int* col, int* bit_depth);

    void read_file_callback(png_structp png_ptr, png_bytep out, png_size_t count);
    void write_file_callback(png_structp png_ptr, png_bytep data, png_size_t count);
}

#endif //_UTIL_PNG_H
