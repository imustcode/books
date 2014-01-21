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

// Config - holds configuration information (can be per-world or universe)
//
#include "Config.h"
#include "Color.h"
#include "Sys.h"
#include "math.h"

Config::Config( int argc, const char * argv[] )
{
    this->win_name  = strdup( "FOS Demo" );
    this->win_w     = 1920; 
    this->win_h     = 1080;
    this->win_off_x = 100;
    this->win_off_y = 100;
    this->win_fullscreen = false;
    this->win_eye[0] = (25.0f + 9.0f*0.006f + 0.2f)/2.0;
    this->win_eye[1] = 0.776;
    this->win_eye[2] = 0.00f;
    this->win_view[0] = win_eye[0];
    this->win_view[1] = win_eye[1];
    this->win_view[2] = this->win_eye[2] - 0.50f;
    this->win_up[0]   = 0.0f;
    this->win_up[1]   = 1.0f;
    this->win_up[0]   = 0.0f;
    this->win_fov_y = 8.0f; 
    this->win_near_z = 0.01f;
    this->win_far_z = 40.0f;
    this->win_perspective_fudge_factor = 4.0f;   // not sure yet why this makes everything look more proportional
    this->win_mouse_motion_enabled = false;
    this->win_batch_vertex_cnt = 64*1024;
    this->win_batch_triangle_cnt = 32*1024;
    this->win_capture_enabled = false;
    this->win_overlay_text_color = Color::rgb( "gray" );
    this->win_overlay_text_scale_factor = 0.4;
    this->win_overlay_text_height = 85;
    this->win_overlay_text_width = 55;
    this->win_overlay_text_line_width = 7.0f;
    this->win_view_print = false;

    // hard code texids for now
    // we don't really have textures yet, just phony colors
    //
    this->texid_background      = Color::rgb( "black" );
    this->texid_unseen          = Color::rgb( "black" );

    // process command-line args
    //
    for( int i = 1; i < argc; i++ )
    {
        if ( strcmp( argv[i], "-win_fullscreen" ) == 0 ) {
            this->win_fullscreen = true;
        } else if ( strcmp( argv[i], "-win_capture" ) == 0 ) {
            this->win_capture_enabled = true;
        } else if ( strcmp( argv[i], "-win_eye_z" ) == 0 ) {
            this->win_eye[2] = atof( argv[++i] );
            this->win_view[2] = this->win_eye[2] - 0.5f;
        } else if ( strcmp( argv[i], "-win_view_print" ) == 0 ) {
            this->win_view_print = true;
        }
    }
}
