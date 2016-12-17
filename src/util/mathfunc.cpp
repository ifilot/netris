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

#include "mathfunc.h"

/**
 * @brief       calculate point of ray-plane intersection
 *
 * @param       ray origin vector
 * @param       ray direction vector
 * @param       plane origin vector
 * @param       plane normal vector
 * @return      point in plane where ray intersects plane
 */
glm::vec3 calculate_ray_plane_intersection(const glm::vec3& ray_origin,
                                           const glm::vec3& ray_vector,
                                           const glm::vec3& plane_origin,
                                           const glm::vec3& plane_normal) {

    float dotprod = glm::dot(ray_vector, plane_normal);

    if(fabs(dotprod) < 0.001) {
        return glm::vec3(-1, -1, -1);
    } else {
        float t = glm::dot(plane_origin - ray_origin, plane_normal) / dotprod;
        return ray_origin + t * ray_vector;
    }
}

bool vec4less_radial(const glm::vec4 &lhs, const glm::vec4 &rhs) {
    if(lhs.x > 0 && rhs.x < 0) {
        return true;
    }

    if(lhs.x < 0 && rhs.x > 0) {
        return false;
    }

    if(lhs.x == 0 && rhs.x == 0) {
        if(lhs.y >= 0 || rhs.y >= 0) {
            return lhs.y > rhs.y;
        }
        return rhs.y > lhs.y;
    }

    float det = (lhs.x * rhs.y) - (rhs.x * lhs.y);

    if(det < 0.0f) {
        return true;
    }

    if(det > 0.0f) {
        return false;
    }

    float d1 = (lhs.x) * (lhs.x) + (lhs.y) * (lhs.y);
    float d2 = (rhs.x) * (rhs.x) + (rhs.y) * (rhs.y);
    return d1 > d2;
}

glm::mat4 get_rotation_matrix(const glm::vec3& v1, const glm::vec3& v2) {
    const float dotprod = glm::dot(v1, v2);

    // check for parallel or anti-parallel configurations
    glm::mat4 rot(1.0f);
    glm::vec3 axis_angle;
    if(fabs(dotprod) > 0.999f) { // axes are parallel or anti-parallel
        if(dotprod < -0.5f) { // anti-parallel --> rotate system by 180 degrees
            const float angle = -(float)M_PI;
            axis_angle = glm::vec3(0, 1, 0);
            rot = glm::rotate(glm::mat4(1.0), angle, axis_angle);
        } // else parallel --> do nothing
    } else { // neither parallel or anti-parallel --> normal behavior
        const float angle = std::acos(dotprod);
        axis_angle = glm::normalize(glm::cross(v1, v2));
        rot = glm::rotate(glm::mat4(1.0), angle, axis_angle);
    }

    return rot;
}

glm::mat4 get_rotation_matrix_from_view(const glm::mat4& view) {
    glm::mat4 mrot = glm::transpose(view);
    mrot[0][3] = 0.0f;
    mrot[1][3] = 0.0f;
    mrot[2][3] = 0.0f;
    mrot[3][3] = 1.0f;
    mrot[3][0] = 0.0f;
    mrot[3][1] = 0.0f;
    mrot[3][2] = 0.0f;

    return mrot;
}
