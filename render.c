#include "fractol.h"

// scaling a rage of numbers with a known max & min values.
/*
            800
  (0, 0) _ _ _ _ _ _ _ _ _ _ _ _   
        |                       |
    600 |                       |
        |                       |
        |                       |
        |                       |
        |_ _ _ _ _ _ _ _ _ _ _ _|

         _ _ _ _ _ _ _ _ _ _ _ _
        |                       |
        |                       |
        |        (0,0)          |
        |                       |
        |                       |
        |_ _ _ _ _ _ _ _ _ _ _ _|
*/
// linear interpolation
// double      mapping(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
// {
//     return (new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min)  + new_min;
// }
// void    pixel_handler(int x, int y, t_mlx *fractol)
// {
//     t_complex z;
//     t_complex c;

//     z.x_real = 0.0;
//     z.y_imaginery = 0.0;

//     // c.x = 



// }

void    fractol_render(t_mlx *fractol)
{
    int x;
    int y;

    y = 0;
    while (y++ < HEIGHT)
    {
        x = 0;
        while (x++ < WIDTH)
        {
            pixel_handler(x, y, fractol);
        }
        
    }
    
}