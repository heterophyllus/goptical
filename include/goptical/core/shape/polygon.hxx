/*

      This file is part of the <goptical/core Core library.
  
      The <goptical/core library is free software; you can redistribute it
      and/or modify it under the terms of the GNU General Public
      License as published by the Free Software Foundation; either
      version 3 of the License, or (at your option) any later version.
  
      The <goptical/core library is distributed in the hope that it will be
      useful, but WITHOUT ANY WARRANTY; without even the implied
      warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
      See the GNU General Public License for more details.
  
      You should have received a copy of the GNU General Public
      License along with the <goptical/core library; if not, write to the
      Free Software Foundation, Inc., 59 Temple Place, Suite 330,
      Boston, MA 02111-1307 USA
  
      Copyright (C) 2010-2011 Free Software Foundation, Inc
      Author: Alexandre Becoulet

*/

#ifndef GOPTICAL_SHAPE_POLYGON_HXX_
#define GOPTICAL_SHAPE_POLYGON_HXX_

#include "base.hxx"

namespace _goptical {

  namespace shape {

    unsigned int Polygon::get_vertices_count() const
    {
      return _vertices.size();
    }

    const math::Vector2 & Polygon::get_vertex(unsigned int id)
    {
      assert(id < _vertices.size());
      return _vertices[id];
    }

    unsigned int Polygon::get_contour_count() const
    {
      return 1;
    }


  }

}

#endif

