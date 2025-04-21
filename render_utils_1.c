/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 03:39:50 by modat             #+#    #+#             */
/*   Updated: 2025/04/21 20:20:10 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	get_smooth_iteration(double zx, double zy, int iteration)
{
	double	log_zn;
	double	nu;

	log_zn = log(zx * zx + zy * zy) / 2.0;
	nu = log(log_zn / log(2)) / log(2);
	return (iteration + 1 - nu);
}

static t_rgb	extract_rgb(int color)
{
	t_rgb	rgb;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (rgb);
}

static t_rgb	interpolate_color(t_rgb c1, t_rgb c2, double frac)
{
	t_rgb	result;

	result.r = (int)((1 - frac) * c1.r + frac * c2.r);
	result.g = (int)((1 - frac) * c1.g + frac * c2.g);
	result.b = (int)((1 - frac) * c1.b + frac * c2.b);
	return (result);
}

static t_palette_info	get_palette_info(double t, t_mlx *fractol)
{
	t_palette_info	info;
	int				idx1;
	int				idx2;

	idx1 = (int)t % PALETTE_SIZE;
	idx2 = (idx1 + 1) % PALETTE_SIZE;
	info.frac = t - floor(t);
	info.color1 = fractol->palette[idx1];
	info.color2 = fractol->palette[idx2];
	return (info);
}

int	get_color(int iteration, double zx, double zy, t_mlx *fractol)
{
	double			t;
	t_palette_info	palette;
	t_rgb			c1;
	t_rgb			c2;
	t_rgb			final_color;

	if (iteration == MAX_ITER)
		return (rgb(0, 0, 0));
	t = get_smooth_iteration(zx, zy, iteration);
	palette = get_palette_info(t, fractol);
	c1 = extract_rgb(palette.color1);
	c2 = extract_rgb(palette.color2);
	final_color = interpolate_color(c1, c2, palette.frac);
	return (rgb(final_color.r, final_color.g, final_color.b));
}
