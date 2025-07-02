# fract-ol

** Graphical project. **

**Fract-ol Project**
- Goal: draw fractals (mandelbrot, julia set, burning_ship).
- Learning objectives: Learn computer graphics optmization:
    1. Minilibx practicing.
    2. Complex numbers using.
    3. Event handling. 

## Do Fract-ol

1. Set up **Makefile** to compile and test the projects through in each step.
2. Prepare the **header** to be able to compile the project correctly.
-> setting the structure that needed for the project (since we need to use it here). (1)
3. Writting from the **main.c** whereas our project starts from there.

## Project requirments 
* To draw:
- Place to draw on it "image + window"
- Tools to draw "mlx- tools"
- Display "mlx + win to display the paint"

## Pre knowledge: Computer Graphics
**Graphics models:**
1. Raster - bit map: (we will use it here)
Raster images are represented by dots pixels.Since it is represented by pixel it is a resolution dependent. Files structures such as JPG, PNG, BMP, GIF. More detailed images.

{bit-map>> Raster images(more details higher quality), resolution dependent} 
2. Vector is the opposite less details, smaller image and less space in memory. They are represented by sequence of commands or mathmatical statements.
everytime I want to render a thing, first, I need to connect to the server. establish a connection with the server. 
- mlx_init() has *xvar a pointer to a struct
 
### Project Implementation:

#1: connect to mlx.  mlx_init()
#2: create a window. mlx_new_window()
#3: images.
#4: draw on image.
#5: display image on window.


## pre-sets:
0.1. check args validation: is_valid().

./fractol <fractal type> <para 1> <para 2>
--> 0.1.1. check argc either 2 or 4 
fractol type <mandelbrot> or <burning_ship>:
    ./fractol <fractal type>
    ->> assign the type to mlx_set->type. 
fractol <julia>:
    ./fractol <fractal type> <para 1> <para 2>
    ->> convert 

__the type enum___
typedef enum
{
    MANDELBROT,
    JULIA,
    BURNING_SHIP
} t_type;



main.c::

1. connect to mlx: mlx_init()
     to have access to the library functions and allocate a memory working through it.
    
    mlx_init():
     - takes no parameter.
     - mlx_set->mlx = mlx_init().

since the mlx library functions takes one args but works on server inside inputs, I need to grouping the mlx sets.
->> create a struct for mlx needs:
typedef struct s_mlx;
{
    void    *mlx; // 1. connect to mlx: to build a connection through it.
    void    *win; // 2. create a win: to create the win to draw on it.
    t_type  type;
}


2. create a win: 
    mlx_new_window(mlx_connection, width, height, title).

->> need to assign macros WIDTH & HEIGHT. "I can just write numbers but I will use them a lot and this is much easier"
1.  #define WIDTH = 800;
    #define HEIGHT = 600;
2. from s_mlxs truct:
    void    *mlx;
    void    *win;
3. title: can be written "fractol", but I want to name it based on the type of fractol, therefore, I have written specific function.
    mlx_set->win = mlx_new_window(mlx_set->mlx, WIDTH, HEIGHT, get_type_name(mlx_set->type));
    get_type_name(mlx_set->type); ->> to return the entered fractol name type.

4. Get Image Data Address
You need to get a pointer to the raw pixel buffer of the image, so you can write pixel colors directly:


Edit
mlxset->img.addr = mlx_get_data_addr(mlxset->img.img,
                                     &mlxset->img.bpp,
                                     &mlxset->img.line_size,
                                     &mlxset->img.endian);
This gives you:

addr/ buffer → pointer to the actual pixel data.

bpp (bits per pixel) → usually 32.

line_size (bytes per line) → important for jumping to next row.

endian → tells you pixel format.

##  x and y in put_pixel
x → the horizontal position of the pixel (0 is left, increasing to the right)

y → the vertical position of the pixel (0 is top, increasing downward)

So if your image size is WIDTH = 800 and HEIGHT = 800:

Valid x range is: 0 to 799

Valid y range is: 0 to 799


     x ➡
   ┌────────────────────────────────┐
 y │ (0,0)      ...           (799,0)
 ↓ │
   │
   │
   │ (0,799)    ...         (799,799)
   └────────────────────────────────┘

### mapping 
Absolutely! Let’s break down mapping from screen space to the complex plane — slowly, clearly, and visually. 

 Imagine Your Window:
Let's say your screen (window) size is:

WIDTH = 800
HEIGHT = 800
This is your pixel space (aka screen space):


(0,0)              → Top-left corner  
(799,799)          → Bottom-right corner
Now, let’s say you're rendering the Mandelbrot set, and the part of the complex plane you're viewing is:

Real range:   [-2.0 to +2.0]     ⬅ left to right
Imaginary range: [+2.0 to -2.0] ⬅ top to bottom (yes, Y is upside down)
 Goal
For every pixel (x, y) on your screen, figure out which complex number c = re + im*i it represents.

 The Formula (Linear Interpolation)
This is how we "map" a number from one range to another:


double map(double val, double from_min, double from_max, double to_min, double to_max)
{
    return to_min + (val - from_min) * (to_max - to_min) / (from_max - from_min);
}
 Example: Map pixel x = 400 (middle of screen) → Real number
We’re mapping:

val = 400

From range [0 to 800] (pixel width)

To range [-2.0 to +2.0] (complex plane)


map(400, 0, 800, -2.0, +2.0) = 0.0
That makes sense! 400 is halfway, and 0.0 is halfway between -2.0 and +2.0.

 Visual Summary
mathematica
Copy code
Screen X (Pixels):     0          400           800
                      |------------|------------|
Complex Re:         -2.0         0.0          +2.0
Same for y → imaginary (with flipped y-axis, optional):

mathematica
Copy code
Screen Y (Pixels):     0          400           800
                      |------------|------------|
Complex Im:         +2.0         0.0          -2.0
So pixel (400, 400) = complex number 0.0 + 0.0i

 Use in Mandelbrot Code
In your fractal rendering loop:

c
Copy code
for (int y = 0; y < HEIGHT; y++)
{
    for (int x = 0; x < WIDTH; x++)
    {
        double re = map(x, 0, WIDTH, -2.0 / zoom + offset_x, +2.0 / zoom + offset_x);
        double im = map(y, 0, HEIGHT, +2.0 / zoom + offset_y, -2.0 / zoom + offset_y);

        // Use (re, im) as your complex number 'c' for Mandelbrot
    }
}
zoom controls how close you’re zoomed in

offset_x/y move the center

map() figures out the correct re and im values

 TL;DR
Mapping screen to complex plane is just:

"Take a screen coordinate and stretch it to match the current view of the complex plane."

Without this, you’d just be drawing on pixels, but Mandelbrot happens in the land of complex numbers 
