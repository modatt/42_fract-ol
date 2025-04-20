/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:24:53 by modat             #+#    #+#             */
/*   Updated: 2025/04/20 19:39:07 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// void burning_ship_math(int x, int y, t_mlx *fractol)
// {
//     double zx, zy, cx, cy, temp;
//     int iteration;

//     cx = (x - WIDTH / 2.0) * (4.0 / (fractol->zoom * WIDTH)) + fractol->offset_x;
//     cy = (y - HEIGHT / 2.0) * (4.0 / (fractol->zoom * HEIGHT)) + fractol->offset_y;
//     zx = 0;
//     zy = 0;
//     iteration = 0;

//     while (zx * zx + zy * zy < 4.0 && iteration < MAX_ITER)
//     {
//         temp = zx * zx - zy * zy + cx;
//         zy = fabs(2.0 * zx * zy) + cy;
//         zx = fabs(temp);
//         iteration++;
//     }

//     ((int *)fractol->img.buffer)[y * WIDTH + x] = get_color(iteration, zx, zy, fractol);
// }

// void burning_ship(t_mlx *fractol)
// {
//     int x = 0;
//     int y = 0;

//     while (y < HEIGHT)
//     {
//         x = 0;
//         while (x < WIDTH)
//         {
//             burning_ship_math(x, y, fractol);
//             x++;
//         }
//         y++;
//     }
// }


#include <math.h>      // fabs
#include "fractol.h"   // assumes t_mlx, WIDTH, HEIGHT, MAX_ITER, etc. are defined

// 🔥 Burning Ship Pixel Calculation
void burning_ship_math(int x, int y, t_mlx *fractol)
{
    double zx, zy, cx, cy, temp;
    int iteration;

    // Map pixel (x, y) to complex plane (cx, cy)
    cx = (x - WIDTH / 2.0) * (4.0 / (fractol->zoom * WIDTH)) + fractol->offset_x;
    cy = (y - HEIGHT / 2.0) * (4.0 / (fractol->zoom * HEIGHT)) + fractol->offset_y;

    zx = 0;
    zy = 0;
    iteration = 0;

    // Fractal iteration loop with correct Burning Ship logic
    while (zx * zx + zy * zy < 4.0 && iteration < MAX_ITER)
    {
        double temp_zx = fabs(zx);
        double temp_zy = fabs(zy);

        temp = temp_zx * temp_zx - temp_zy * temp_zy + cx;
        zy = 2.0 * temp_zx * temp_zy + cy;
        zx = temp;

        iteration++;
    }

    // Use your color function here
    int color = get_color(iteration, zx, zy, fractol);
    ((int *)fractol->img.buffer)[y * WIDTH + x] = color;
}

// 🚀 Main Render Function
void burning_ship(t_mlx *fractol)
{
    int x, y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            burning_ship_math(x, y, fractol);
            x++;
        }
        y++;
    }
}
