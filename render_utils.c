/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 03:36:13 by modat             #+#    #+#             */
/*   Updated: 2025/04/21 20:20:34 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	init_colors(t_mlx *fractol)
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
