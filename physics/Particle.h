// Copyright (c) 2014 Robert A. Alfieri
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 

// Particle - QED-style particle (amplitude, phase)
//
#ifndef _Particle_h
#define _Particle_h

#include "Entity.h"

// constants
//
static const float PI		    = 3.14159265358979323846;       // I think you know what this is :-)
static const float PI_DIV2          = PI / 2.0;
static const float PI_DIV4          = PI / 4.0;
static const float PI_DIV8          = PI / 8.0;
static const float PI_MUL2          = PI * 2.0;
static const float C                = 299792458;                    // exact speed of light in m/s
static const float C_POW2           = C * C;                        // c-squared
static const float H                = 6.62606957e-34;               // Planck's constant in J-sec
static const float HBAR             = H / PI_MUL2;                  // reduced Planck's constant (Dirac constant)
static const float ECHARGE          = 1.602176585e-19;              // elementary charge in Coulombs (C)

class Particle 
{
public:
    Particle( Entity * parent, World * world, 
              float x, float y, float z,        // m
              int   texid,                      // texture id
              float mass,                       // kg
              float freq,                       // cyc/sec
              float amp,                        // probability amplitude (length of arrow)
              float phase  = 0.0,               // phase of arrow about its center (0 .. 2*PI)
              float spin   = 0.0,               // spin  of arrow about its axis   (0 .. 2*PI)
              float charge = 0.0 );             // Coulombs (C)
    ~Particle();

    // basic field methods 
    //
    float       mass_get( void );
    float       freq_get( void );

    float       amp_get( void );
    void        amp_set( float amp );

    float       phase_get( void );
    void        phase_set( float phase );

    float       spin_get( void );

    float       charge_get( void );

private:
    class Impl;
    Impl *impl;
};

#endif
