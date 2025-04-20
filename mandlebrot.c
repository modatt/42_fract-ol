/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandlebrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:25:05 by modat             #+#    #+#             */
/*   Updated: 2025/04/20 20:58:10 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// f(Z) = z^2 + c
// c = (x_real, y_i) these are the inputs (fixed) for mandlebrot



void    mandelbrot(t_mlx *fractol)
{
    int y;
    int x;
        
    y = 0;
    while (y++ < HEIGHT)
    {
        x = 0;
        while (x++ < WIDTH)
        {
            mandelbrot_math(x, y, fractol);
            // x++;
        }
        // y++;     
    }
}

void mandelbrot_math(int x, int y, t_mlx *fractol)
{
    int iteration;
    double zx = 0, zy = 0, cx, cy, temp;
    
    cx = (x - WIDTH / 2.0) * (4.0 / (fractol->zoom * WIDTH)) + fractol->offset_x;
    cy = (y - HEIGHT / 2.0) * (4.0 / (fractol->zoom * HEIGHT)) + fractol->offset_y;
    iteration = 0;

    while (zx * zx + zy * zy < 4.0 && iteration < MAX_ITER)
    {
        temp = zx * zx - zy * zy + cx;
        zy = 2.0 * zx * zy + cy;
        zx = temp;
        iteration++;
    }

    ((int *)fractol->img.buffer)[y * WIDTH + x] = get_color(iteration, zx, zy, fractol);
}

// int get_color(int iteration, double zx, double zy, t_mlx *fractol)
// {
//     double smooth, log_zn, t;

//     if (iteration == MAX_ITER)
//         return (rgb(10, 10, 10));

//     log_zn = log(zx * zx + zy * zy) / 2.0;
//     smooth = iteration + 1 - log(log_zn / log(2)) / log(2);
//     t = smooth / MAX_ITER;

//     if (t > 0.6)
//     {
//         int r = (int)(9 * (1 - t) * t * t * t * 255);
//         int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
//         int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
//         return rgb(r, g, b);
//     }
//     return fractol->palette[iteration % PALETTE_SIZE];
// }

int rgb(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

void    init_colors(t_mlx *fractol)
{
    fractol->palette[0] = 0x421e0f;
    fractol->palette[1] = 0x19071a;
    fractol->palette[2] = 0x09012f;
    fractol->palette[3] = 0x040449;
    fractol->palette[4] = 0x000764;
    fractol->palette[5] = 0x0c2c8a;
    fractol->palette[6] = 0x1852b1;
    fractol->palette[7] = 0x397dd1;
    fractol->palette[8] = 0x86b5e5;
    fractol->palette[9] = 0xd3ecf8;
    fractol->palette[10] = 0xf1e9bf;
    fractol->palette[11] = 0xf8c95f;
    fractol->palette[12] = 0xffaa00;
    fractol->palette[13] = 0xcc8000;
    fractol->palette[14] = 0x995700;
    fractol->palette[15] = 0x6a3403;
}
int get_color(int iteration, double zx, double zy, t_mlx *fractol)
{
    double log_zn, nu, t;

    if (iteration == MAX_ITER)
        return rgb(0, 0, 0); // Black center

    // Smooth iteration count
    log_zn = log(zx * zx + zy * zy) / 2.0;
    nu = log(log_zn / log(2)) / log(2);
    t = iteration + 1 - nu;

    // Map t to palette index with interpolation
    int idx1 = (int)t % PALETTE_SIZE;
    int idx2 = (idx1 + 1) % PALETTE_SIZE;
    double frac = t - floor(t);

    // Extract RGB components from palette
    int color1 = fractol->palette[idx1];
    int color2 = fractol->palette[idx2];

    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;

    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;

    // Linear interpolation
    int r = (int)((1 - frac) * r1 + frac * r2);
    int g = (int)((1 - frac) * g1 + frac * g2);
    int b = (int)((1 - frac) * b1 + frac * b2);

    return rgb(r, g, b);
}
