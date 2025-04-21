/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:24:58 by modat             #+#    #+#             */
/*   Updated: 2025/04/21 20:19:08 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_win(t_mlx *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img.img);
	mlx_clear_window(fractol->mlx, fractol->win);
	mlx_destroy_window(fractol->mlx, fractol->win);
	mlx_destroy_display(fractol->mlx);
	free(fractol->mlx);
	free(fractol);
	exit(0);
	return (0);
}

int	keypress_hook(int keycode, t_mlx *fractol)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_image(fractol->mlx, fractol->img.img);
		mlx_clear_window(fractol->mlx, fractol->win);
		mlx_destroy_window(fractol->mlx, fractol->win);
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
		free(fractol);
		exit(0);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_mlx *fractol)
{
	double	mouse_real;
	double	mouse_imag;

	mouse_real = (x - WIDTH / 2.0) * (4.0 / (fractol->zoom * WIDTH))
		+ fractol->offset_x;
	mouse_imag = (y - HEIGHT / 2.0) * (4.0 / (fractol->zoom * HEIGHT))
		+ fractol->offset_y;
	if (button == 4)
		fractol->zoom *= ZOOM_FACTOR;
	else if (button == 5)
		fractol->zoom /= ZOOM_FACTOR;
	else
		return (0);
	fractol->offset_x = mouse_real - (x - WIDTH / 2.0) * (4.0 / (fractol->zoom
				* WIDTH));
	fractol->offset_y = mouse_imag - (y - HEIGHT / 2.0) * (4.0 / (fractol->zoom
				* HEIGHT));
	return (0);
}

int	arrow_keys(int keycode, t_mlx *fractol)
{
	if (keycode == KEY_UP)
		fractol->offset_y -= 0.001;
	else if (keycode == KEY_DOWN)
		fractol->offset_y += 0.001;
	else if (keycode == KEY_LEFT)
		fractol->offset_x -= 0.001;
	else if (keycode == KEY_RIGHT)
		fractol->offset_x += 0.001;
	return (0);
}
