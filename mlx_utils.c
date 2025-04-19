/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:13:41 by modat             #+#    #+#             */
/*   Updated: 2025/04/19 11:27:03 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int    mem_alloc(t_mlx **fractol)
{
    *fractol = malloc(sizeof(t_mlx));
    if (!*fractol)
    {
        perror("Memory allocation failed");
        return 1;
    }
    return (0);
}

// static void    error_mes(t_mlx *mlxset)
// {
//     mlx_destroy_display(mlxset->mlx);
//     free(mlxset->mlx);
//     exit(EXIT_FAILURE);
// }

void    init_mlxset(t_mlx  *mlxset)
{
    mlxset->mlx = mlx_init();
    if (!mlxset)
        return ;
    mlxset->win = mlx_new_window(mlxset->mlx, WIDTH, HEIGHT, get_type_name(mlxset->type));
    if (!mlxset->win)
    {
        mlx_destroy_display(mlxset->mlx);
        free(mlxset->mlx);
        exit(EXIT_FAILURE);
    } // or error_mes();
    mlxset->img.img = mlx_new_image(mlxset->mlx, WIDTH, HEIGHT); // create image buffer canvas to draw on You now have an image buffer of WIDTH×HEIGHT pixels, but you don’t yet know how to reach its pixel memory.
    // img.img is the pointer returned by mlx_new_img >> the buffer
    if (!mlxset->img.img)
    {
        mlx_destroy_window(mlxset->mlx, mlxset->win);
        mlx_destroy_display(mlxset->mlx);
        free(mlxset->mlx);
        exit(EXIT_FAILURE);
    }
    mlxset->img.buffer = mlx_get_data_addr(mlxset->img.img, &mlxset->img.bpp, &mlxset->img.line_size, &mlxset->img.endian);
    if (!mlxset->img.buffer || mlxset->img.bpp <= 0 || mlxset->img.line_size <= 0)
    {
        perror("mlx_get_data_addr failed or returned invalid metadata\n");
        exit(EXIT_FAILURE);
    }
    // event_init(fractol)
    zoom_init(mlxset); // zoom ..etc. 
}


char *get_type_name(t_type type)
{
    if (type == MANDELBROT)
        return "Mandelbrot";
    else if (type == JULIA)
        return "Julia";
    else if (type == BURNING_SHIP)
        return "Burning Ship";
    return "Unknown";
}

void    zoom_init(t_mlx *fractol)
{
     // Set initial zoom and offsets
    fractol->zoom = 1.0;
    fractol->offset_x = 0.0;
    fractol->offset_y = 0.0;
}