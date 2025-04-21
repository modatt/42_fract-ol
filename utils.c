/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:25:20 by modat             #+#    #+#             */
/*   Updated: 2025/04/21 04:59:54 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_valid(t_mlx *fractol, int argc, char **argv)
{
	if (argc == 2)
	{
		if (ft_strcmp(argv[1], "mandlebrot") == 0)
			fractol->type = MANDELBROT;
		else if (ft_strcmp(argv[1], "burning_ship") == 0)
			fractol->type = BURNING_SHIP;
		else if (ft_strcmp(argv[1], "julia") == 0)
		{
			fractol->type = JULIA;
			fractol->fractal.j_cx = -0.835;
			fractol->fractal.j_cy = -0.2321;
		}
		else
			error_mess(fractol);
	}
	else if (argc == 4 && ft_strcmp(argv[1], "julia") == 0)
	{
		julia_valid(fractol, argv);
	}
	else
		error_mess(fractol);
	return (1);
}

void	julia_valid(t_mlx *fractol, char **argv)
{
	fractol->type = JULIA;
	if (is_julia_valid(argv[2]) == 1 && is_julia_valid(argv[3]) == 1)
	{
		fractol->fractal.j_cx = ft_atof(argv[2]);
		fractol->fractal.j_cy = ft_atof(argv[3]);
		if (fractol->fractal.j_cx < -2.0 || fractol->fractal.j_cx > 2.0
			|| fractol->fractal.j_cy < -2.0 || fractol->fractal.j_cy > 2.0)
			error_mess(fractol);
	}
	else
	{
		write(STDERR_FILENO, "<julia> range <[(-2 ~ 2),(-2 ~ 2)]>\n", 36);
		free(fractol);
		exit(0);
	}
}

int	is_julia_valid(char *str)
{
	int	sign_count;
	int	count_dot;

	sign_count = 0;
	count_dot = 0;
	if (*str == '-' || *str == '+')
	{
		sign_count++;
		str++;
	}
	if (sign_count > 1 || *str == '\0')
		return (0);
	while (*str)
	{
		if (*str == '.')
		{
			if (count_dot++)
				return (0);
		}
		else if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

void	error_mess(t_mlx *mlxset)
{
	write(STDERR_FILENO, "Enter a valid args:\n", 20);
	write(STDERR_FILENO, "./fractol <mandlebrot>\n", 23);
	write(STDERR_FILENO, "./fractol <burning_ship>\n", 25);
	write(STDERR_FILENO, "./fractol <julia> <real> <imaginery>\n", 37);
	free(mlxset);
	exit(1);
}
