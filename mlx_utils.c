/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:13:41 by modat             #+#    #+#             */
/*   Updated: 2025/04/21 20:19:50 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	exit_faild(t_mlx *mlxset)
{
	clean_exit(mlxset);
	exit(EXIT_FAILURE);
}

void	init_mlxset(t_mlx *mlxset)
{
	mlxset->mlx = mlx_init();
	if (!mlxset->mlx)
		exit_faild(mlxset);
	mlxset->win = mlx_new_window(mlxset->mlx, WIDTH, HEIGHT,
			get_type_name(mlxset->type));
	if (!mlxset->win)
	{
		exit_faild(mlxset);
	}
	mlxset->img.img = mlx_new_image(mlxset->mlx, WIDTH, HEIGHT);
	if (!mlxset->img.img)
	{
		mlx_destroy_window(mlxset->mlx, mlxset->win);
		exit_faild(mlxset);
	}
	mlxset->img.buffer = mlx_get_data_addr(mlxset->img.img, &mlxset->img.bpp,
			&mlxset->img.line_size, &mlxset->img.endian);
	if (!mlxset->img.buffer || mlxset->img.bpp <= 0
		|| mlxset->img.line_size <= 0)
	{
		perror("mlx_get_data_addr failed or returned invalid metadata\n");
		exit(EXIT_FAILURE);
	}
	init_colors(mlxset);
	zoom_init(mlxset);
}

char	*get_type_name(t_type type)
{
	if (type == MANDELBROT)
		return ("Mandelbrot");
	else if (type == JULIA)
		return ("Julia");
	else if (type == BURNING_SHIP)
		return ("Burning Ship");
	return ("Unknown");
}

void	zoom_init(t_mlx *fractol)
{
	if (fractol->type == BURNING_SHIP)
	{
		fractol->zoom = 20.0;
		fractol->offset_x = -1.758;
		fractol->offset_y = -0.035;
	}
	else
	{
		fractol->zoom = 1.0;
		fractol->offset_x = 0.0;
		fractol->offset_y = 0.0;
	}
}

void	clean_exit(t_mlx *mlxset)
{
	if (mlxset->img.img)
		mlx_destroy_image(mlxset->mlx, mlxset->img.img);
	if (mlxset->win)
		mlx_destroy_window(mlxset->mlx, mlxset->win);
	if (mlxset->mlx)
	{
		mlx_destroy_display(mlxset->mlx);
		free(mlxset->mlx);
		free(mlxset);
	}
}
