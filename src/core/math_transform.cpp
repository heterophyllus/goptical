/*

      This file is part of the Goptical Core library.

      The Goptical library is free software; you can redistribute it
      and/or modify it under the terms of the GNU General Public
      License as published by the Free Software Foundation; either
      version 3 of the License, or (at your option) any later version.

      The Goptical library is distributed in the hope that it will be
      useful, but WITHOUT ANY WARRANTY; without even the implied
      warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
      See the GNU General Public License for more details.

      You should have received a copy of the GNU General Public
      License along with the Goptical library; if not, write to the
      Free Software Foundation, Inc., 59 Temple Place, Suite 330,
      Boston, MA 02111-1307 USA

      Copyright (C) 2010-2011 Free Software Foundation, Inc
      Author: Alexandre Becoulet

*/

#include <cassert>

#include <goptical/core/math/transform.hpp>

namespace goptical
{

namespace math
{

void
get_rotation_matrix (Matrix<2> &r, unsigned int axis, double a)
{
  assert (axis == 0);

  /*
   * See https://mathworld.wolfram.com/RotationMatrix.html
   * the matrix that rotates a given vector v_0 by a counterclockwise angle
   * theta in a fixed coordinate system.
   */
  r.value (0, 0) = cos (a);
  r.value (0, 1) = sin (-a);
  r.value (1, 0) = sin (a);
  r.value (1, 1) = cos (a);
}

void
get_rotation_matrix (Matrix<3> &r, unsigned int axis, double a)
{
  assert (axis < 3);

  /*
   * Note on convention used below.
   *
   * See https://mathworld.wolfram.com/RotationMatrix.html
   * coordinate system rotations of the x-, y-, and z-axes in a
   * counterclockwise direction when looking towards the origin give the
   * matrices.
   *
   * This appears to correspond to xyz convention described in appendix A,
   * Classical Mechanics, Goldstein, 3rd Ed. 'It appears that most U.S. and
   * British aerodynamicists and pilots prefer the sequence in which the first
   * rotation is the yaw angle (phi) about a z-axis, the second is the pitch
   * angle (theta) about an intermediary y-axis, and the third is a bank or
   * roll angle (psi) about the final x-axis.'
   *
   */
  switch (axis)
    {
    case 0:
      // rotation around the X axis
      r.value (0, 0) = 1;
      r.value (0, 1) = 0;
      r.value (0, 2) = 0;
      r.value (1, 0) = 0;
      r.value (1, 1) = cos (a);
      r.value (1, 2) = sin (a);
      r.value (2, 0) = 0;
      r.value (2, 1) = -sin (a);
      r.value (2, 2) = cos (a);
      return;

    case 1:
      // rotation around the Y axis
      r.value (0, 0) = cos (a);
      r.value (0, 1) = 0;
      r.value (0, 2) = -sin (a);
      r.value (1, 0) = 0;
      r.value (1, 1) = 1;
      r.value (1, 2) = 0;
      r.value (2, 0) = sin (a);
      r.value (2, 1) = 0;
      r.value (2, 2) = cos (a);
      return;

    case 2:
      // rotation around the Z axis
      r.value (0, 0) = cos (a);
      r.value (0, 1) = sin (a);
      r.value (0, 2) = 0;
      r.value (1, 0) = -sin (a);
      r.value (1, 1) = cos (a);
      r.value (1, 2) = 0;
      r.value (2, 0) = 0;
      r.value (2, 1) = 0;
      r.value (2, 2) = 1;
      return;
    }
}

}

}
