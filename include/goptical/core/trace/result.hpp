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


#ifndef GOPTICAL_TRACE_RESULT_HH_
#define GOPTICAL_TRACE_RESULT_HH_

#include <set>
#include <deque>
#include <memory>

#include "goptical/core/common.hpp"

#include "goptical/core/sys/element.hpp"
#include "goptical/core/sys/surface.hpp"
#include "goptical/core/trace/ray.hpp"

namespace goptical {

  namespace trace {

    /**
       @short Store light propagation result
       @header <goptical/core/trace/Result
       @module {Core}
       @main

       This class encapsulates rays data propagation result.

       It must be properly configured before light propagation as
       needed by the analysis currently being performed. All
       requested light propagation informations will be store for
       further processing.

       All @ref Ray object are allocated by this class. It is able
       to remember which element intercepted and generated each ray.
    */
    class Result
    {
      friend class Tracer;

    public:
      typedef std::vector<const sys::Source *> sources_t;

      /** Crate a new empty result object */
      Result();

      ~Result();

      /** Get the list of rays striking a given surface */
      inline const rays_queue_t & get_intercepted(const sys::Surface &s) const;
      /** Get the list of rays generated by a given element */
      inline const rays_queue_t & get_generated(const sys::Element &s) const;

      /** Get list of sources used for ray tracing */
      inline const trace::Result::sources_t & get_source_list() const;

      /** Get window which include all ray intercepted on a surface */
      math::VectorPair3 get_intercepted_window(const sys::Surface &s) const;
      /** Get center of window */
      math::Vector3 get_intercepted_center(const sys::Surface &s) const;
      /** Get centroid of all ray intercepted on a surface */
      math::Vector3 get_intercepted_centroid(const sys::Surface &s) const;

      std::vector<std::vector<double> > pixelate(const sys::Surface &s) const;

      /** Clear all result data */
      void clear();

      /** List of rays striking this surface must be saved when tracing rays */
      void set_intercepted_save_state(const sys::Element &e, bool enabled = true);
      /** Return true if generated rays must be saved for this element */
      bool get_intercepted_save_state(const sys::Element &e);

      /** List of rays generated by this element must be saved when tracing rays */
      void set_generated_save_state(const sys::Element &e, bool enabled = true);
      /** Return true if generated rays must be saved for this element */
      bool get_generated_save_state(const sys::Element &e);

      /** Set all save states to false */
      void clear_save_states();

      /** Get maximum intensity for a single ray FIXME */
      double get_max_ray_intensity() const;

      /* Get raytracing mode used FIXME */
      //  inline tracer::Mode get_mode() const;

      /** Allocate a new trace::Ray object from result */
      inline Ray & new_ray();

      /** Allocate a new trace::Ray object from result */
      inline Ray & new_ray(const light::Ray &r);

      /** Declare a new ray interception */
      inline void add_intercepted(const sys::Surface &s, Ray &ray);
      /** Declare a new ray generation */
      inline void add_generated(const sys::Element &s, Ray &ray);

      /** Declare ray wavelen used for tracing */
      inline void add_ray_wavelen(double wavelen);

      /** Get ray wavelen in use set */
      inline const std::set<double> & get_ray_wavelen_set() const;

      /** Get reference to tracer parameters used */
      inline const Params & get_params() const;

      /** Draw all tangential rays using specified renderer. Only rays
          which end up hitting the image plane are drawn when @tt
          hit_image is set. */
      void draw_2d(io::Renderer &r, bool hit_image = false,
                   const sys::Element *ref = 0) const;
      /** Draw all rays using specified renderer. Only rays
          which end up hitting the image plane are drawn when @tt
          hit_image is set.*/
      void draw_3d(io::Renderer &r, bool hit_image = false,
                   const sys::Element *ref = 0) const;

    private:
      void init(const sys::System *system);
      void init(const sys::Element &element);

      void prepare();

      struct element_result_s
      {
        std::shared_ptr<rays_queue_t> 
            _intercepted; // list of rays for each intercepted surfaces
        std::shared_ptr<rays_queue_t> 
            _generated; // list of rays for each generator surfaces
        bool _save_intercepted_list;
        bool _save_generated_list;
      };

      inline struct element_result_s & get_element_result(const sys::Element &e);
      inline const struct element_result_s & get_element_result(const sys::Element &e) const;

      vector_pool<Ray, 1024> _rays; // rays allocation pool
      std::vector<struct element_result_s> _elements;
      std::set<double>          _wavelengths;
      rays_queue_t              *_generated_queue;
      trace::Result::sources_t  _sources;
      unsigned int              _bounce_limit_count;
      const sys::System* _system; /* warning System must be valid ! */
      const trace::Params       *_params;
      //  tracer::Mode          _mode;
    };
    Result::element_result_s & Result::get_element_result(const sys::Element &e)
    {
      return _elements[e.id() - 1];
    }

    const Result::element_result_s & Result::get_element_result(const sys::Element &e) const
    {
      return _elements[e.id() - 1];
    }

    const trace::rays_queue_t & Result::get_intercepted(const sys::Surface &s) const
    {
      const struct element_result_s &er = get_element_result(s);

      if (!er._intercepted)
	throw Error("no such ray interception surface in ray trace result");

      return *er._intercepted;
    }

    const trace::rays_queue_t & Result::get_generated(const sys::Element &e) const
    {
      const struct element_result_s &er = get_element_result(e);

      if (!er._generated)
	throw Error("no such ray generator element in ray trace result");

      return *er._generated;
    }

    const trace::Result::sources_t & Result::get_source_list() const
    {
      return _sources;
    }

    void Result::add_intercepted(const sys::Surface &s, Ray &ray)
    {
      element_result_s &er = get_element_result(s);

      if (er._intercepted)
	er._intercepted->push_back(&ray);
    }

    void Result::add_generated(const sys::Element &s, Ray &ray)
    {
      element_result_s &er = get_element_result(s);

      if (er._generated)
	er._generated->push_back(&ray);
    }

    void Result::add_ray_wavelen(double wavelen)
    {
      _wavelengths.insert(wavelen);
    }

    const std::set<double> & Result::get_ray_wavelen_set() const
    {
      return _wavelengths;
    }

    trace::Ray & Result::new_ray()
    {
      trace::Ray        &r = _rays.create();

      if (_generated_queue)
	_generated_queue->push_back(&r);

      return r;
    }

    trace::Ray & Result::new_ray(const light::Ray &ray)
    {
      trace::Ray        &r = _rays.create(ray);

      if (_generated_queue)
	_generated_queue->push_back(&r);

      return r;
    }

    const Params & Result::get_params() const
    {
      assert(_params != 0);
      return *_params;
    }
  }
}

#endif

