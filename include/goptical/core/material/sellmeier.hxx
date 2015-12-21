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

#ifndef GOPTICAL_MATERIAL_SELLMEIER_HXX_
#define GOPTICAL_MATERIAL_SELLMEIER_HXX_

#include <cassert>

#include "goptical/core/material/dielectric.hxx"

namespace _goptical {

  namespace material {

    void Sellmeier::set_contant_term(double A)
    {
      _constant = A;
    }

    void Sellmeier::set_term(unsigned int term, double K, double L)
    {
      term *= 2;

      assert(term + 1 < _coeff.size());

      _coeff[term] = K;
      _coeff[term + 1] = L;
    }

  }

}

#endif

