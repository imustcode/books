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
#include "Particle.h"
#include "Arrow.h"

const float ARROW_WIDTH         = 0.1f;
const float ARROW_DEPTH         = 0.05f;
const float AMP_TO_ARROW_HEIGHT = 2.0f;

class Particle::Impl
{
public:
    float mass; 
    float freq;
    float amp;
    float phase;
    float spin;
    float charge;

    Arrow * arrow;
};

Particle::Particle( Entity * parent, World * world, 
                    float x, float y, float z, 
                    int   texid,
                    float mass, 
                    float freq, 
                    float amp,
                    float phase,
                    float spin,
                    float charge )
{
    impl = new Particle::Impl;

    impl->mass   = mass;
    impl->freq   = freq;
    impl->amp    = amp;
    impl->phase  = phase;
    impl->spin   = spin;
    impl->charge = charge;

    float w = ARROW_WIDTH;
    float h = amp * AMP_TO_ARROW_HEIGHT;
    float d = ARROW_DEPTH;
    impl->arrow = new Arrow( parent, world, x, y, z, w, h, d, phase, texid );
}

Particle::~Particle()
{
    delete impl->arrow;
    delete impl;
}

float Particle::mass_get( void )
{
    return impl->mass;
}

float Particle::freq_get( void )
{
    return impl->freq;
}

float Particle::amp_get( void )
{
    return impl->amp;
}

void Particle::amp_set( float amp )
{
    // scale arrow height first
    //
    float w, h, d;
    impl->arrow->whd_get( &w, &h, &d );
    h *= amp / impl->amp;
    impl->arrow->whd_set( w, h, d );

    impl->amp = amp;
}

float Particle::phase_get( void )
{
    return impl->phase;
}

void Particle::phase_set( float phase )
{
    impl->phase = phase;
    impl->arrow->rotation_set( phase );
}

float Particle::spin_get( void )
{
    return impl->spin;
}

float Particle::charge_get( void )
{
    return impl->charge;
}
