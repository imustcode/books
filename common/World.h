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

// The Universe is composed of multiple Worlds, but only one is displayed at any given time.  
//
// An Entity may belong to different Worlds and will typically maintain different geometry for each.
// For example, an Entity may have an outer world and an inner world.
//
#ifndef _World_h
#define _World_h

#include "Config.h"

// Common directions
//
enum {
    DIR_X_POS   = 0,
    DIR_X_NEG   = 1,
    DIR_Y_POS   = 2,
    DIR_Y_NEG   = 3,
    DIR_Z_NEG   = 4,
    DIR_Z_POS   = 5
};

// Entities maintain arrays of Vertex and Triangle and tell World when they change
//
class Vertex
{
public:
    float          position[3];  // absolute location within world
    float          normal[3];    // normal unit vector
    int            texid;        // texture array index
    float          texcoord[2];  // texture 2D coords
};

class Triangle
{
public:
    unsigned short v0;           // vertex0 index
    unsigned short v1;           // vertex1 index
    unsigned short v2;           // vertex2 index
};

class Sys;

class World 
{
public:
    World( Config * config, Sys * sys, float w, float h, float d );
    ~World();

    // CONFIG
    //
    Config * config_get( void );

    // CAMERA VIEW
    //
    void view_get( float * fov_y, float * near_z, float * far_z,
                   float eye[], float view[], float up[] );
    void view_set( float fov_y, float near_z, float far_z,
                   float eye[], float view[], float up[] );

    // GEOMETRY 
    //
    // NOTE: Vertex and Triangle are not object classes because we want to be able to 
    //       download them into the GPU without modification.  This is a performance
    //       consideration.
    //
    //       Geom is not an object class for the same reason.
    //       However, Geom is hidden (known only between World.cpp and Sys.h).
    //       Instead, users of this module get back an opaque geometry handle (an int).
    //
    // geom_add() returns an opaque handle for referring to the added geometry in subsequent calls.
    // The vertex and triangle arrays must continue to exist after this call.  
    // They will get copied later, possibly multiple times if changes occur.
    // 
    // geom_changed() is called to note that the vertex data has changed, but the number and order 
    // of the vertices and triangles hasn't.  
    //
    // geom_remove() is called to remove the geometry.  Currently, if you want to change the number
    // or order of vertexes or triangles, you must first remove the old geometry using this function.
    // This is also called when an Entity is deleted.
    //
    int  geom_add( Vertex * vertex, int vertex_cnt, Triangle * triangle, int triangle_cnt );
    bool geom_visible_get( int hdl );
    void geom_visible_set( int hdl, bool visible );
    void geom_changed( int hdl );
    void geom_remove( int hdl );

    // OVERLAY TEXT
    //
    void text2d_set( int x, int y, int h, int rgb, int str_cnt, const char * str[] );

    // VECTOR MATH
    //
    static float vec_length( const float A[], int dims = 3 );
    static void  vec_assign( float R[], const float A[], int dims = 3 );
    static void  vec_normalize( float R[], const float A[], int dims = 3 );
    static void  vec_add( float R[], const float A[], const float B[], int dims = 3 );
    static void  vec_sub( float R[], const float A[], const float B[], int dims = 3 );
    static void  vec_scale( float R[], const float A[], const float B[], int dims = 3 );
    static void  vec_scale( float R[], const float A[], const float c, int dims = 3 );
    static void  vec_cross( float R[], const float A[], const float B[], int dims = 3 );

private:
    class Impl;
    Impl * impl;

    friend class Sys;

    // Sys calls this to render the next frame
    //
    void frame_render( float wall_clock_ms );

    // This is called at the beginning of each frame drawn
    //
    virtual void frame_begin( float wall_clock_ms );

    // Sys calls these in response to user input and other things
    //
    void resize_event( double w, double h );
    void motion_event( double x, double y );
    void key_event(    int key,    int action, int modifiers );
    void button_event( int button, int action, int modifiers );
    void scroll_event( int scroll, int action, int modifiers );
};

#endif
