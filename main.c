/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:24:43 by modat             #+#    #+#             */
/*   Updated: 2025/04/21 20:18:53 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_mlx	*fractol;

	fractol = NULL;
	if (mem_alloc(&fractol))
		return (1);
	if (is_valid(fractol, argc, argv))
	{
		fractol->img.img = NULL;
		fractol->win = NULL;
		fractol->mlx = NULL;
		init_mlxset(fractol);
		mlx_hook(fractol->win, CLOSE, 0, close_win, fractol);
		mlx_hook(fractol->win, 2, 1, keypress_hook, fractol);
		mlx_mouse_hook(fractol->win, mouse_hook, fractol);
		mlx_key_hook(fractol->win, arrow_keys, fractol);
		mlx_loop_hook(fractol->mlx, fractal_rendering, fractol);
		mlx_loop(fractol->mlx);
	}
	clean_exit(fractol);
	return (0);
}
