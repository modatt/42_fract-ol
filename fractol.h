#ifndef FRACTOL_H
#define FRACTOL_H

#include <unistd.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600 
#define ESC_KEY 65307
#define CLOSE 17

#define ZOOM_FACTOR 1.1
#define PAN_FACTOR 0.1
#define MOVE_SPEED 0.1
#define MAX_ITER  100

#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_UP 65362
#define KEY_DOWN 65364
#define PALETTE_SIZE 16

typedef struct s_fractal
{
    double      zx;
    double      zy;
    double      cx;
    double      cy;
    int     max_iter; 
    double  j_real;
    double  j_imaginery;
} t_fractal;

typedef struct s_complex
{
    double  real;
    double  imaginery;

} t_complex;

// first built this to args checing
typedef enum
{
    MANDELBROT,
    JULIA,
    BURNING_SHIP
} t_type;
// in fractol we use raster image to draw
// to zoom in and still see image
typedef struct s_image
{
    void    *img; // image buffer/ canvas to draw on // pointer to buffer returned by new_img()
    char    *buffer; // store the image buffer pointer address & image data.
    int     bpp; // bits per pixel 
    int     line_size; // number of bytes in the line.
    int     endian; // is either 0 or 1, 1 == most signeficant byte or 0 == least. to describe the order of bytes in memory 

} t_image;
/*
Correct channel mapping
If you assume the wrong byte order, your red, green, and blue channels end up swapped and your image looks garbled.

Portability
If you ever run your code on a big‑endian platform (very rare these days, but possible in embedded or older hardware),
 a raw 32‑bit write would place the bytes in the opposite order—so your colors would all be wrong unless you handle endianness.

 In plain terms: endianness is just the CPU’s “direction” for multi‑byte numbers in memory.
  On your machine (“least significant first”), the byte that matters least goes into the lowest address, 
  and the one that matters most goes into the highest. Getting that right makes sure “0x00FF0000” actually paints red,
   not green or blue!
Byte 3 | Byte 2 | Byte 1 | Byte 0
  AA   |   RR   |   GG   |   BB
“Least significant byte” (LSB) is Byte 0 (BB)—it contributes the smallest value (the “ones” place in normal decimal).

“Most significant byte” (MSB) is Byte 3 (AA)—it contributes the largest value (the “billions” place, if you will).

 */

typedef struct s_mlx
{
    t_type  type;
    void    *mlx;
    void    *win;
    t_image img;
// zoom hooks:
    double  zoom;       // Zoom level (like scale)
    double  offset_x;   // X pan offset in complex plane
    double  offset_y;   // Y pan offset in complex plane
// Fractal parameters:
    double  win_x;
    double  win_y;
    int palette[PALETTE_SIZE];
    t_complex   complex;
    t_fractal   fractal;
} t_mlx;


/*
For zooming: I do the mapping screen to complex plane
*/

// setup::
void        init_mlxset(t_mlx  *mlxset);
void        zoom_init(t_mlx *fractol);
int         mem_alloc(t_mlx **fractol);

// utils setup::
int         is_valid(t_mlx *fractol, int argc, char **argv);
int         ft_strcmp(const char *s1, const char *s2);
double      ft_atof1(const char *nptr, unsigned int i);
double      ft_atof(const char *nptr);
char        *get_type_name(t_type type);

// math utils
// double  mapping(double value, double min, double max, double screen_max);

// events::
int     keypress_hook(int keycode, t_mlx *fractol);
int     close_win(t_mlx *fractol);
int     mouse_hook(int button, int x, int y, t_mlx *fractol);
int     arrow_keys(int keycode, t_mlx *fractol);

// rendering
void    mandelbrot(t_mlx *fractol);
int   fractal_rendering(t_mlx *fractol);
// int rgb(int r, int g, int b);

int rgb(int r, int g, int b);
int get_color(int iteration, double zx, double zy, t_mlx *fractol);
// int hsv_to_rgb(double h, double s, double v);
void mandelbrot_math(int x, int y, t_mlx *fractol);
void    init_colors(t_mlx *fractol);
void julia(t_mlx *fractol);
void julia_math(int x, int y, t_mlx *fractol);
void burning_ship(t_mlx *fractol);
void burning_ship_math(int x, int y, t_mlx *fractol);

void print_type(t_mlx *fractol);

#endif 

/*

💡 What does 1L << 0 mean?
This is bit shifting. Let’s unpack it:

1L means the number 1 as a long (not int).

<< 0 means "shift it 0 bits to the left."

So 1L << 0 = 1.


ESC handling ::
🔢 Event and Mask Pairing in MLX
Event Number	  Event Name    	                    Mask	       Bit Shift (1L << ?)
    2	           KeyPress	                        1L << 0 → 1	             0
    3	           KeyRelease	                    1L << 1 → 2	             1
    4	           ButtonPress	                    1L << 2 → 4	             2
    5	           ButtonRelease	                1L << 3 → 8	             3
    6	           MotionNotify	                    1L << 6 → 64	         6
    17	           DestroyNotify (close window)	    1L << 17 → 131072	     17

*/