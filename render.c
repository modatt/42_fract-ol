/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 04:21:01 by modat             #+#    #+#             */
/*   Updated: 2025/04/21 20:20:44 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	fractal_rendering(t_mlx *fractol)
{
	int	y;
	int	x;

	y = 0;
	while (y++ < HEIGHT)
	{
		x = 0;
		while (x++ < WIDTH)
		{
			if (fractol->type == MANDELBROT)
				mandelbrot_math(x, y, fractol);
			else if (fractol->type == JULIA)
				julia_math(x, y, fractol);
			else if (fractol->type == BURNING_SHIP)
				burning_ship_math(x, y, fractol);
		}
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img,
		fractol->win_x, fractol->win_y);
	return (0);
}

void	mandelbrot_math(int x, int y, t_mlx *fractol)
{
	int		iteration;
	double	temp;

	fractol->fractal.zx = 0;
	fractol->fractal.zy = 0;
	fractol->fractal.cx = (x - WIDTH / 2.0) * (4.0 / (fractol->zoom * WIDTH))
		+ fractol->offset_x;
	fractol->fractal.cy = (y - HEIGHT / 2.0) * (4.0 / (fractol->zoom * HEIGHT))
		+ fractol->offset_y;
	iteration = 0;
	while (fractol->fractal.zx * fractol->fractal.zx + fractol->fractal.zy
		* fractol->fractal.zy < 4.0 && iteration < MAX_ITER)
	{
		temp = fractol->fractal.zx * fractol->fractal.zx - fractol->fractal.zy
			* fractol->fractal.zy + fractol->fractal.cx;
		fractol->fractal.zy = 2.0 * fractol->fractal.zx * fractol->fractal.zy
			+ fractol->fractal.cy;
		fractol->fractal.zx = temp;
		iteration++;
	}
	((int *)fractol->img.buffer)[y * WIDTH + x] = get_color(iteration,
			fractol->fractal.zx, fractol->fractal.zy, fractol);
}

void	julia_math(int x, int y, t_mlx *fractol)
{
	int		iter;
	double	cx;
	double	cy;
	double	temp;

	fractol->fractal.zx = (x - WIDTH / 2.0) * (4.0 / (fractol->zoom * WIDTH))
		+ fractol->offset_x;
	fractol->fractal.zy = (y - HEIGHT / 2.0) * (4.0 / (fractol->zoom * HEIGHT))
		+ fractol->offset_y;
	cx = fractol->fractal.j_cx;
	cy = fractol->fractal.j_cy;
	iter = 0;
	while (fractol->fractal.zx * fractol->fractal.zx + fractol->fractal.zy
		* fractol->fractal.zy < 4.0 && iter < MAX_ITER)
	{
		temp = fractol->fractal.zx * fractol->fractal.zx - fractol->fractal.zy
			* fractol->fractal.zy + cx;
		fractol->fractal.zy = 2.0 * fractol->fractal.zx * fractol->fractal.zy
			+ cy;
		fractol->fractal.zx = temp;
		iter++;
	}
	((int *)fractol->img.buffer)[y * WIDTH + x] = get_color(iter,
			fractol->fractal.zx, fractol->fractal.zy, fractol);
}

void	burning_ship_math(int x, int y, t_mlx *fractol)
{
	int		ite;
	double	temp_zx;
	double	temp_zy;
	int		color;
	double	temp;

	ite = 0;
	fractol->fractal.zx = 0;
	fractol->fractal.zy = 0;
	fractol->fractal.cx = (x - WIDTH / 2.0) * (4.0 / (fractol->zoom * WIDTH))
		+ fractol->offset_x;
	fractol->fractal.cy = (y - HEIGHT / 2.0) * (4.0 / (fractol->zoom * HEIGHT))
		+ fractol->offset_y;
	while (fractol->fractal.zx * fractol->fractal.zx + fractol->fractal.zy
		* fractol->fractal.zy < 4.0 && ite < MAX_ITER)
	{
		temp_zx = fabs(fractol->fractal.zx);
		temp_zy = fabs(fractol->fractal.zy);
		temp = temp_zx * temp_zx - temp_zy * temp_zy + fractol->fractal.cx;
		fractol->fractal.zy = 2.0 * temp_zx * temp_zy + fractol->fractal.cy;
		fractol->fractal.zx = temp;
		ite++;
	}
	color = get_color(ite, fractol->fractal.zx, fractol->fractal.zy, fractol);
	((int *)fractol->img.buffer)[y * WIDTH + x] = color;
}
