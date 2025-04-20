/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:25:02 by modat             #+#    #+#             */
/*   Updated: 2025/04/20 19:07:12 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void julia_math(int x, int y, t_mlx *fractol)
{
    double zx, zy, temp;
    int iteration;

    // z starts at the screen-mapped coordinates
    zx = (x - WIDTH / 2.0) * (4.0 / (fractol->zoom * WIDTH)) + fractol->offset_x;
    zy = (y - HEIGHT / 2.0) * (4.0 / (fractol->zoom * HEIGHT)) + fractol->offset_y;

    // fractol->julia_cx and julia_cy should be constants (set by user or default)
    double cx = fractol->fractal.cx;
    double cy = fractol->fractal.cy;

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

void julia(t_mlx *fractol)
{
    int x = 0;
    int y = 0;

    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            julia_math(x, y, fractol);
            x++;
        }
        y++;
    }
}
