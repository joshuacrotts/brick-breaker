#ifndef DRAW_H
#define DRAW_H

#include "stds.h"

extern app_t app;

/**
 * Clears the screen with a black color.
 */
extern void prepare_scene( void );

/**
 * Presents the current scene from the application.
 */
extern void present_scene( void );

/**
 * Copies the graphics from the texture to a different
 * rectangle. You can specify what portion of the src
 * SDL_Texture* to render by the size attributes of the
 * SDL_Rect* pointer
 */
extern void blit_rect( SDL_Texture *texture, SDL_Rect *src, float x, float y, bool camera_offset );

/**
 * Renders a texture, specified by src, at
 * coordinates (x, y). You may pass in both integers or
 * floating-point numbers to this function.
 *
 * @param SDL_Texture*
 * @param float x
 * @param float y
 * @param bool if the texture should be centered or not.
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
extern void blit_texture( SDL_Texture *texture, float x, float y, bool is_center,
                          bool camera_offset );

/**
 * Draws a rotated SDL_Texture pointer at an x, y coordinate. The
 * rotation is applied about the center of the texture.
 *
 * @param SDL_Texture* pointer to texture object.
 * @param float x coordinate.
 * @param float y coordinate.
 * @param uint16_t angle of rotation in degrees (0 to 360).
 * @param SDL_RendererFlip flip status (SDL_FLIP_HORIZONTAL/VERTICAL).
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
extern void blit_texture_rotated( SDL_Texture *texture, float x, float y, uint16_t angle,
                                  SDL_RendererFlip flip, bool camera_offset );

/**
 * Blits a rotated SDL texture at an x and y coordinate with a given
 * scale. A color is also provided to alter the color of the texture.
 *
 * @param SDL_Texture* pointer to texture object.
 * @param float x coordinate.
 * @param float y coordinate.
 * @param scale_x scale factor on x-axis.
 * @param scale_y scale factor on y-axis.
 * @param uint16_t angle of rotation (0 to 360).
 * @param SDL_RendererFlip flip status (SDL_FLIP_HORIZONTAL/VERTICAL)
 * @param SDL_Color* color to apply.
 * @param bool applies camera offset or not.
 *
 * @return void.
 */
extern void blit_texture_color_scaled( SDL_Texture *texture, float x, float y, float scale_x,
                                       float scale_y, uint16_t angle, SDL_RendererFlip flip,
                                       SDL_Color *c, bool camera_offset );

/**
 * Blits a rotated SDL texture at an x and y coordinate with a given
 * scale. Note that you will have to account for the scaling routine
 * yourself in your game (i.e. handling collisions if applicable).
 *
 * @param SDL_Texture*
 * @param float x
 * @param float y
 * @param float scale_x
 * @param float scale_y
 * @param uint16_t angle
 * @param SDL_RendererFlip flip status (SDL_FLIP_HORIZONTAL/VERTICAL)
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
extern void blit_texture_scaled( SDL_Texture *texture, float x, float y, float scale_x,
                                 float scale_y, uint16_t angle, SDL_RendererFlip flip,
                                 bool camera_offset );

/**
 * Draws a rectangle with the supplied color to the screen. The
 * rectangle's properties should be filled (i.e x, y, w, and h).
 * If the last parameter is true, the shape will be filled.
 *
 * @param SDL_Rect*
 * @param SDL_Color color to fill.
 * @param bool
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
extern void draw_rect( SDL_Rect *rect, SDL_Color *c, bool is_center, bool camera_offset );

/**
 * Draws a rectangle with the specified stroke (pixel width) and color.
 * First four parameters are the x, y, width, and height of rectangle.
 * The next specifies how "thick" it should be. The last four values
 * specify the RGBA values.
 *
 * @param int32_t x
 * @param int32_t y
 * @param uint32_t w
 * @param uint32_t h
 * @param uint32_t stroke thickness
 * @param SDL_Color *c color.
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
extern void draw_rect_stroke( int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t thickness,
                              SDL_Color *c, bool camera_offset );

/**
 * Draws a circle. Simple as that. Takes in the circle's center coordinates,
 * the radius, and RGBA.
 *
 * @param int32_t x-center of circle.
 * @param int32_t y-center of circle.
 * @param uint32_t radius of circle.
 * @param SDL_Color *c color to draw.
 *
 * @return void.
 */
extern void draw_circle( int32_t center_x, int32_t center_y, uint32_t radius, SDL_Color *c );

/**
 * Fills a circle. Simple as that.
 *
 * @param int32_t x-center of circle.
 * @param int32_t y-center of circle.
 * @param uint32_t radius of circle.
 * @param SDL_Color *c color to fill.
 *
 * @return void.
 */
extern void fill_circle( int32_t center_x, int32_t center_y, uint32_t radius, SDL_Color *c );

/*
 * Draws a line with the specified color to the screen.
 */
extern void draw_line( float x1, float y1, float x2, float y2, SDL_Color *c );

/*
 * Loads an image from the specified path. An error is
 * displayed if the file cannot be found or is not
 * loadable.
 */
extern SDL_Texture *load_texture( char *directory );

/*
 * Completes one iteration of the color-merge procedure.
 * The speed is dependent on the fade_color_t struct passed.
 */
extern SDL_Color combine_fade_color( fade_color_t *fade_color );

#endif
