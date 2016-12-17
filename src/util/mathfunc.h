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

#ifndef _VEEVEE_MATH_H
#define _VEEVEE_MATH_H

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Sparse>

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static const double kcal_per_mol_to_ev = 0.0433634;

/**
 * @fn square
 * @brief Convenience function that returns the square of a double
 *
 * @param c  Number to be squared
 *
 * @return square
 */
inline double square(double c) {
    return c * c;
}

/**
 * @fn cube
 * @brief Convenience function that returns the cube of a double
 *
 * @param c  Number to be cubed
 *
 * @return cube
 */
inline double cube(double c) {
    return c * c * c;
}

inline double deg2rad(double deg) {
    return deg / 360.0f * 2.0f * M_PI;
}

typedef Eigen::Matrix<double, 3, 1> Vector3;
typedef Eigen::Matrix<double, 3, 3> Matrix3;

typedef Eigen::Matrix<double, 4, 4> Matrix4;
typedef Eigen::Matrix<double, 4, 1> Vector4;

typedef Eigen::Matrix<double, Eigen::Dynamic, 1> VectorXf;

typedef Eigen::Matrix<double, Eigen::Dynamic, 3> MatrixX3f;
typedef Eigen::Matrix<double, Eigen::Dynamic, 4> MatrixX4f;

typedef Eigen::Matrix<double, 3, Eigen::Dynamic> Matrix3Xf;
typedef Eigen::Matrix<double, 4, Eigen::Dynamic> Matrix4Xf;

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXXf;

double get_angle(const Vector3& d1, const Vector3& d2);

double get_dihedral(const Vector3& v1, const Vector3& v2, const Vector3& v3);

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename T>
T clamp(const T& n, const T& lower, const T& upper) {
  return std::max(lower, std::min(n, upper));
}

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
                                           const glm::vec3& plane_normal);

bool vec4less_radial(const glm::vec4 &lhs, const glm::vec4 &rhs);

glm::mat4 get_rotation_matrix(const glm::vec3& v1, const glm::vec3& v2);

glm::mat4 get_rotation_matrix_from_view(const glm::mat4& view);

#endif //_VEEVEE_MATH_H
