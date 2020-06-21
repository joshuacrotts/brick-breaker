#ifndef DRAW_H
#define DRAW_H

#include "stds.h"

extern app_t app;


/*
 * Clears the screen with a black color.
 */
extern void 
prepare_scene();


/*
 * Presents the current scene from the application.
 */
extern void 
present_scene();


/*
 * Copies the graphics from the texture to a different
 * rectangle. You can specify what portion of the src
 * SDL_Texture* to render by the size attributes of the
 * SDL_Rect* pointer. Integers and floats can be passed
 * for the location parameters, but they will be down-casted
 * to integers.
 */
extern void 
blit_rect(SDL_Texture*, SDL_Rect*, float, float);


/*
 * Renders a texture, specified by src, at
 * coordinates (x, y). You may pass in both integers or
 * floating-point numbers to this function, but any floating-point
 * values will be down-casted to integers.
 */
extern void 
blit_texture(SDL_Texture*, float, float, bool);


/*
 * Draws a rotated SDL_Texture pointer at an x, y coordinate. You may
 * pass in both integers or floating-point numbers to this function, but
 * any floating-point values will be down-casted to integers.
 *
 * @param SDL_Texture* pointer to texture object.
 * @param float x coordinate.
 * @param float y coordinate.
 * @param uint16_t angle of rotation (0 to 360).
 */
extern void 
blit_texture_rotated(SDL_Texture*, float, float, uint16_t);


/*
 * Blits a rotated SDL texture at an x and y coordinate with a given
 * scale. A color is also provided to alter the color of the texture.
 * 
 * @param SDL_Texture* pointer to texture object.
 * @param float x coordinate.
 * @param float y coordinate.
 * @param scale_x scale factor on x-axis.
 * @param scale_y scale factor on y-axis.
 * @param uint16_t angle of rotation (0 to 360).
 * @param uint8_t r color value.
 * @param uint8_t g color value.
 * @param uint8_t b color value.
 * @param uint8_t a color value.
 */
extern void 
blit_texture_color_scaled(SDL_Texture*, float, float, float, float, uint16_t, uint8_t, uint8_t, uint8_t, uint8_t);


/*
 * Blits a rotated SDL texture at an x and y coordinate with a given
 * scale. Note that you will have to account for the scaling routine
 * yourself in your game (i.e. handling collisions if applicable).
 */
extern void 
blit_texture_scaled(SDL_Texture*, float, float, float, float, uint16_t);


/*
 * Draws a rectangle with the supplied color to the screen. The
 * rectangle's properties should be filled (i.e x, y, w, and h).
 * If the last parameter is true, the shape will be filled.
 */
extern void 
draw_rect(SDL_Rect*, uint8_t, uint8_t, uint8_t, uint8_t, bool);


/*
 * Draws a rectangle with the specified stroke (pixel width) and color.
 * First four parameters are the x, y, width, and height of rectangle.
 * The next specifies how "thick" it should be. The last four values 
 * specify the RGBA values.
 */
extern void 
draw_rect_stroke(int32_t, int32_t, uint32_t, uint32_t, uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);


/*
 * Draws a circle. Simple as that. Takes in the circle's center coordinates,
 * the radius, and RGBA.
 */
extern void 
draw_circle(int32_t, int32_t, uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);


/*
 * Fills a circle. Simple as that.
 */
extern void 
fill_circle(int32_t, int32_t, uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);


/*
 * Draws a line with the specified color to the screen.
 */
extern void 
draw_line(float, float, float, float, uint8_t, uint8_t, uint8_t, uint8_t);


/*
 * Loads an image from the specified path. An error is
 * displayed if the file cannot be found or is not
 * loadable.
 */
extern SDL_Texture* 
load_texture(char*);


/*
 *
 */
extern SDL_Color 
combine_fade_color(fade_color_t*);

#endif
