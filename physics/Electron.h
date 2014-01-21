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
#ifndef _Electron_h
#define _Electron_h

#include "Particle.h"
#include "math.h"

// constants
//
const float ELECTRON_MASS         = 9.10938291e-31;        // kg
const float ELECTRON_CHARGE       = -ECHARGE;              // C
const float ELECTRON_UB           = (ECHARGE * HBAR) / (2.0 * ELECTRON_MASS);  // Bohr magneton
const float ELECTRON_SPIN_G       = -2.00231930436153;     // spin g-factor
const float ELECTRON_SPIN_QUANTUM = 0.5;                   // spin quantum number
const float ELECTRON_SPIN_ANG_MOM = HBAR * sqrt( ELECTRON_SPIN_QUANTUM*( ELECTRON_SPIN_QUANTUM + 1.0 ) );  // spin ang momentum
const float ELECTRON_SPIN_MOMENT  = ELECTRON_SPIN_G * ELECTRON_UB / HBAR * ELECTRON_SPIN_ANG_MOM;          // spin magnetic moment

class Electron : public Particle
{
public:
    Electron( Entity * parent, World * world, 
              float x, float y, float z,        
              int   texid,                      // texture id
              float freq,                       // frequency, so energy = freq * H
              float amp,                        // scalar amplitude, 0 .. 1 
              float phase );                    // 0 .. 2*PI
};

#endif
